#include <assert.h>
#include <stddef.h>

template <class T>
class ArrayQueue {
    enum { MAX_CAPCITY = 100000 };

public:
    ArrayQueue();
    ArrayQueue(int);
    ~ArrayQueue();
    T& front();
    T& back();
    bool empty();
    int size();
    void push(const T&);
    void pop();

private:
    int* array;
    int m_capacity;
    int m_size;
    int m_front;
    int m_rear;
};
template <class T>
ArrayQueue<T>::ArrayQueue() : m_capacity(MAX_CAPCITY), m_size(0), m_front(0), m_rear(0) {
    array = new int[m_capacity];
}
template <class T>
ArrayQueue<T>::ArrayQueue(int cap) : m_capacity(cap), m_size(0), m_front(0), m_rear(0) {
    array = new int[m_capacity];
}
template <class T>
ArrayQueue<T>::~ArrayQueue() {}

template <class T>
bool ArrayQueue<T>::empty() {
    return size() == 0;
}
template <class T>
int ArrayQueue<T>::size() {
    return m_size;
}

template <class T>
T& ArrayQueue<T>::back() {
    assert(size() != 0);
    return array[m_rear == 0 ? m_capacity - 1 : m_rear - 1];
}
template <class T>
T& ArrayQueue<T>::front() {
    assert(size() != 0);
    return array[m_front];
}

template <class T>
void ArrayQueue<T>::push(const T& value) {
    assert(size() < m_capacity);
    array[m_rear] = value;
    m_rear = (m_rear + 1) % m_capacity;
    m_size++;
}
template <class T>
void ArrayQueue<T>::pop() {
    assert(size() != 0);
    m_front = (m_front + 1) % m_capacity;
    m_size--;
}