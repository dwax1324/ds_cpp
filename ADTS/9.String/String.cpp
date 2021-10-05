
#include <bits/stdc++.h>

#include <vector>
class String {
public:
    String(){};
    String(int size) { vec.resize(size); }
    String(int size, char k) {
        for (int i = 0; i < size; i++) vec.push_back(k);
    }

    // A member function takes an implicit first parameter.
    const int size() const { return vec.size(); }
    friend String operator+(String lhs, const String& rhs) {
        String ret;
        for (int i = 0; i < lhs.size(); i++) ret.vec.push_back(lhs.vec[i]);
        for (int i = 0; i < rhs.size(); i++) ret.vec.push_back(rhs.vec[i]);
        return ret;
    }
    friend String operator+(String lhs, const char* rhs) {
        String ret;
        for (int i = 0; i < lhs.size(); i++) ret.vec.push_back(lhs.vec[i]);

        for (int i = 0; rhs[i] != '\0'; i++) ret.vec.push_back(rhs[i]);
        return ret;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& p) {
        for (int i = 0; i < p.size(); i++) {
            out << p.vec[i];
        }
        return out;
    }
    friend std::istream& operator>>(std::istream& in, String& p) {
        while (1) {
            char a;
            in >> a;
            if (!in) break;
            p.push_back(a);
        }
        return in;
    }

    bool operator==(String& p) {
        if (size() != p.size()) return false;
        for (int i = 0; i < size(); i++)
            if (this->vec[i] != p[i]) return false;
        return true;
    }
    bool operator==(const char* p) {
        int len = 0;
        while (p[len] != '\0') len++;
        if (size() != len) return false;
        for (int i = 0; i < size(); i++)
            if (this->vec[i] != p[i]) return false;
        return true;
    }
    bool operator!=(String& p) {
        return !(*this == p);
    }
    bool operator!=(const char* p) {
        return !(*this == p);
    }

    void operator+=(const char* p) {
        *this = *this + p;
    }

    void operator+=(const String& p) {
        *this = *this + p;
    }

    char operator[](int idx) {
        return this->vec[idx];
    }

    char front() {
        return vec.front();
    }
    char back() {
        return vec.back();
    }
    void push_back(const char p) {
        vec.push_back(p);
    }
    void erase(int idx, int toDelete) {
        vec.erase(vec.begin() + idx, vec.begin() + idx + toDelete);
    }

    // private:
    std::vector<char> vec;
};
