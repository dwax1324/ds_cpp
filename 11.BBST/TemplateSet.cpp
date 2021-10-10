#include <stddef.h>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;

template <class K>
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
        Node *parent;
        Node *left;
        Node *right;
        bool color;
        bool nullLeaf;
        ~Node();
        Node() {}
        Node(K k) : key(k), parent(NULL), color(RED), left(NULL), right(NULL), nullLeaf(0) {}
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
    Node *find(K key);
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
    void insert(K key) { insert(new Node(key)); }
    int size() { return _size; }
    Node *root;
    int _size;
    void print() { print(root); }
    void print(Node *cur)
    {
        if (cur == NULL)
            return;
        print(cur->right);
        cout << cur->key << '\n';
        print(cur->left);
    }
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
template <class K>
typename RBtree<K>::Node *RBtree<K>::find(K key)
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
template <class K>
typename RBtree<K>::Node *RBtree<K>::getSuccesor(Node *cur)
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
template <class K>
RBtree<K>::Node::~Node()
{
    if (left && left->parent == this)
        left->parent = NULL;
    if (right && right->parent == this)
        right->parent = NULL;
    if (parent && parent->key > key && parent->left && parent->left == this)
        parent->left = NULL;
    if (parent && parent->key <= key && parent->right && parent->right == this) // successor의 값복사 때문에 등호를 붙힌다.
        parent->right = NULL;
    left = right = parent = NULL;
}
template <class K>
bool RBtree<K>::count(K key)
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

template <class K>
void RBtree<K>::destroy(Node *byebye)
{
    if (byebye == root)
        root = NULL;

    delete byebye;
}

template <class K>
typename RBtree<K>::Node *RBtree<K>::getParent(Node *cur) // return NULL if arg is NULL,root
{
    if (cur == NULL)
        return NULL;
    return cur->parent;
}
template <class K>
typename RBtree<K>::Node *RBtree<K>::getGrandParent(Node *cur)
{
    return getParent(getParent(cur));
}

template <class K>
typename RBtree<K>::Node *RBtree<K>::getSibling(Node *cur) // return NULL if cur have no silbing
{
    assert(cur != NULL);
    Node *parent = getParent(cur);
    if (parent == NULL)
        return NULL;
    else if (cur == parent->left)
        return parent->right;
    else
        return parent->left;
}
template <class K>
typename RBtree<K>::Node *RBtree<K>::getUncle(Node *cur)
{
    assert(cur != NULL);
    return getSibling(getParent(cur));
}

template <class K>
void RBtree<K>::rotateLeft(Node *cur)
{
    Node *child = cur->right;
    Node *parent = cur->parent;
    if (cur == root)
        root = child;
    if (child->left != NULL && !child->right->nullLeaf)
    {
        child->left->parent = cur;
    }
    cur->right = child->left;
    cur->parent = child;
    child->left = cur;
    child->parent = parent;

    if (parent != NULL && !parent->nullLeaf)
    {
        if (parent->left == cur)
            parent->left = child;
        else
            parent->right = child;
    }
}

template <class K>
void RBtree<K>::rotateRight(Node *cur)
{
    Node *child = cur->left;    // child
    Node *parent = cur->parent; // Parent
    if (cur == root)
        root = child;
    if (child->right != NULL && !child->right->nullLeaf)
        child->right->parent = cur;

    cur->left = child->right;
    cur->parent = child;
    child->right = cur;
    child->parent = parent;

    if (parent != NULL && !parent->nullLeaf)
    {
        if (parent->right == cur)
            parent->right = child;
        else
            parent->left = child;
    }
}

// ! helper function END

// ! INSERTION BEGIN

