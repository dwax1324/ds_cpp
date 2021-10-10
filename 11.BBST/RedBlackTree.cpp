#include <stddef.h>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;
/*

* 1. 노드는 레드 혹은 블랙 중의 하나이다.
* 2. 루트 노드는 블랙이다.
* 3. 모든 리프 노드들(NIL)은 블랙이다.
* 4. 레드 노드는 연달아 나타날 수 없다.
* 5. 어떤 노드로부터 리프노드까지 항상 같은 개수의 블랙 노드가 있다.
    ! 위 다섯 조건만 만족하면 트리의 높이가 최악의 경우 logN이 됨을 보장한다.

left rotate, right rotate
rotate을 했을때 이진탐색트리의 특성을 항상 유지하는가? O
rotate을 했을때 레드블랙트리의 특성을 항상 유지하는가? X

P = parent, U = uncle, G = grandparent , N = newNode

*Insertion
    case 1: 부모가 NULL인 경우
    case 2: 부모색이 블랙일 경우
    case 3: 부모와 삼촌이 레드일 경우
    이 밑에서부터는 왼쪽을 기준으로 말한다. (반대쪽 경우도 생각해줘야함)
    case 4: 부모는 레드, 삼촌은 블랙, 자신은 부모의 오른쪽 자식이며, 부모는 할아버지의 왼쪽 자식이다.
    case 5: 부모는 레드,삼촌은 블랙,  자신은 부모의 왼쪽 자식이고, 부모는 할아버지의 왼쪽 자식이다.

    *Solution
        Case1: tree의 size가 0이다. 루트로 지정한 후 색을 블랙으로 바꾼다.
        Case2: 모든 조건을 만족하므로 리턴한다.
        Case3: 부모,삼촌,할아버지의 색을 반전시킨다.
        Case4: 부모를 rotate를 시켜서 case5형태로 만들어준다.
        Case5: 할아버지를 rotate를 시킨다. 이 경우, 
               부모가 subtree의 루트가 된다. 부모의 자식(자신과 할아버지)의 색을 빨간색으로 바꾼후
               부모의 색은 검은색으로 바꾼다.




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
    RBtree() : root(NULL), size(0) {}
    void destroy(Node *);
    bool count(int);
    Node *getParent(Node *);
    Node *getGrandParent(Node *);
    Node *getSibling(Node *);
    Node *getUncle(Node *);
    Node *getCloseNephew(Node *);
    Node *getDistantNewphew(Node *);
    Node *find(int key);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void insert(Node *);
    void insertCase1(Node *);
    void insertCase2(Node *);
    void insertCase3(Node *);
    void insertCase4(Node *);
    void insertCase5(Node *);
    bool isLeaf(Node *cur) { return cur != root && cur == NULL; } // 모든 leaf 노드는 NULL
    void insert(int key, int value) { insert(new Node(key, value)); }
    Node *root;
    int size;

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
RBtree::Node::~Node()
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

bool RBtree::count(int key)
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

void RBtree::destroy(Node *byebye)
{
    if (byebye == root)
        root = NULL;

    delete byebye;
}

RBtree::Node *RBtree::getParent(Node *cur) // return NULL if arg is NULL,root
{
    if (cur == NULL)
        return NULL;
    return cur->parent;
}
RBtree::Node *RBtree::getGrandParent(Node *cur)
{
    return getParent(getParent(cur));
}
RBtree::Node *RBtree::getSibling(Node *cur) // return NULL if cur have no silbing
{
    assert(cur != NULL);
    Node *parent = getParent(cur);
    if (cur == parent->left)
        return parent->right;
    else
        return parent->left;
}
RBtree::Node *RBtree::getUncle(Node *cur)
{
    assert(cur != NULL);
    return getSibling(getParent(cur));
}

/*
  ?left rotation     ===>

    ㅇ <- cur                        ㅇ   <- child
   /  \                             /  \
  A    ㅇ <- child         cur -> ㅇ    C
       / \                       /  \
      B   C                     A    B
*/
void RBtree::rotateLeft(Node *cur)
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
/*
  ?rotate right     ===>

      cur->  ㅇ                       ㅇ <- child
            /  \                     /  \             
child ->  ㅇ    C                   A    ㅇ <- cur  
         /  \                            / \          
        A    B                          B   C                 
*/

void RBtree::rotateRight(Node *cur)
{
    Node *child = cur->left;    // child
    Node *parent = cur->parent; // Parent

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
// * 이진탐색트리와 똑같이 삽입해준 후  케이스분류를 해준다.
void RBtree::insert(Node *newNode)
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
    size++;
    insertCase1(cur);
};

