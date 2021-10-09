/* SET

https://www.acmicpc.net/source/34118048 passed
https://www.acmicpc.net/problem/7785 failed..T_T erase problem..?



main functions
insert
count (== find,serch)
erase

erase 문제있음.. 디버깅못하ㅔㄱㅆ음...
*/

#include <assert.h>
#include <stddef.h>

#include <iostream>
template <class T>
class BinarySearchTree {
public:
    class Node {
    public:
        T value;
        Node *parent;
        Node *left;
        Node *right;
        Node(const T &val) : value(val), parent(NULL), left(NULL), right(NULL) {}
    };
    BinarySearchTree() : _size(0), root(NULL) {}

    int size() { return _size; }
    const T &max() {
        assert(size());
        Node *cur = root;
        while (cur->right != NULL) cur = cur->right;
        return cur->value;
    }
    const T &min() {
        assert(size());
        Node *cur = root;
        while (cur->left != NULL) cur = cur->left;
        return cur->value;
    }

    void insert(const T &newValue) {
        if (root == NULL) {
            root = new Node(newValue);
            root->parent = root;
            _size++;
            return;
        }
        insert(root, root, newValue);
    };
    // prev는 cur이전의 노드다.
    // cur이 null를 만나면 cur 값에따라 prev의 왼쪽,오른쪽에 삽입할지 결정한다.
    void insert(Node *cur, Node *prev, const T &newValue) {
        if (cur == NULL) {
            cur = new Node(newValue);
            cur->parent = prev;
            _size++;
            if (cur->value > prev->value) prev->right = cur;
            else
                prev->left = cur;
            return;
        }
        if (newValue == cur->value) return;  // no duplicate values
        else if (newValue < cur->value) {
            insert(cur->left, cur, newValue);
        } else
            insert(cur->right, cur, newValue);
    };

    bool count(const T &target) { return count(root, target); }
    bool count(Node *cur, const T &target) {
        if (cur == NULL) return false;

        if (target == cur->value) return true;
        else if (target > cur->value)
            return count(cur->right, target);
        else
            return count(cur->left, target);
    }

    Node *find(Node *cur, const T &target) {
        if (cur == NULL) return NULL;

        if (target == cur->value) return cur;
        else if (target > cur->value)
            return find(cur->right, target);
        else
            return find(cur->left, target);
    }

    void makeRoot(Node *cur) {
        root->parent = root;
    };

    bool eraser(Node *cur, Node *prev, const T &target) {
        bool ret = false;
        if (cur->left == NULL && cur->right == NULL) {  // case 1: no child. just delete
                                                        // std::cerr << "@" << cur->value << ' ' << prev->value << "@" << '\n';
            // std::cerr << cur->parent->value << ' ' << cur->value << '\n';
            if (cur->parent == cur) root = NULL;
            else if (cur->value > prev->value) {
                prev->right = NULL;
            } else
                prev->left = NULL;
            // delete cur;
            _size--;
            ret |= true;
        } else if (cur->left == NULL) {  // case 2: only one child. connect previous and after node
            // std::cerr << 1;
            if (cur->parent == cur) root = cur->right, makeRoot(cur);
            else if (cur->value > prev->value) {
                prev->right = cur->right;
                cur->right->parent = prev;
            } else {
                prev->left = cur->right;
                cur->right->parent = prev;
            }
            _size--;
            // delete cur;
            ret |= true;
        } else if (cur->right == NULL) {  // case 2: only one child. connect previous and after node
            if (cur->parent == cur) root = cur->left, makeRoot(cur);
            else if (cur->value > prev->value) {
                prev->right = cur->left;
                cur->left->parent = prev;
            } else {
                prev->left = cur->left;
                cur->left->parent = prev;
            }
            // delete cur;
            _size--;
            ret |= true;
        };
        return ret;
    };

    void erase(const T &target) {
        erase(root, target);
    }
    void erase(Node *cur, const T &target) {
        if (cur == NULL) return;
        if (cur->value == target) {
            if (!eraser(cur, cur->parent, target)) {
                // case 3: two child.
                //         find the target's successor,( it must exist because target have two child)
                //         replace the target'value with successor's value, delete successor (successor have 0 or 1 child so it's case1 or case2)
                //         (after replacement BST rule won't break because left subtree is still lesser, right subtree is still greater)
                Node *tar = find(root, target);
                Node *succ = successor(tar);
                // std::cerr << "@@" << tar->value << ' ' << succ->value << "@@" << '\n';
                tar->value = succ->value;  // replacement

                Node *prev = succ->parent;
                if (prev->value > succ->value) prev->left = NULL;
                else
                    prev->right = NULL;
                _size--;
                // delete succ;
            }
            return;
        }
        if (cur->value > target)
            erase(cur->left, target);
        else
            erase(cur->right, target);
    }

    void print(int n) {
        if (n == 0) preorder(root);
        if (n == 1) inorder(root);
        if (n == 2) postorder(root);

        // Node *t = find(root, n);
        // while (t->parent != t) {
        //     std::cerr << t->value << ' ';
        //     t = t->parent;
        // }
    };

private:
    int _size;
    Node *successor(Node *target);
    void preorder(Node *cur);
    void inorder(Node *cur);
    void postorder(Node *cur);
    Node *root;
};

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::successor(Node *target) {
    // 3 cases
    if (target->value == max()) return target;  // target is max() => no successor

    if (target->right != NULL) {  // if right subtree exist, return right subtree's min node
        Node *cur = target->right;
        while (cur->left != NULL) cur = cur->left;
        return cur;
    } else {  // if right subtree does not exist, return go up untill cur is not prev's right child
        Node *cur = target;
        Node *prev = target->parent;
        while (prev->right == cur) {
            cur = prev;
            prev = prev->parent;
        }
        return prev;
    }
}

template <class T>
void BinarySearchTree<T>::preorder(Node *cur) {
    if (cur == NULL) return;
    std::cout << cur->value << ' ';
    preorder(cur->left);
    preorder(cur->right);
}

template <class T>
void BinarySearchTree<T>::inorder(Node *cur) {
    if (cur == NULL) return;
    inorder(cur->left);
    std::cout << cur->value << ' ';
    inorder(cur->right);
}

template <class T>
void BinarySearchTree<T>::postorder(Node *cur) {
    if (cur == NULL) return;
    postorder(cur->left);
    postorder(cur->right);
    std::cout << cur->value << ' ';
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
#define int long long
using namespace std;

int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin.tie(0)->sync_with_stdio(0);
    BinarySearchTree<string> st;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sort(all(s));
        st.insert(s);
    }
    cout << st.size() << '\n';
}
