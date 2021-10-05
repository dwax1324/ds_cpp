#include <assert.h>
#include <stddef.h>
template <class T>
class LinkedStack {
   private:
    class Node {
       public:
        T value;
        Node* next;
        Node() : value(0), next(NULL){};
        Node(T _value) : value(_value), next(NULL){};
    };

   public:
    LinkedStack();
    ~LinkedStack();
    T& top() const;
    bool empty() const;
    unsigned size() const;
    void push(const T&);
    void pop();

   private:
    Node* head;
    unsigned sz;  // size
    void increaseSize() { sz++; };
    void decreaseSize() { sz--; };
};
template <class T>
LinkedStack<T>::LinkedStack() : sz(0), head() {}
template <class T>
LinkedStack<T>::~LinkedStack() {
    while (size()) {
        pop();
    }
}
template <class T>
bool LinkedStack<T>::empty() const { return size() == 0; }
template <class T>
unsigned LinkedStack<T>::size() const { return sz; }

template <class T>
void LinkedStack<T>::push(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    increaseSize();
}

template <class T>
void LinkedStack<T>::pop() {
    assert(!empty());
    if (size() == 1)
        head = NULL;
    else
        head = head->next;
    decreaseSize();
}
template <class T>
T& LinkedStack<T>::top() const {
    assert(!empty());
    return head->value;
}