/*
    ! Insert Case1: 루트인 경우
    검은색으로 색을 바꾸고 리턴한다.
*/
void RBtree::insertCase1(Node *newNode)
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
void RBtree::insertCase2(Node *newNode)
{
    // cerr << "case2\n";
    if (newNode->parent->color == BLACK)
    {
        // cerr << newNode->key << ' ' << newNode->key << '\n';
        return;
    }

    insertCase3(newNode);
}

/*
    ! Insert Case3: 부모와 삼촌이 모두 빨간색일 경우

    삽입되는 노드는 항상 빨간색이므로,
    
    한 노드에서부터 뻗어나가는 모든 경로에 대한 검은색 노드의 수를
    유지하기 위해서, 부모와 삼촌을 검은색으로 바꾸고 할아버지 노드를 붉은색으로 바꾼다. 
    하지만 이렇게 바꾸면
        2)root node는 검은색이다
        4)붉은색 노드의 두 자식 노드는 검은색이다.
    위 조건을 만족하지 않을 수 있다.
    따라서 할아버지 노드를 다시 InsertCase1로 호출한다.
    할아버지 불쌍ㅠ_ㅠ
*/

void RBtree::insertCase3(Node *newNode)
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

/*
    부모 노드 P가 할아버지 노드 G의 왼쪽 자식이라고 가정한다.
    반대의 경우도 생각해야한다.
    ! Insert Case4: 부모 노드 P가 붉은색인데, 삼촌 노드 U는 검은색이고, 
    ! 새로운 노드 N은 P의 오른쪽 자식 노드이며, P는 할아버지 노드 G의 왼쪽 자식 노드이다.

    4. 붉은색 노드의 모든 자식은 검은색 노드이다을 만족하지 않기 때문에
    이경우, left rotation을 진행한 후, 부모 노드였던 P를 다섯번째 케이스로 넘겨준다.
    

*/
void RBtree::insertCase4(Node *newNode)
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

/*
    ! Insert Case5: 
    ! 부모 노드 P는 붉은색이지만 삼촌 노드 U는 검은색이고, 
    ! 새로운 노드 N이 P의 왼쪽 자식 노드이고,
    ! P가 할아버지 노드 G의 왼쪽 자식 노드인 상황에서는 G에 대해 오른쪽 회전

    회전의 결과 이전의 부모 노드였던 P는 새로운 노드 N과 할아버지 노드 G를 자식 노드로 갖는다. 
    G가 이전에 검은색이었고, P는 붉은색일 수밖에 없기 때문에, 
    P와 G의 색을 반대로 바꾸면 
    레드-블랙 트리의 네 번째 속성(붉은색 노드의 두 자식 노드는 검은색 노드이다)을 만족한다. 
    레드-블랙 트리의 다섯 번째 속성(한 노드에서부터 뻗어나가는 모든 경로에 대해 검은색 노드의 수는 같다)은 
    계속 유지되는데, 이는 이전에 P를 포함하는 경로는 모두 G를 지나게 되고, 
    바뀐 후 G를 포함하는 경로는 모두 P를 지나기 때문이다. 바뀌기 전에는 G가, 
    바뀐 후에는 P가 P, G, N중 유일한 검은색 노드이다.

*/
void RBtree::insertCase5(Node *newNode)
{
    // cerr << "case5\n";
    Node *parent = getParent(newNode);
    Node *grandParent = getGrandParent(newNode);
    parent->color = BLACK;
    grandParent->color = RED;
    // rotate시킬 할아버지 노드 G가 루트일경우 루트를 그 밑 노드인 parent로 재설정해줘야한다.
    if (grandParent == root)
        root = parent;
    if (newNode == parent->left)
        rotateRight(grandParent);
    else
        rotateLeft(grandParent);
}

/*

    RBtree::Node *RBtree::getCloseNephew(Node *)
    {
    }
    RBtree::Node *RBtree::getDistantNewphew(Node *) {}
*/
//!INSERTION END

//!DELETION BEGIN

//!DELETION END
#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    RBtree tree;
    vector<int> perfect = {8, 4, 2, 6, 1, 3, 5, 7, 12, 11, 14, 9, 10, 13, 15};
    for (auto i : perfect)
    {
        cerr << "inserted: " << i << '\n';
        tree.insert(i, 1);
    }
    // tree.inorder();

    // TODO TEST INSERTION
    /*
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    do
    {
        RBtree tree;
        for (auto x : v)
            tree.insert(x, 1);
        // tree.preorder();
        // cout << '\n';
    } while (next_permutation(v.begin(), v.end()));
    */
}