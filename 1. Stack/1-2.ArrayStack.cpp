#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <new>
template <class T>
class ArrayStack {
    enum { DEF_CAPACITY = 100001 };

   public:
    ArrayStack();
    ArrayStack(int);
    ~ArrayStack();
    T& top() const;
    bool empty() const;
    unsigned size() const;
    void push(const T&);
    void pop();

   private:
    int* array;
    int capacity;
    int cursor;
};
template <class T>
ArrayStack<T>::ArrayStack() : capacity(DEF_CAPACITY), cursor(-1) {
    array = new int[capacity];
}
template <class T>
ArrayStack<T>::ArrayStack(int _capacity) : capacity(_capacity), cursor(-1) {
    assert(capacity >= 0 && capacity < INT_MAX);
    array = new int[capacity];
}
template <class T>
ArrayStack<T>::~ArrayStack() {}
template <class T>
bool ArrayStack<T>::empty() const { return size() == 0; }
template <class T>
unsigned ArrayStack<T>::size() const { return cursor + 1; }

template <class T>
void ArrayStack<T>::push(const T& value) {
    array[cursor++] = value;
    assert(size() < capacity);
}

template <class T>
void ArrayStack<T>::pop() {
    assert(cursor != -1);
    cursor--;
}
template <class T>
T& ArrayStack<T>::top() const {
    assert(!empty());
    return array[cursor - 1];
}
