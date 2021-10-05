

#include <bits/stdc++.h>

#include <vector>

template <class T>
class Heap {
public:
    std::vector<T> _array;

    void push(int __value) {
        _array.push_back(__value);
        int idx = size() - 1;
        int parent = idx / 2;
        while (idx > 0 && _array[idx / 2] < _array[idx]) {
            parent = idx / 2;
            std::swap(_array[parent], _array[idx]);
            idx = parent;
        }
    }
    void pop() {
        std::swap(_array[0], _array[size() - 1]);
        _array.pop_back();
        heapify(0);
    };

    void heapify(int __idx) {
        int left = __idx * 2, right = __idx * 2 + 1;
        if (left >= size() && right >= size()) return;
        int k;
        if (right >= size()) {
            k = left;
        } else
            k = _array[left] > _array[right] ? left : right;
        if (_array[__idx] >= _array[k]) return;
        std::swap(_array[__idx], _array[k]);
        heapify(k);
        // // // iterative
        // // int left = __idx * 2, right = __idx * 2 + 1;
        // // while (__idx * 2 < size() && __idx * 2 + 1 < size()) {
        // //     left = __idx * 2, right = __idx * 2 + 1;
        // //     int k;
        // //     if (right >= size()) k = left;
        // //     else
        // //         k = _array[left] > _array[right] ? left : right;
        // //     if (_array[__idx] >= _array[k]) return;
        // //     std::swap(_array[__idx], _array[k]);
        // //     __idx = k;
        // }
    }
    int size() {
        return _array.size();
    }

    int top() {
        assert(size() != 0);
        return _array.front();
    }
};

#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Heap<int> heap;

    int n;
    cin >> n;
    while (n--) {
        int a;
        cin >> a;
        if (a) heap.push(a);
        else {
            if (heap.size() == 0) {
                cout << 0 << '\n';
                continue;
            }
            cout << heap.top() << '\n';
            heap.pop();
        }
    }
}