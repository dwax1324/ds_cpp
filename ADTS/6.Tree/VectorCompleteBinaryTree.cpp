

#include <vector>

template <typename T>
class VectorCompleteBinaryTree {
public:
    typedef typename std::vector<T>::iterator iter;
    VectorCompleteBinaryTree() {}
    int size() const { return vec.size(); }
    iter left(const iter& it) { return idxToit(itToIdx(it) * 2); }
    iter right(const iter& it) { return idxToit(itToIdx(it) * 2 + 1); }
    iter parent(const iter& it) { return idxToit(itToIdx(it) / 2); }
    bool hasLeft(const iter& it) const { return itToidx(it) * 2 <= size(); }
    bool hasRight(const iter& it) const { return itToidx(it) * 2 + 1 <= size(); }
    bool isRoot(const iter& it) const { return itToidx(it) == 0; }
    iter root() { return vec.begin(); }
    iter last() { return --vec.end(); }
    void insert(const T& value) { vec.push_back(value); }
    void pop() { vec.pop_back(); }
    void swap(const iter& it1, const iter& it2) {
        T temp = *it1;
        *it1 = *it2;
        *it2 = temp;
    }

private:
    std::vector<T> vec;
    int itToIdx(const iter& it) { return it - vec.begin(); }
    iter idxToit(int i) { return vec.begin() + i; }
};

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