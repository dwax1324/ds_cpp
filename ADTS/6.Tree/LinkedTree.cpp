#include <assert.h>
#include <stddef.h>

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
/// vector END
/// node BEGIN

/// node END

// LinkedTree BEGIN

template <class T>
class LinkedTree {
public:
    class Node {
    public:
        Node* __parent;
        T __value;
        Vector<Node*> __children;
        Node() : __parent(NULL), __children(), __value(0) {}
        Node(T& _value) : __parent(NULL), __children(), __value(_value) {}
        Node* parent() const { return __parent; }
        void set_parent(Node* _parent) { __parent = _parent; }
        void set_child(Node* _child) { __children.push_back(_child); }
        Vector<Node*> children() const { return __children; }
        bool is_root() const { return __parent == NULL; }
        bool is_external() const { return children().size() == 0; }
        T& operator*() { return __value; }
    };

public:
    LinkedTree() : __size(0), nodes() {}
    void add_node() { nodes.push_back(new Node), __size++; }

public:
    Node __root;
    int __size;
    Vector<Node*> nodes;
};