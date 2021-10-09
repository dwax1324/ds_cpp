
#include <stddef.h>

class BinaryTree {
public:
    class Node {
    public:
        int value;
        Node *left;
        Node *right;
        Node(int _val = 0) : value(_val), left(NULL), right(NULL) {}
    };

    Node *getRoot() {
        return root;
    }

    void addRoot(int num) {
        root = new Node(num);
    };
    void add(Node *, int parent, int left, int right);
    void preorder(Node *);
    void inorder(Node *);
    void postorder(Node *);

private:
    Node *root;
};

void BinaryTree::add(Node *cur, int parent, int left, int right) {
    if (cur == NULL) return;
    if (cur->value == parent) {
        if (left != -1)
            cur->left = new Node(left);
        if (right != -1)
            cur->right = new Node(right);
        return;
    }
    add(cur->left, parent, left, right);
    add(cur->right, parent, left, right);
}

#include <bits/stdc++.h>
void BinaryTree::preorder(Node *cur) {
    if (cur == NULL) return;
    std::cout << char(cur->value + 'A');
    preorder(cur->left);
    preorder(cur->right);
}
void BinaryTree::inorder(Node *cur) {
    if (cur == NULL) return;
    inorder(cur->left);
    std::cout << char(cur->value + 'A');
    inorder(cur->right);
}

void BinaryTree::postorder(Node *cur) {
    if (cur == NULL) return;
    postorder(cur->left);
    postorder(cur->right);
    std::cout << char(cur->value + 'A');
}
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    BinaryTree tree;

    int n;
    cin >> n;
    tree.addRoot(0);
    while (n--) {
        char a[3];
        for (int i = 0; i < 3; i++) cin >> a[i];
        int b[3];
        for (int i = 0; i < 3; i++) {
            if (a[i] == '.') b[i] = -1;
            else
                b[i] = a[i] - 'A';
        }
        tree.add(tree.getRoot(), b[0], b[1], b[2]);
    }
    tree.preorder(tree.getRoot());
    cout << '\n';
    tree.inorder(tree.getRoot());
    cout << '\n';
    tree.postorder(tree.getRoot());
}