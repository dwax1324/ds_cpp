#include <assert.h>
#include <bits/stdc++.h>
#include <stddef.h>
template <class T>
class Stack {
   private:
    class Node {
       public:
        T value;
        Node* next;
        Node() : value(0), next(NULL){};
        Node(T _value) : value(_value), next(NULL){};
    };

   public:
    Stack();
    ~Stack();
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
Stack<T>::Stack() : sz(0), head() {}
template <class T>
Stack<T>::~Stack() {
    while (size()) {
        pop();
    }
}
template <class T>
bool Stack<T>::empty() const { return size() == 0; }
template <class T>
unsigned Stack<T>::size() const { return sz; }

template <class T>
void Stack<T>::push(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    increaseSize();
}

template <class T>
void Stack<T>::pop() {
    assert(!empty());
    if (size() == 1)
        head = NULL;
    else
        head = head->next;
    decreaseSize();
}
template <class T>
T& Stack<T>::top() const {
    assert(!empty());
    return head->value;
}
