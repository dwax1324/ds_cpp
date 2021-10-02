#include <iostream>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

#include "SingleLinkedList.hpp"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    SingleLinkedList<int> list;

    for (int i = 1; i <= 10; i++)list.pushFront(i);
    Iterator<int> it = list.begin();
    while (it != list.end()) {
        cout << *it << ' ';
        ++it;
    }
    cout << '\n';
    while (!list.empty()) { cout << list.front() << ' '; list.popFront(); }

}