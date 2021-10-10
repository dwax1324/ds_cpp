#include <stddef.h>
#include <assert.h>
#include <bits/stdc++.h>

#define DEBUG
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

*Deletion
    단순 값을 복사하는 것은 레드-블랙 특성(properties)을 위반하지 않는다.
    삭제했을 때 특성을 위반하는지만 체크해주면 된다.
    간단한 상황들 부터 처리
        - 간단한 상황들
            삭제할 노드가 레드일 경우 -> 그냥 삭제해주면 된다. 규칙위반 X
            삭제할 노드가 블랙이고 그 자식이 레드일때 특성4,5를 위반할 수 있으나, 자식을 검은색으로 칠하면 된다.
            



*/

class RBtree
{

public:
    enum
    {
        RED = true,
        BLACK = false
    };
    class Node
    {
    public:
        int key;
        int value;
        Node *parent;
        Node *left;
        Node *right;
        bool color;
        bool nullLeaf;
        ~Node();
        Node() {}
        Node(int k) : key(k), parent(NULL), color(RED), left(NULL), right(NULL), nullLeaf(0) {}
        Node(int k, int v) : key(k), value(v), parent(NULL), color(RED), left(NULL), nullLeaf(0), right(NULL) {}
    };
    RBtree() : root(NULL), _size(0) {}
    void destroy(Node *);
    bool count(int);
    Node *getParent(Node *);
    Node *getGrandParent(Node *);
    Node *getSibling(Node *);
    Node *getUncle(Node *);
    Node *getCloseNephew(Node *);
    Node *getDistantNewphew(Node *);
    Node *find(int key);
    Node *getSuccesor(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void insert(Node *);
    void insertCase1(Node *);
    void insertCase2(Node *);
    void insertCase3(Node *);
    void insertCase4(Node *);
    void insertCase5(Node *);
    void erase(int);
    void erase(Node *); // = delete
    void deleteCase1(Node *);
    void deleteCase2(Node *);
    void deleteCase3(Node *);
    void deleteCase4(Node *);
    void deleteCase5(Node *);
    void deleteCase6(Node *);
    bool isLeaf(Node *cur) { return cur != root && cur == NULL; } // 모든 leaf 노드는 NULL
    void insert(int key, int value) { insert(new Node(key, value)); }
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

RBtree::Node *RBtree::find(int key)
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
RBtree::Node *RBtree::getSuccesor(Node *cur)
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
RBtree::Node::~Node()
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
    if (parent == NULL)
        return NULL;
    else if (cur == parent->left)
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
    _size++;
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

void RBtree::erase(int key) { erase(find(key)); }
void RBtree::erase(Node *cur)
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

/*
    *Delete Case1: 루트인경우 종료한다.
*/
void RBtree::deleteCase1(Node *cur)
{
    if (cur->parent == NULL)
    {
        return;
    }
    deleteCase2(cur);
}

/*
    *Delete Case2: 
    ! case 2를 통과하면 N과 S는 반드시 검은색 노드가 된다. new-> cur, S ->sibling
    S: sibling , P: parent, 
    * S 가 빨강일 경우. P의 자식인 S가 빨강색이므로 P가 검은색임이 명확하다.
    * 이 경우 P와 S의 색을 바꾸고, P에서 왼쪽으로 회전 하면, S가 N의 할아버지 노드가 된다.
*/
void RBtree::deleteCase2(Node *cur)
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

/*
    * Delete Case 3:
    * P, S, 그리고 S의 자식들이 검은색인 경우 
    * S를 빨강으로 칠하면 된다
    부모는 case 1부터 시작하는 rebalancing 과정을 수행해야 한다.

*/
void RBtree::deleteCase3(Node *cur)
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

/*
    Case4: S와 S의 자식들은 검은색이지만, P는 빨강인 경우.
     S와 P의 색을 바꾸면 된다

*/

void RBtree::deleteCase4(Node *cur)
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

/*
    Case5: S가 검정, S의 왼쪽 자식이 빨강, S의 오른쪽 자식이 검정이며, N이 부모의 왼쪽 자식인 경우. 
     S가 검정, S의 오른쪽 자식이 빨강, S의 왼쪽 자식이 검정이며, N이 부모의 오른쪽 자식인 경우. 

     S를 오른쪽으로 회전시켜서 S의 왼쪽 자식이 S의 부모노드이자 N의 새로운 형제 노드가 되도록 만든다.
*/

void RBtree::deleteCase5(Node *cur)
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

/*
    Deletion Case 6:S가 검은색, S의 오른쪽 자식이 빨강이며, N 이 P의 왼쪽 자식인 경우

    P를 왼쪽으로 회전해서, S가 P와 S의 오른쪽 자식노드의 부모 노드가 되게 한 후,
    P와 S의 색을 바꾸고, S의 오른쪽 자식노드를 검은색으로 만든다
*/

void RBtree::deleteCase6(Node *cur)
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
#ifdef DEBUG
    RBtree tree;

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    do
    {
        for (auto x : v)
            tree.insert(x, 1);
        for (auto x : v)
            tree.erase(x);
    } while (next_permutation(v.begin(), v.end()));

#endif
}