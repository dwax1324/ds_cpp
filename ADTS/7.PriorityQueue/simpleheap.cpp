#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

class minheap {
public:
    int capacity;
    minheap(int _a) : capacity(_a), sz(0) {
        arr = new int[capacity];
    };

    // from top to down , choose higher prioritiy one
    void heapify(int i, int len) {
        int idx = i;
        while (1) {
            int p = idx, l = i * 2 + 1, r = i * 2 + 2;
            if (l < len && arr[p] > arr[l]) p = l;
            if (r < len && arr[p] > arr[r]) p = r;
            if (p == idx) break;
            swap(arr[idx], arr[p]);
            idx = p;
        }
    }
    // O(n), i think not neccessary, just push and pop
    void construct(int *temp, int n) {
        for (int i = 0; i < n; i++) arr[i] = temp[i];
        sz = n;
        for (int i = sz / 2 - 1; i >= 0; i--) {
            heapify(i, sz);
        }
    };
    void push(int val) {
        arr[sz] = val;
        int idx = sz;
        sz++;
        while (idx) {
            int pa = (idx - 1) / 2;
            if (arr[pa] > arr[idx]) swap(arr[pa], arr[idx]);
            idx = pa;
        }
    }
    void pop() {
        swap(arr[0], arr[sz - 1]);
        sz--;
        heapify(0, sz);
    }
    int size() { return sz; }
    int top() {
        return arr[0];
    }

private:
    int *arr;
    int sz;
};