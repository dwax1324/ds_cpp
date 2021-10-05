#include <assert.h>
#include <stddef.h>
template <class T>
class LinkedQueue {
    class CircleList {
       private:
        class Node {
           public:
            T value;
            Node* next;

            Node() : value(0), next(NULL) {}
            Node(T _value) : value(_value), next(NULL) {}
        };

       public:
        CircleList();
        ~CircleList();

        bool empty() const;
        int size() const;
        void push(const T&);
        void pop();
        const T& front() const;
        const T& back() const;
        void advance();

       private:
        unsigned length;
        Node* cursor;
    };

   public:
    LinkedQueue();
    ~LinkedQueue();
    int size() const;
    bool empty() const;
    const T& front() const;
    const T& back() const;
    void push(const T&);
    void pop();

   private:
    CircleList list;
    int sz;
};
template <class T>
LinkedQueue<T>::LinkedQueue() : list(), sz(0){};

template <class T>
LinkedQueue<T>::~LinkedQueue(){};

template <class T>
int LinkedQueue<T>::size() const {
    return sz;
};
template <class T>
bool LinkedQueue<T>::empty() const {
    return sz == 0;
};
template <class T>
const T& LinkedQueue<T>::front() const {
    assert(!empty());
    return list.front();
};
template <class T>
const T& LinkedQueue<T>::back() const {
    assert(!empty());
    return list.back();
};

template <class T>
void LinkedQueue<T>::push(const T& value) {
    list.push(value);
    list.advance();
    sz++;
};
template <class T>
void LinkedQueue<T>::pop() {
    assert(!empty());
    list.pop();
    sz--;
};

/// circle list BEGIN

//constructor, destructor
template <class T>
LinkedQueue<T>::CircleList::CircleList() : cursor() {}
template <class T>
LinkedQueue<T>::CircleList::~CircleList() {
    while (!empty()) pop();
}

template <class T>
bool LinkedQueue<T>::CircleList::empty() const { return cursor == NULL; }
template <class T>
int LinkedQueue<T>::CircleList::size() const { return length; }
template <class T>
const T& LinkedQueue<T>::CircleList::front() const {
    assert(!empty());
    return cursor->next->value;
};

template <class T>
const T& LinkedQueue<T>::CircleList::back() const {
    assert(!empty());
    return cursor->value;
};

template <class T>
void LinkedQueue<T>::CircleList::push(const T& value) {
    length++;
    Node* newNode = new Node(value);
    // list is empty
    if (cursor == NULL) {
        newNode->next = newNode;  // points to itself
        cursor = newNode;
        return;
    }

    // list is nonempty
    newNode->next = cursor->next;
    cursor->next = newNode;
    return;
}

template <class T>
void LinkedQueue<T>::CircleList::pop() {  // remove node after cursor
    assert(!empty());
    length--;
    if (cursor->next == cursor) {
        cursor = NULL;
    } else {
        cursor->next = cursor->next->next;
    }
    return;
};
template <class T>
void LinkedQueue<T>::CircleList::advance() {
    cursor = cursor->next;
}
//circle list END