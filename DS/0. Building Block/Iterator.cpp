#include <stddef.h>
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

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin.tie(0)->sync_with_stdio(0);
}