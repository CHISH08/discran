#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef RBT_H
#define RBT_H

using ulli = unsigned long long int;

const short LEAF = -1;

class TRBtree {
public:
    class TNode {
    public:
        TNode() {};
        TNode(bool, ulli, char*);
        ~TNode();

        TNode* parent;
        TNode* left;
        TNode* right;
        char* key;
        ulli value;
        bool color;
    };

    TRBtree();
    ~TRBtree();
    void DeleteTree(TNode* root);
    TNode* Search(const char*);

    void Insert(TNode&);
    void RBInsertFixup(TNode*);

    void LeftRotate(TNode&);
    void RightRotate(TNode&);

    void RBTransPlant(TNode*, TNode*);
    TNode* FindMin(TNode*);

    void RBDelete(TNode*);
    void RBDeleteFixup(TNode*);

    void Save(const char*);
    void Save(std::ofstream&, TNode*);
    void Load(const char*);
    void Load(std::ifstream&, TNode*&);

    static const bool BLACK = false;
    static const bool RED = true;
private:
    TNode* root;
    TNode* nil;
};

#endif