
#include <stddef.h>
#include <assert.h>

/*

Search = 똑같음

Insertion
    case 1: 루트가 NULL인 경우



*/
enum
{
    RED = 1,
    BLACK = 0
};

class RBtree
{
public:
    class Node
    {
    public:
        int key;
        int value;
        Node *parent;
        Node *left;
        Node *right;
        bool color;
        ~Node();
        Node() {}
        Node(int k) : key(k), parent(NULL), color(RED), left(NULL), right(NULL) {}
        Node(int k, int v) : key(k), value(v), parent(NULL), color(RED), left(NULL), right(NULL) {}
    };
    void destroy(Node *);
    Node *getParent(Node *);
    Node *getGrandParent(Node *);
    Node *getSibling(Node *);
    Node *getUncle(Node *);
    Node *getCloseNephew(Node *);
    Node *getDistantNewphew(Node *);
    Node *find(int key);
    void insert(Node *);
    void insertCase1(Node *);
    void insertCase2(Node *);
    void insertCase3(Node *);
    void insertCase4(Node *);
    void insertCase5(Node *);
    bool isLeaf(Node *cur) { return cur != NULL && cur->left == NULL && cur->right == NULL; }
    void insert(int key, int value) { insert(new Node(key, value)); }
    Node *root;
    int size;
};

RBtree::Node::~Node()
{
    if (parent && parent->left == this)
        parent->left = NULL;
    if (parent && parent->right == this)
        parent->right = NULL;
    if (left && left->parent == this)
        left->parent = NULL;
    if (right && right->parent == this)
        right->parent = NULL;
}

void RBtree::destroy(Node *byebye)
{
    byebye = NULL;
    delete byebye;
}

RBtree::Node *RBtree::getParent(Node *cur) // return NULL if arg is NULL or root
{
    if (cur == root || cur == NULL)
        return NULL;
    return cur->parent;
}
RBtree::Node *RBtree::getGrandParent(Node *cur)
{
    return getParent(getParent(cur));
}
RBtree::Node *RBtree::getSibling(Node *cur) // return NULL if no silbing
{
    assert(cur != NULL);
    Node *parent = getParent(cur);
    if (parent->left == cur && parent->right)
        return parent->right;
    if (parent->right == cur && parent->left)
        return parent->left;
    return NULL;
}
RBtree::Node *RBtree::getUncle(Node *cur)
{
    assert(cur != NULL);
    return getSibling(getParent(cur));
}

// 이진탐색트리와 똑같이 삽입해준 후  케이스분류를 해준다.
void RBtree::insert(Node *newNode)
{
    Node *cur = root;
    while (!isLeaf(cur))
    {
        if (cur->key > newNode->key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    cur = cur->parent;
    if (cur->key > newNode->key)
        cur->left = newNode;
    else
        cur->right = newNode;
    newNode->parent = cur;
    insertCase1(cur);
};

void RBtree::insertCase1(Node *newNode) // 루트인 경우
{
    if (newNode->parent == NULL)
    {
        newNode->color = BLACK;
    }
    else
    {
        insertCase2(newNode);
    }
}
void RBtree::insertCase2(Node *newNode) // 부모가 흑인인 경우
{
    if (newNode->parent->color == BLACK)
        return;
    else
        insertCase3(newNode);
}
void RBtree::insertCase3(Node *newNode)
{
}

/*
    RBtree::Node *RBtree::getCloseNephew(Node *)
    {
    }
    RBtree::Node *RBtree::getDistantNewphew(Node *) {}
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
}