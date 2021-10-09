#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // bst<int, int> tree;

    // 직선 체크
    // for (int i : {1, 2, 3, 4, 5}) {
    //     tree.insert(i, 1);
    //     tree.erase(i);
    // }
    // cout << tree.size() << '\n';
    // for (int i : {5, 4, 3, 2, 1}) {
    //     tree.insert(i, 1);
    //     tree.erase(i);
    // }
    // cout << tree.size() << '\n';
    // for (int i : {1, 2, 3, 4, 5}) {
    //     tree.insert(i, 1);
    // }
    // for (int i : {1, 2, 3, 4, 5}) {
    //     tree.erase(i);
    // }
    // cout << tree.size() << '\n';
    // for (int i : {5, 4, 3, 2, 1}) {
    //     tree.insert(i, 1);
    // }
    // for (int i : {5, 4, 3, 2, 1}) {
    //     tree.erase(i);
    // }
    // cout << tree.size() << '\n';
    // //
    // //
    // for (int i : {5, 3, 4, 1, 2}) {
    //     tree.insert(i, 1);
    // }
    // tree.erase(3);
    // tree.erase(2);
    // tree.erase(1);
    // tree.erase(5);
    // tree.erase(4);
    // tree.insert(1, 1);
    // cout << tree.min()->key;
    // cout << tree.max()->key;
    // tree.erase(1);
    // cout << tree.size() << '\n';
    //
    //  완벽이진트리
    // 순열테스트
    // vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // vector<int> perfect = {8, 4, 2, 6, 1, 3, 5, 7, 12, 11, 14, 9, 10, 13, 15};
    // do {
    //     for (auto x : v) cout << x << ' ';
    //     cout << '\n';
    //     // cout << '\n';
    //     for (int i : perfect) tree.insert(i, 1);
    //     // tree.preorder(), cout << '\n';
    //     for (int i : v) tree.erase(i);
    //     if (tree.size() != 0) break;
    //     // cout << tree.size() << '\n';
    // } while (next_permutation(v.begin(), v.end()));

    /*에러케이스 1*/
    // for (int i : {4, 2, 1, 3, 6, 5, 7}) tree.insert(i, 1);
    // for (int i : {1, 2, 3, 6, 7, 4, 5}) tree.erase(i);

    /* 에러케이스 2 (하나 안지워짐) */
    // for (int i : perfect) tree.insert(i, 1);
    // tree.preorder();
    // cout << '\n';
    // for (int i : {1, 2, 3, 4, 5, 6, 8, 7, 9, 10, 11, 12, 13, 14, 15}) {
    //     tree.erase(i);
    //     cout << tree.count(10);
    //     tree.preorder();
    //     // cout << tree.min()->key;
    //     cout << " deleted : " << i;
    //     cout << '\n';
    // }

    /* 에러케이스 3 */
    // for (int i : perfect) tree.insert(i, 1);
    // tree.preorder();
    // cout << '\n';
    // for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 11, 14, 15}) {
    //     tree.erase(i);
    //     cout << tree.count(11) << " @";
    //     // cout << tree.count(10);
    //     tree.preorder();
    //     cout << " deleted : " << i;
    //     // cout << tree.min()->key;
    //     cout << '\n';
    // }
}