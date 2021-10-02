## ADT

Singly Linked List

(head)......(tail)
ㅁ -> ㅁ -> ㅁ-> x

each node have

1.value, 2.pointer to the next node

#### class functions

Node:

    T value;
    Node<T>* next;
    Node() {};
    Node(T _value, Node* _next) :value(_value), next(_next) {};

SingleLinkedList:

    SinglyLinkedList();
    ~SinglyLinkedList();
    Iterator<T> begin() const;
    Iterator<T> end() const;
    bool empty() const;
    int size() const;
    const T& front() const;
    void addFront(const T&);
    void popFront();
    void remove(const T&); // remove by value
    Iterator<T> erase(const Iterator<T>&);
    void insert(const Iterator<T>&);

Iterator:

    T& operator*();
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&)const;
    Iterator& operator++();
    Node<T>* v;
    Iterator(Node<T>* u);


#### disclaimer

Codes are not secure!!!!
end() is very slow, takes O(N) time
erase() is not safe
size() is not implemented

#### testing:

https://www.acmicpc.net/problem/10818 passed
https://www.acmicpc.net/problem/10104 passed