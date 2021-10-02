#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

#include "1. LinkedList/1-1/1-1. SinglyLinkedList.hpp"
int main() {

    cin.tie(0)->sync_with_stdio(0);

    SinglyLinkedList<int> list;

    list.addFront(1);
    list.addFront(2);
    list.addFront(3);

    list.remove(4);

    while (!list.empty()) {

        cout << list.front() << ' ';
        list.popFront();
    }

}