// * 이진탐색트리와 똑같이 삽입해준 후  케이스분류를 해준다.
template <class K>
void RBtree<K>::insert(Node *newNode)
{
    Node *cur = root;
    while (cur != NULL)
    {
        if (cur->key == newNode->key) // duplicate
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

    if (cur == NULL) // root
    {
        root = newNode;
        cur = root;
    }
    else
    {
        // cerr << cur->key << ' ' << newNode->key << '\n';
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

/*

    ! Insert Case1: 루트인 경우
    검은색으로 색을 바꾸고 리턴한다.
*/
template <class K>
void RBtree<K>::insertCase1(Node *newNode)
{
    // cerr << "case1\n";
    if (newNode->parent == NULL)
    {
        newNode->color = BLACK;
        return;
    }

    insertCase2(newNode);
}

/* 

    ! Insert Case2: 부모가 검은색일 경우
    규칙에 위배되는게 없으므로 리턴한다.
*/
template <class K>
void RBtree<K>::insertCase2(Node *newNode)
{
    // cerr << "case2\n";
    if (newNode->parent->color == BLACK)
    {
        // cerr << newNode->key << ' ' << newNode->key << '\n';
        return;
    }

    insertCase3(newNode);
}

template <class K>
void RBtree<K>::insertCase3(Node *newNode)
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
        // 할아버지와 할아버지의 부모가 둘 다 RED일 수 있으므로 다시 할아버지노드를 case1부터 체크해준다
        insertCase1(grandParent); // 위쪽으로 문제를 갖고 올라간다.(최악의 경우 -> 루트까지 올라감)
        return;
    }

    insertCase4(newNode);
}

template <class K>
void RBtree<K>::insertCase4(Node *newNode)
{
    // cerr << "case4\n";
    Node *parent = getParent(newNode);
    Node *grandParent = getGrandParent(newNode);
    // cerr << "@@" << (grandParent == NULL);
    // cerr << "rootcolor" << root->color;
    // cerr << newNode->parent->parent->key;
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

template <class K>
void RBtree<K>::insertCase5(Node *newNode)
{
    // cerr << "case5\n";
    Node *parent = getParent(newNode);
    Node *grandParent = getGrandParent(newNode);
    parent->color = BLACK;
    grandParent->color = RED;
    if (newNode == parent->left)
        rotateRight(grandParent);
    else
        rotateLeft(grandParent);
}

//!INSERTION END

//!DELETION BEGIN
template <class K>
void RBtree<K>::erase(K key) { erase(find(key)); }
template <class K>
void RBtree<K>::erase(Node *cur)
{

    if (cur == NULL || !count(cur->key)) // no such key
        return;
    Node *toDelete = NULL;
    Node *child = NULL;
    // 양쪽 자식인경우 -> successor를 찾아준다.
    if (cur->left && cur->right)
    {
        toDelete = getSuccesor(cur);
    }
    else
    {
        toDelete = cur;
    }
#ifdef DEBUG
    // cout << "+--------------------------+" << endl;
    // cout << "cur, Successor: " << cur->key << ' ' << toDelete->key << '\n';
#endif

    // NULL을 대비한 가짜노드
    Node *leaf = new Node(toDelete->key, toDelete->value);
    leaf->nullLeaf = true;
    // 자식이 하나 이하이다.
    if (toDelete->left == NULL)
        child = toDelete->right;
    else
        child = toDelete->left;
    if (child == NULL)
    {
        child = leaf;
        leaf->color = BLACK;
    }

    // 자식의 부모포인터를 재설정
    child->parent = toDelete->parent;

    // 삭제할 노드가 루트인 경우
    if (toDelete->parent == NULL)
    {
        root = child;
    }
    else
    {
        // 루트가 아닌경우
        // 삭제할 노드의 부모 포인터를 자식에게 연결
        if (toDelete == toDelete->parent->left)
            toDelete->parent->left = child;
        else
            toDelete->parent->right = child;
    }

    // cur가 succssor인 경우 값을 복사한다.
    if (cur != toDelete)
    {
        cur->key = toDelete->key;
        cur->value = toDelete->value;
        // if (cur->key == 8)
        //     cur->key = -95;
    }
    _size--;
    // 간단경우 2개
    // 1. 지운 노드가 RED일경우 추가작업이 필요없다.
    if (toDelete->color == RED)
    {
        destroy(toDelete);
        destroy(leaf);
        return;
    }

    // 2. 지운 노드가 블랙이고 그 자식이 레드일때
    //    자식을 검은색으로 칠하고 종료한다.
    if (child != NULL && toDelete->color == BLACK && child->color == RED)
    {
        child->color = BLACK;
        destroy(toDelete);
        destroy(leaf);
        return;
    }

    // 지운 노드의 자식노드를 다음 경우에 넘겨준다.
    deleteCase1(child);
    destroy(leaf);
}

template <class K>
void RBtree<K>::deleteCase1(Node *cur)
{
    if (cur->parent == NULL)
    {
        return;
    }
    deleteCase2(cur);
}

template <class K>
void RBtree<K>::deleteCase2(Node *cur)
{
    Node *sibling = getSibling(cur);
    if (sibling && sibling->color == RED)
    {
        // cerr << "#" << cur->key << "#";
        cur->parent->color = RED;
        sibling->color = BLACK;
        // cerr << "!!" << root->right->key << "!!";
        if (cur == cur->parent->left)
            rotateLeft(cur->parent);
        else
            rotateRight(cur->parent);
        // cerr << "!!" << root->right->key << "!!";
    }
    deleteCase3(cur);
}

template <class K>
void RBtree<K>::deleteCase3(Node *cur)
{
    Node *sibling = getSibling(cur);

    // parent, sibling , sibling's children이 블랙이면 sibling을 RED로 칠한다.
    if (sibling)
    {
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
    }
    deleteCase4(cur);
}

template <class K>
void RBtree<K>::deleteCase4(Node *cur)
{

    Node *sibling = getSibling(cur);

    if (sibling)
    {
        bool A = cur->parent->color == RED;
        bool B = sibling->color == BLACK;
        bool C = sibling->left == NULL || sibling->left->color == BLACK;
        bool D = sibling->right == NULL || sibling->right->color == BLACK;
        if (A && B && C && D)
        {
            // cerr << "#" << cur->key << "#";
            sibling->color = RED;
            cur->parent->color = BLACK;

            return;
        }
    }
    deleteCase5(cur);
}

template <class K>
void RBtree<K>::deleteCase5(Node *cur)
{
    Node *sibling = getSibling(cur);
    if (sibling && sibling->color == BLACK)
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
                rotateLeft(sibling);
            }
        }
    }
    deleteCase6(cur);
}

template <class K>
void RBtree<K>::deleteCase6(Node *cur)
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