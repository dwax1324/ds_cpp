/*
    GOOD^^
    search, insert, delete
    successor
*/

#include <bits/stdc++.h>

#include <limits>
using namespace std;
template <class K, class V>
class bst
{
public:
    // class NODE
    class Node
    {
    public:
        K key;
        V value;

        Node *left, *right, *parent;
        ~Node()
        {
            if (left && left->parent == this)
                left->parent = NULL;
            if (right && right->parent == this)
                right->parent = NULL;
            if (parent && parent->key > key && parent->left && parent->left == this)
                parent->left = NULL;
            if (parent && parent->key < key && parent->right && parent->right == this)
                parent->right = NULL;
            left = right = parent = NULL;
        }
        Node(K k) : key(k), left(NULL), right(NULL), parent(NULL) {}
        Node(K k, V v) : key(k), value(v), left(NULL), right(NULL), parent(NULL) {}
    };
    class Iterator
    {
    public:
        Node *ptr;
        Iterator(Node *_p) : ptr(_p) {}
        Node *operator*() const { return ptr; };
        bool operator==(const Iterator &_p) const { return ptr == _p.ptr; };
        bool operator!=(const Iterator &_p) const { return ptr != _p.ptr; };
        Iterator &operator++();
    };
    // BEGIN,END
    Iterator begin() { return Iterator(min()); }
    Iterator end() { return Iterator(max()); } // inclusive

    bst() : root(), _size(0) {}
    // SIZE
    int size() { return _size; }
    V &operator[](K _key)
    {
        return find(_key)->value;
    }
    // successor
    Node *successor(Node *cur)
    {
        if (cur->right)
        { // right subtree's leftmost node (move down left chain)
            cur = cur->right;
            while (cur->left)
                cur = cur->left;
            return cur;
        }
        else
        { // move up untill parent is smaller than cur (move up right chain)
            Node *parent = cur->parent;
            while (parent && parent->right == cur)
            {
                cur = parent, parent = cur->parent;
            }
            cur = parent;
        }
        return cur;
    }
    // MIN
    Node *min()
    {
        assert(root != NULL);
        Node *cur = root;
        while (cur->left)
            cur = cur->left;
        return cur;
    };
    Node *min(Node *cur)
    {
        assert(root != NULL && cur != NULL);
        while (cur->left)
            cur = cur->left;
        return cur;
    };

    // MAX
    Node *max()
    {
        assert(root != NULL);
        Node *cur = root;
        while (cur->right)
            cur = cur->right;
        return cur;
    };
    Node *max(Node *cur)
    {
        assert(root != NULL && cur != NULL);
        while (cur->right)
            cur = cur->right;
        return cur;
    };

    //  FIND
    Node *find(K _key)
    {
        if (!count(_key))
        {
            Node *newNode = new Node(_key);
            insert(newNode);
            return newNode;
        }
        Node *cur = root;
        while (cur != NULL)
        {
            if (_key == cur->key)
                return cur;
            else if (_key > cur->key)
                cur = cur->right;
            else
                cur = cur->left;
        }
        return NULL;
    }

    // COUNT
    bool count(K _key)
    {
        Node *cur = root;
        while (cur != NULL)
        {
            if (_key == cur->key)
                return true;
            else if (_key > cur->key)
                cur = cur->right;
            else
                cur = cur->left;
        }
        return false;
    }

    // INSERT
    void insert(K _key, V _value) { insert(new Node(_key, _value)); }
    void insert(Node *newNode)
    {
        if (root == NULL)
        {
            root = newNode;
            _size++;
            return;
        }
        Node *cur = root;
        while (1)
        {
            if (newNode->key == cur->key)
            {
                destroy(newNode);
                return; // no duplicate
            }
            if (newNode->key > cur->key)
            {
                if (cur->right == NULL)
                {
                    cur->right = newNode;
                    cur->right->parent = cur;
                    _size++;
                    break;
                }
                cur = cur->right;
            }
            else
            {
                if (cur->left == NULL)
                {
                    cur->left = newNode;
                    cur->left->parent = cur;
                    _size++;
                    break;
                }
                cur = cur->left;
            }
        }
    };

    // ERASE
    void destroy(Node *byebye)
    {
        if (root == byebye)
            root = NULL;
        else
            delete byebye;
        _size--;
    }

