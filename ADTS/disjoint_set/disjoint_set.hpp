#include <vector>

using namespace std;

struct Disj {
    vector<int> p;
    Disj() {};

    Disj(int n) {
        p = vector<int>(n, -1);
    };

    int find(int a) {
        if (p[a] == -1) return a;
        return p[a] = find(p[a]);
    };

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    };
};