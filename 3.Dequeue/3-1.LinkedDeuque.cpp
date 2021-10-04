#include <assert.h>
#include <stddef.h>  // for NULL
template <class T>
class DoubleLinkedList {
private:
    class Node {
    public:
        T value;
        Node* prev;
        Node* next;

        Node() : value(0), prev(NULL), next(NULL) {}
        Node(T _value) : value(_value), prev(NULL), next(NULL) {}
    };

public:
    class Iterator {
    public:
        Iterator() {}
        Iterator(Node*);
        T& operator*();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        Iterator& operator++();
        Iterator& operator--();
        Node* ptr;
    };

public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    // insert, remove
    Iterator begin() const;
    Iterator end() const;
    bool empty() const;
    int size() const;
    void pushFront(const T&);
    void pushBack(const T&);
    void popFront();
    void popBack();
    // lvalue , rvalue error
    Iterator& insert(Iterator&, const T&);
    void erase(Iterator&);

    const T& front() const;
    const T& back() const;

private:
    Node* head;
    Node* tail;
    int length;
};

template <class T>
DoubleLinkedList<T>::DoubleLinkedList() {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
    length = 0;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    while (!empty()) {
        popBack();
    }
}
template <class T>
bool DoubleLinkedList<T>::empty() const { return head->next == tail; }
template <class T>
int DoubleLinkedList<T>::size() const { return length; }
template <class T>
void DoubleLinkedList<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}
template <class T>
void DoubleLinkedList<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}
template <class T>
const T& DoubleLinkedList<T>::front() const {
    assert(!empty());
    return head->next->value;
};

template <class T>
const T& DoubleLinkedList<T>::back() const {
    assert(!empty());
    return tail->prev->value;
};

template <class T>
void DoubleLinkedList<T>::popBack() {
    assert(!empty());
    tail->prev = tail->prev->prev;
    tail->prev->next = tail;
    length--;
};

template <class T>
void DoubleLinkedList<T>::popFront() {
    assert(!empty());
    head->next = head->next->next;
    head->next->prev = head;
    length--;
};

//// Iterator
template <class T>
DoubleLinkedList<T>::Iterator::Iterator(Node* node) { ptr = node; }

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const {
    Iterator it = Iterator(head->next);
    return it;
};
template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const {
    Iterator it = Iterator(tail);
    return it;
};

template <class T>
T& DoubleLinkedList<T>::Iterator::operator*() {
    // assert ptr is not head and not tail
    assert(ptr->prev != NULL && ptr->next != NULL);
    return ptr->value;
}

template <class T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& it) const { return ptr == it.ptr; }
template <class T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& it) const { return ptr != it.ptr; }
// begin의 Iterator의 타입이 DoubleLinkedList에 종속적이기 때문에 typename 혹은 class를 앞에 붙여줘야한다
template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator ::operator++() {
    assert(ptr->next != NULL);
    ptr = ptr->next;
    return *this;
}
template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator ::operator--() {
    assert(ptr->prev != NULL);
    ptr = ptr->prev;
    return *this;
}

template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::insert(Iterator& it, const T& value) {
    length++;
    if (it.ptr->prev->prev == NULL) {  // if it is begin()    NULL<-[head]<->[begin()]
        pushFront(value);
        return --it;
    }
    if (it.ptr->next == NULL) {  // if it is end() [tail] -> NULL
        pushBack(value);
        return --it;
    }

    Node* newNode = new Node(value);
    newNode->prev = it.ptr->prev;
    newNode->next = it.ptr;
    it.ptr->prev->next = newNode;
    it.ptr->prev = newNode;
    --it;
    return it;
}

template <class T>
void DoubleLinkedList<T>::erase(Iterator& it) {
    length--;
    if (it.ptr->prev->prev == NULL) {  // begin()
        popFront();
        return;
    }
    if (it.ptr->next == NULL) {  // end()
        popBack();
        return;
    }

    it.ptr->prev->next = it.ptr->next;
    it.ptr->next->prev = it.ptr->prev;
}

template <class T>
class LinkedDequeue {
public:
    LinkedDequeue();
    ~LinkedDequeue();
    int size();
    bool empty();
    const T& front();
    const T& back();
    void pushFront(const T&);
    void pushBack(const T&);
    void popFront();
    void popBack();

private:
    DoubleLinkedList<T> list;
};

template <class T>
LinkedDequeue<T>::LinkedDequeue() : list(){};
template <class T>
LinkedDequeue<T>::~LinkedDequeue(){};

template <class T>
int LinkedDequeue<T>::size() { return list.size(); };
template <class T>
bool LinkedDequeue<T>::empty() { return size() == 0; };
template <class T>
const T& LinkedDequeue<T>::front() { return list.front(); };
template <class T>
const T& LinkedDequeue<T>::back() { return list.back(); };

template <class T>
void LinkedDequeue<T>::pushFront(const T& value) { list.pushFront(value); };

template <class T>
void LinkedDequeue<T>::pushBack(const T& value) { list.pushBack(value); };
template <class T>
void LinkedDequeue<T>::popFront() { list.popFront(); };

template <class T>
void LinkedDequeue<T>::popBack() { list.popBack(); };

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    LinkedDequeue<int> dq;

    for (int i = 0; i < 10; i++) dq.pushBack(i);
    while (dq.size()) {
        cout << dq.front() << ' ';
        dq.popFront();
    }
}