#include <assert.h>
#include <stddef.h>
// iterator BEGIN
template <class T>
class Iterator {
public:
    Iterator(){};
    T& operator*();
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    Iterator& operator++();
    Iterator& operator--();
    T* ptr;
};

template <class T>
T& Iterator<T>::operator*() {
    // assert ptr is not head and not tail
    assert(ptr->prev != NULL && ptr->next != NULL);
    return ptr->value;
}

template <class T>
bool Iterator<T>::operator==(const Iterator& it) const { return ptr == it.ptr; }
template <class T>
bool Iterator<T>::operator!=(const Iterator& it) const { return ptr != it.ptr; }
template <class T>
Iterator<T>& Iterator<T>::operator++() {
    assert(ptr->next != NULL);
    ptr = ptr->next;
    return *this;
}
template <class T>
Iterator<T>& Iterator<T>::operator--() {
    assert(ptr->prev != NULL);
    ptr = ptr->prev;
    return *this;
}
// iterator END

// vector BEGIN
template <class T>
class Vector {
public:
    enum { DEFAULT_CAPACITY = 10 };
    Vector();
    ~Vector();
    unsigned size() const;
    bool empty() const;
    const T& front() const;
    const T& back() const;
    void push_back(const T&);
    void pop_back();
    void insert(int, const T&);
    void erase(int);
    void reserve(int);
    const T& operator[](int);

private:
    int __capacity;
    int __size;
    T* array;
};
template <class T>  // constructor
Vector<T>::Vector() : __size(0), __capacity(DEFAULT_CAPACITY) {
    array = new T[__capacity];
}
template <class T>  // desturctor
Vector<T>::~Vector() {
    if (array != NULL) delete[] array;
}

template <class T>  // size
unsigned Vector<T>::size() const { return __size; }
template <class T>  // empty
bool Vector<T>::empty() const { return size() == 0; }
template <class T>
const T& Vector<T>::operator[](int i) {  // operator []
    assert(i >= 0 && i < size());
    return array[i];
}
template <class T>  // front
const T& Vector<T>::front() const {
    assert(!empty());
    return array[0];
}
template <class T>  // back
const T& Vector<T>::back() const {
    assert(!empty());
    return array[__size - 1];
}
template <class T>  // reserve
void Vector<T>::reserve(int reserve_size) {
    if (__capacity >= reserve_size) return;
    T* new_array = new T[reserve_size];
    for (int i = 0; i < __size; i++) new_array[i] = array[i];
    if (array != NULL) delete[] array;
    array = new_array;
    __capacity = reserve_size;
}

template <class T>  // insert
void Vector<T>::insert(int index, const T& value) {
    if (__size == __capacity) { reserve(__capacity * 2); }

    for (int i = size(); i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
    __size++;
}
template <class T>  // erase
void Vector<T>::erase(int index) {
    for (int i = index; i < size(); i++) {
        array[i] = array[i + 1];
    }
    __size--;
}
template <class T>  // push_back
void Vector<T>::push_back(const T& value) {
    if (__size == __capacity) { reserve(__capacity * 2); }
    array[__size] = value;
    __size++;
}
template <class T>  // pop_back
void Vector<T>::pop_back() {
    assert(!empty());
    __size--;
}
// vector END