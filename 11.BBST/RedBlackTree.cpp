#include <stddef.h>
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

template <class K, class V>
class RBtree
{

public:
    enum
    {
        RED = 1,
        BLACK = 0
    };
    class Node
    {
    public:
        K key;
        V value;
        Node *parent;
        Node *left;
        Node *right;
        bool color;
        ~Node();
        Node() {}
        Node(K k) : key(k), parent(NULL), color(RED), left(NULL), right(NULL) {}
        Node(K k, V v) : key(k), value(v), parent(NULL), color(RED), left(NULL), right(NULL) {}
    };
    RBtree() : root(NULL), _size(0) {}
    void destroy(Node *);
    bool count(K);
    Node *getParent(Node *);
    Node *getGrandParent(Node *);
    Node *getSibling(Node *);
    Node *getUncle(Node *);
    Node *getCloseNephew(Node *);
    Node *getDistantNewphew(Node *);
    Node *find(K);
    Node *getSuccesor(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void insert(Node *);
    void insertCase1(Node *);
    void insertCase2(Node *);
    void insertCase3(Node *);
    void insertCase4(Node *);
    void insertCase5(Node *);
    void erase(K);
    void erase(Node *); // = delete
    void deleteCase1(Node *);
    void deleteCase2(Node *);
    void deleteCase3(Node *);
    void deleteCase4(Node *);
    void deleteCase5(Node *);
    void deleteCase6(Node *);
    bool isLeaf(Node *cur) { return cur != root && cur == NULL; } // 모든 leaf 노드는 NULL
    void insert(K key, V value) { insert(new Node(key, value)); }
    int size() { return _size; }
    Node *root;
    int _size;

    void inorder() { inorder(root); }
    void inorder(Node *cur)
    {
        if (cur == NULL)
            return;
        inorder(cur->left);
        cout << cur->key << ' ';
        inorder(cur->right);
    }
    void preorder() { preorder(root); }
    void preorder(Node *cur)
    {
        if (cur == NULL)
            return;
        cout << cur->key << ' ';
        preorder(cur->left);
        preorder(cur->right);
    }
};
// ! helper function BEGIN
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::find(K key)
{
    Node *cur = root;
    while (cur != NULL)
    {
        if (cur->key == key)
            return cur;
        else if (cur->key > key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return NULL;
}
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::getSuccesor(Node *cur)
{
    if (cur->right)
    {
        cur = cur->right;
        while (cur->left)
            cur = cur->left;
        return cur;
    }
    else
    {
        Node *parent = cur->parent;
        while (parent && parent->right == cur)
        {
            cur = parent, parent = cur->parent;
        }
        cur = parent;
    }
    return cur;
}
template <class K, class V>
RBtree<K, V>::Node::~Node()
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
template <class K, class V>
bool RBtree<K, V>::count(K key)
{
    Node *cur = root;
    while (cur != NULL)
    {
        if (cur->key == key)
            return true;
        else if (cur->key > key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return false;
}
template <class K, class V>
void RBtree<K, V>::destroy(Node *byebye)
{
    if (byebye == root)
        root = NULL;

    delete byebye;
}
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::getParent(Node *cur)
{
    if (cur == NULL)
        return NULL;
    return cur->parent;
}
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::getGrandParent(Node *cur)
{
    return getParent(getParent(cur));
}
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::getSibling(Node *cur)
{
    assert(cur != NULL);
    Node *parent = getParent(cur);
    if (cur == parent->left)
        return parent->right;
    else
        return parent->left;
}
template <class K, class V>
typename RBtree<K, V>::Node *RBtree<K, V>::getUncle(Node *cur)
{
    assert(cur != NULL);
    return getSibling(getParent(cur));
}
template <class K, class V>
void RBtree<K, V>::rotateLeft(Node *cur)
{
    Node *child = cur->right;
    Node *parent = cur->parent;
    if (child->left != NULL)
    {
        child->left->parent = cur;
    }
    cur->right = child->left;
    cur->parent = child;
    child->left = cur;
    child->parent = parent;

    if (parent != NULL)
    {
        if (parent->left == cur)
            parent->left = child;
        else
            parent->right = child;
    }
}
template <class K, class V>
void RBtree<K, V>::rotateRight(Node *cur)
{
    Node *child = cur->left;
    Node *parent = cur->parent;

    if (child->right != NULL)
        child->right->parent = cur;

    cur->left = child->right;
    cur->parent = child;
    child->right = cur;
    child->parent = parent;

    if (parent != NULL)
    {
        if (parent->right == cur)
            parent->right = child;
        else
            parent->left = child;
    }
}

// ! helper function END

// ! INSERTION BEGIN
template <class K, class V>
void RBtree<K, V>::insert(Node *newNode)
{
    Node *cur = root;
    while (cur != NULL)
    {
        if (cur->key == newNode->key)
        {
            destroy(newNode);
            return;
        }
        else if (cur->key > newNode->key)
        {
            if (cur->left == NULL)
                break;
            cur = cur->left;
        }
        else
        {
            if (cur->right == NULL)
                break;
            cur = cur->right;
        }
    }

    if (cur == NULL)
    {
        root = newNode;
        cur = root;
    }
    else
    {
        if (cur->key > newNode->key)
        {
            cur->left = newNode;
            newNode->parent = cur;
            cur = cur->left;
        }
        else
        {
            cur->right = newNode;
            newNode->parent = cur;
            cur = cur->right;
        }
    }
    _size++;
    insertCase1(cur);
};
template <class K, class V>
void RBtree<K, V>::insertCase1(Node *newNode)
{
    if (newNode->parent == NULL)
    {
        newNode->color = BLACK;
        return;
    }

    insertCase2(newNode);
}
template <class K, class V>
void RBtree<K, V>::insertCase2(Node *newNode)
{
    if (newNode->parent->color == BLACK)
    {
        return;
    }

    insertCase3(newNode);
}
template <class K, class V>
void RBtree<K, V>::insertCase3(Node *newNode)
{
    // cerr << "case3\n";
    Node *parent = getParent(newNode);
    Node *uncle = getUncle(newNode);
    Node *grandParent = getGrandParent(newNode);
    if ((uncle != NULL) && (uncle->color == RED))
    {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandParent->color = RED;
        insertCase1(grandParent);
        return;
    }

    insertCase4(newNode);
}
template <class K, class V>
void RBtree<K, V>::insertCase4(Node *newNode)
{
    Node *parent = getParent(newNode);
    Node *grandParent = getGrandParent(newNode);
    if ((newNode == parent->right) && (parent == grandParent->left))
    {
        rotateLeft(parent);
        newNode = newNode->left;
    }
    else if ((newNode == parent->left) && (parent == grandParent->right))
    {
        rotateRight(parent);
        newNode = newNode->right;
    }

    insertCase5(newNode);
}
template <class K, class V>
void RBtree<K, V>::insertCase5(Node *newNode)
{
    // cerr << "case5\n";
    Node *parent = getParent(newNode);
    Node *grandParent = getGrandParent(newNode);
    parent->color = BLACK;
    grandParent->color = RED;
    if (grandParent == root)
        root = parent;
    if (newNode == parent->left)
        rotateRight(grandParent);
    else
        rotateLeft(grandParent);
}
//!INSERTION END

//!DELETION BEGIN
template <class K, class V>
void RBtree<K, V>::erase(K key) { erase(find(key)); }
template <class K, class V>
void RBtree<K, V>::erase(Node *cur)
{

    if (cur == NULL || !count(cur->key))
        return;
    Node *toDelete = NULL;
    Node *child = NULL;
    if (cur->left && cur->right)
    {
        toDelete = getSuccesor(cur);
    }
    else
    {
        toDelete = cur;
    }

    if (toDelete->left == NULL)
        child = toDelete->right;
    else
        child = toDelete->left;

    if (child)
        child->parent = toDelete->parent;

    if (toDelete->parent == NULL)
    {
        root = child;
    }
    else
    {
        if (toDelete == toDelete->parent->left)
            toDelete->parent->left = child;
        else
            toDelete->parent->right = child;
    }
    if (cur != toDelete)
    {
        cur->key = toDelete->key;
        cur->value = toDelete->value;
    }

    destroy(toDelete);
    _size--;
    if (toDelete->color == RED)
    {
        return;
    }

    if (child != NULL && toDelete->color == BLACK && child->color == RED)
    {
        child->color = RED;
        return;
    }

    deleteCase1(child);
}
template <class K, class V>

void RBtree<K, V>::deleteCase1(Node *cur)
{
    if (cur == NULL || cur->parent == NULL)
    {
        return;
    }
    deleteCase2(cur);
}
template <class K, class V>

void RBtree<K, V>::deleteCase2(Node *cur)
{
    Node *sibling = getSibling(cur);

    if (sibling->color == RED)
    {
        cur->parent->color = RED;
        sibling->color = BLACK;
        if (cur == cur->parent->left)
            rotateLeft(cur->parent);
        else
            rotateRight(cur->parent);
    }
    deleteCase3(cur);
}
template <class K, class V>

void RBtree<K, V>::deleteCase3(Node *cur)
{
    Node *sibling = getSibling(cur);

    bool A = cur->parent->color == BLACK;
    bool B = sibling->color == BLACK;
    bool C = sibling->left == NULL || sibling->left->color == BLACK;
    bool D = sibling->right == NULL || sibling->right->color == BLACK;
    if (A && B && C && D)
    {
        sibling->color = RED;
        deleteCase1(cur->parent);
        return;
    }
    deleteCase4(cur);
}
template <class K, class V>

void RBtree<K, V>::deleteCase4(Node *cur)
{
    Node *sibling = getSibling(cur);

    bool A = cur->parent->color == RED;
    bool B = sibling->color == BLACK;
    bool C = sibling->left == NULL || sibling->left->color == BLACK;
    bool D = sibling->right == NULL || sibling->right->color == BLACK;
    if (A && B && C && D)
    {
        sibling->color = RED;
        cur->parent->color = BLACK;
        return;
    }
    deleteCase5(cur);
}
template <class K, class V>

void RBtree<K, V>::deleteCase5(Node *cur)
{
    Node *sibling = getSibling(cur);
    if (sibling->color == BLACK)
    {
        bool a = cur == cur->parent->left;
        bool b = sibling->right == NULL || sibling->right->color == BLACK;
        bool c = sibling->left && sibling->left->color == RED;
        if (a && b && c)
        {
            sibling->color = RED;
            sibling->left->color = BLACK;
            rotateRight(sibling);
        }
        else
        {
            bool A = cur == cur->parent->right;
            bool B = sibling->right && sibling->right->color == RED;
            bool C = sibling->left == NULL || sibling->left->color == BLACK;
            if (A && B && C)
            {
                sibling->color = RED;
                sibling->right->color = BLACK;
                rotateRight(sibling);
            }
        }
    }
    deleteCase6(cur);
}
template <class K, class V>
void RBtree<K, V>::deleteCase6(Node *cur)
{
    Node *sibling = getSibling(cur);

    sibling->color = cur->parent->color;
    cur->parent->color = BLACK;

    if (cur == cur->parent->left)
    {
        sibling->right->color = BLACK;
        rotateLeft(cur->parent);
    }
    else
    {
        sibling->left->color = BLACK;
        rotateRight(cur->parent);
    }
}
//!DELETION END

#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    RBtree<string, int> tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string a, b;
        cin >> a >> b;
        if (b == "enter")
            tree.insert(a, 1);
        else
            tree.erase(a);
    }
    cout << tree.size();
}