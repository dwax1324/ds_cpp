#include <assert.h>
#include <cstddef>




// NODE
template<typename T>
class Node {
public:
    T value;
    Node<T>* next;
    Node() {};
    Node(T _value, Node* _next) :value(_value), next(_next) {};
};


// ITERATOR
template<typename T>
class Iterator {
public:
    T& operator*();
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&)const;
    Iterator& operator++();
    Node<T>* v;
    Iterator(Node<T>* u);
};


// SINGLYLINKEDLIST 
template<typename T>
class SingleLinkedList {

public:

    SingleLinkedList();
    ~SingleLinkedList();
    Iterator<T> begin() const;
    Iterator<T> end() const;
    bool empty() const;
    int size() const;
    const T& front() const;
    void pushFront(const T&);
    void popFront();
    void remove(const T&); // remove by value
    Iterator<T> erase(const Iterator<T>&);
    void insert(const Iterator<T>&);

private:
    int sz;
    Node<T>* head;
};


// Iterator
template<typename T>
Iterator<T>::Iterator(Node<T>* u) { v = u; }
template<typename T>
T& Iterator<T>::operator*() { return v->value; }
template<typename T>
bool Iterator<T>::operator==(const Iterator& p)const { return v == p.v; }
template<typename T>
bool Iterator<T>::operator!=(const Iterator& p)const { return v != p.v; }
template<typename T>
Iterator<T>& Iterator<T>::operator++() { v = v->next; return *this; }
template<typename T>
Iterator<T> SingleLinkedList<T>::begin()const { return Iterator(head); }
template<typename T>
Iterator<T> SingleLinkedList<T>::end()const {
    Node<T>* ptr = head;
    while (ptr->next != NULL) ptr = ptr->next;
    return Iterator(ptr);
}






// SingleLinkedList
template<typename T>
SingleLinkedList<T>::SingleLinkedList() :head(NULL) {}
template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    while (!empty()) {
        popFront();
    }
}


template<typename T>
bool SingleLinkedList<T>::empty() const { return head == NULL; }

template<typename T>
const T& SingleLinkedList<T>::front() const {
    assert(!empty());
    return head->value;
}

template<typename T>
void SingleLinkedList<T>::pushFront(const T& newValue) {
    Node<T>* newNode = new Node<T>;
    newNode->value = newValue;
    newNode->next = head;
    head = newNode;
}

template<typename T>
void SingleLinkedList<T>::popFront() {
    assert(!empty());
    Node<T>* old = head;
    head = head->next;
    delete old;
}
template<typename T>
void SingleLinkedList<T>::remove(const T& target) {

    if (head == NULL) {
        head = new Node<T>;
        head->value = target;
        return;
    }
    if (head->value == target) {
        head = head->next;
        return;
    }

    Node<T>* cur = head;
    while (cur->next != NULL) {
        if (cur->next->value == target) {
            cur->next = cur->next->next;
            break;
        }
        cur = cur->next;
    };
}
template<typename T>
Iterator<T> SingleLinkedList<T>::erase(const Iterator<T>& p) {
    Iterator<T> it = Iterator(head);

    while (1) {
        Iterator<T> it2 = it;
        if (it2.v->next == NULL)return it;
        if (++it2 == p) break;
        ++it;
    }
    it.v->next = it.v->next->next;
    return it;
}