    void erase(K _key)
    {
        if (!count(_key))
            return;
        Node *cur = find(_key);
        // cerr << cur->key << '\n';
        if (cur->left == NULL && cur->right == NULL)
        { // NO CHILD
            destroy(cur);
            return;
        }
        if (cur->left == NULL && cur->right != NULL)
        { // ONLY RIGHT
            if (cur == root)
            { //speical case: root
                root = cur->right;
                destroy(cur);
                return;
            }
            if (cur->key > cur->parent->key)
            { // if cur on the right
                cur->parent->right = cur->right;
                cur->right->parent = cur->parent;
                destroy(cur);
                return;
            }

            if (cur->key < cur->parent->key)
            { // if cur is on the left
                cur->parent->left = cur->right;
                cur->right->parent = cur->parent;
                destroy(cur);
                return;
            }
        }
        if (cur->left != NULL && cur->right == NULL)
        { // ONLY LEFT
            if (cur == root)
            { //speical case: root
                root = cur->left;
                destroy(cur);
                return;
            }
            // cerr << (cur->left != NULL) << ' ' << (cur->right == NULL) << ' ' << cur->key << '\n';
            if (cur->key > cur->parent->key)
            { // if cur on the right
                cur->parent->right = cur->left;
                cur->left->parent = cur->parent;
                destroy(cur);
                return;
            }

            if (cur->key < cur->parent->key)
            { // if cur is on the left
                cur->parent->left = cur->left;
                cur->left->parent = cur->parent;
                destroy(cur);
                return;
            }
        }

        // 2 CHILD
        // cerr << "@@ " << cur->key;
        Node *succ = successor(cur); // successor
        assert(succ->key > cur->key);
        K tempKey = succ->key;
        V tempValue = succ->value;
        if (succ->right)
        {
            succ->right->parent = succ->parent;
            if (succ->parent->key > succ->key)
            {
                /* 
                       ㅇ
                      /
                    ㅇ <- successor
                      \
                       ㅇ

            */
                succ->parent->left = succ->right;
            }
            else
            {
                /*
                    ㅇ
                      \
                       ㅇ <- successor
                        \
                         ㅇ

            */
                succ->parent->right = succ->right;
            }
        }
        destroy(succ);
        cur->key = tempKey, cur->value = tempValue;
        return;
    }

    void debug()
    {
        Node *cur = root;
        // cout << root->value;
        // cout << (cur->left == NULL) << ' ' << (cur->right == NULL) << '\n';
        while (cur != NULL)
        {
            cout << cur->key << '\n';
            cur = cur->right;
        }
    }

    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }

    void preorder(Node *cur)
    {
        if (cur == NULL)
            return;
        cout << "[" << cur->key << "]" << ' ';
        preorder(cur->left);
        preorder(cur->right);
    }
    void inorder(Node *cur)
    {
        if (cur == NULL)
            return;
        inorder(cur->left);
        cout << cur->key << ' ';
        inorder(cur->right);
    }
    void postorder(Node *cur)
    {
        if (cur == NULL)
            return;
        postorder(cur->left);
        postorder(cur->right);
        cout << cur->key << '\n';
    }

    Node *root;
    int _size;
};
template <class K, class V>
typename bst<K, V>::Iterator &bst<K, V>::Iterator::operator++()
{
    Node *cur = this->ptr;
    if (cur->right)
    { // right subtree's leftmost node (move down left chain)
        cur = cur->right;
        while (cur->left)
            cur = cur->left;
    }
    else
    { // move up untill parent is smaller than cur (move up right chain)
        Node *parent = cur->parent;
        while (parent->right == cur)
        {
            cur = parent, parent = cur->parent;
        }
        cur = parent;
    }
    this->ptr = cur;
    return *this;
};

#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    bst<int, int> tree;

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    vector<int> perfect = {8, 4, 2, 6, 1, 3, 5, 7, 12, 11, 14, 9, 10, 13, 15};
    int cnt = 0;
    do
    {
        for (auto x : perfect)
            tree.insert(x, 1);

        tree.preorder();
        cout << '\n';
        for (auto x : v)
        {
            tree.erase(x);
        }
        assert(tree.size() == 0);
    } while (next_permutation(v.begin(), v.end()) && cnt++ < 100);
    cout << cnt;
}