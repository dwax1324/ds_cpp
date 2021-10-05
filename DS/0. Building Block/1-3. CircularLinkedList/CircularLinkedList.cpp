#include <assert.h>
#include <stddef.h>  // for NULL
template <class T>
class CircularLinkedList {
   private:
    class Node {
       public:
        T value;
        Node* next;

        Node() : value(0), next(NULL) {}
        Node(T _value) : value(_value), next(NULL) {}
    };

   public:
    CircularLinkedList();
    ~CircularLinkedList();

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

//constructor, destructor
template <class T>
CircularLinkedList<T>::CircularLinkedList() : cursor() {}
template <class T>
CircularLinkedList<T>::~CircularLinkedList() {
    while (!empty()) pop();
}

template <class T>
bool CircularLinkedList<T>::empty() const { return cursor == NULL; }
template <class T>
int CircularLinkedList<T>::size() const { return length; }
template <class T>
const T& CircularLinkedList<T>::front() const {
    assert(!empty());
    return cursor->next->value;
};

template <class T>
const T& CircularLinkedList<T>::back() const {
    assert(!empty());
    return cursor->value;
};
#include <iostream>
template <class T>
void CircularLinkedList<T>::push(const T& value) {
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
void CircularLinkedList<T>::pop() {  // remove node after cursor
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
void CircularLinkedList<T>::advance() {
    cursor = cursor->next;
}

using namespace std;
int main() {
    CircularLinkedList<string> myList;
    myList.push("Staying Alive");
    myList.push("Le Freak");
    myList.push("Jive Talkin");
    cout << myList.front() << ' ' << myList.back() << '\n';
    myList.advance();
    cout << myList.front() << ' ' << myList.back() << '\n';
    myList.advance();
    cout << myList.front() << ' ' << myList.back() << '\n';
    myList.pop();
    cout << myList.front() << ' ' << myList.back() << '\n';
    return EXIT_SUCCESS;
}