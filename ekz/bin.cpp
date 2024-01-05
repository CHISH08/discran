#include<bits/stdc++.h>


class binTree;
class Tnode {
    friend class binTree;
public:
    Tnode(int val) {
        value = val;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    Tnode(int val, Tnode* par) {
        value = val;
        parent = par;
        left = nullptr;
        right = nullptr;
    }
    Tnode(int val, Tnode* par, Tnode* L, Tnode* R) {
        value = val;
        parent = par;
        left = L;
        right = R;
    }
    ~Tnode() {
        // if (parent) {
        delete[] parent;
        // }
        // if (left) {
        delete[] left;
        // }
        // if (right) {
        delete[] right;
        // }
    }
private:
    Tnode *parent;
    Tnode *left;
    Tnode *right;
    int value;
}


class binTree {
public:
    binTree() {
        root = new Tnode(NULL);
    }
    ~binTree() {
        delete[] Tnode;
    }
private:
    Tnode* root;
}

int main()
{
    binTree ST;
    return 0;
}