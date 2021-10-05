#include <assert.h>

#include <vector>
template <typename T>
class VectorCompleteBinaryTree {
public:
    typedef typename std::vector<T>::iterator iter;
    VectorCompleteBinaryTree() : vec(1) {}
    int size() const { return vec.size() - 1; }
    iter left(const iter& it) { return idxToIt(itToIdx(it) * 2); }
    iter right(const iter& it) { return idxToIt(itToIdx(it) * 2 + 1); }
    iter parent(const iter& it) { return idxToIt(itToIdx(it) / 2); }
    bool hasLeft(const iter& it) { return itToIdx(it) * 2 <= size(); }
    bool hasRight(const iter& it) { return itToIdx(it) * 2 + 1 <= size(); }
    bool isRoot(const iter& it) { return (itToIdx(it) == 1); }
    iter begin() { return idxToIt(1); }
    iter end() { return idxToIt(size()); }
    void push(const T& value) { vec.push_back(value); }
    void pop() { vec.pop_back(); }
    void swap(const iter& it1, const iter& it2) {
        T temp = *it1;
        *it1 = *it2;
        *it2 = temp;
    }

private:
    std::vector<T> vec;
    int itToIdx(const iter& it) { return it - vec.begin(); }
    iter idxToIt(int i) { return vec.begin() + i; }
};

template <typename T, typename C>
class HeapPriorityQueue {
    typedef typename VectorCompleteBinaryTree<T>::iter iter;

public:
    HeapPriorityQueue() {}
    int size() const;
    bool empty() const;
    void push(const T&);
    const T& top();
    void pop();

private:
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
    VectorCompleteBinaryTree<T> tree;
    C isLess;
};

template <typename T, typename C>
int HeapPriorityQueue<T, C>::size() const { return tree.size(); }

template <typename T, typename C>
bool HeapPriorityQueue<T, C>::empty() const { return size() == 0; }

template <typename T, typename C>
const T& HeapPriorityQueue<T, C>::top() { return *(tree.begin()); }

template <typename T, typename C>
void HeapPriorityQueue<T, C>::push(const T& value) {
    tree.push(value);
    iter current = tree.end();
    while (!tree.isRoot(current)) {
        iter parent = tree.parent(current);
        if (!isLess(*current, *parent)) break;
        tree.swap(current, parent);
        current = parent;
    }
}

template <typename T, typename C>
void HeapPriorityQueue<T, C>::pop() {
    assert(size() > 0);
    if (size() == 1) tree.pop();
    else {
        iter root = tree.begin();
        tree.swap(root, tree.end());
        tree.pop();
        while (tree.hasLeft(root)) {
            iter v = tree.left(root);
            if (tree.hasRight(root) && isLess(*(tree.right(root)), *v)) v = tree.right(root);
            if (isLess(*v, *root)) {
                tree.swap(root, v);
                root = v;
            } else
                break;
        }
    }
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

class cmp {
public:
    bool operator()(const int a, const int b) const {
        if (abs(a) == abs(b)) return a < b;
        return abs(a) < abs(b);
    }
};