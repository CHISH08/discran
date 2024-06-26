#ifndef RBT_H
#define RBT_H

#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;

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

    void Serialize(const char*);
    void Serialize(ofstream&, TNode*);
    void Deserialize(const char*);
    void Deserialize(ifstream&, TNode*&);

    static const bool BLACK = false;
    static const bool RED = true;
private:
    TNode* root;
    TNode* nil;
};

#endif

TRBtree::TRBtree() {
    nil = new TNode(BLACK, 0, nullptr);
    root = nil;
}

TRBtree::~TRBtree() {
    DeleteTree(this->root);
    delete this->nil;
}

TRBtree::TNode::TNode(bool newColor, ulli newValue,
    char* newKey) {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    value = newValue;
    color = newColor;
    key = newKey;
}

TRBtree::TNode::~TNode() {
    delete [] key;
    key = nullptr;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void TRBtree::Insert(TNode& newNode) {
    TNode* preNode = this->nil;
    TNode* curNode = this->root;
    while(curNode != this->nil) {
        preNode = curNode;
        if(0 > strcmp(newNode.key, curNode->key)) {
            curNode = curNode->left;
        } else {
            curNode = curNode->right;
        }
    }
    newNode.parent = preNode;
    if(preNode == this->nil) {
        this->root = &newNode;
    } else if(0 > strcmp(newNode.key, preNode->key)) {
        preNode->left = &newNode;
    } else {
        preNode->right = &newNode;
    }
    newNode.right = this->nil;
    newNode.left = this->nil;
    newNode.color = RED;
    RBInsertFixup(&newNode);
}

void TRBtree::LeftRotate(TNode& curNode) {
    TNode* y = curNode.right;
    curNode.right = y->left;
    if(y->left != this->nil) {
        y->left->parent = &curNode;
    }
    y->parent = curNode.parent;
    if(curNode.parent == this->nil) {
        this->root = y;
    } else if(&curNode == curNode.parent->left) {
        curNode.parent->left = y;
    } else {
        curNode.parent->right = y;
    }
    y->left = &curNode;
    curNode.parent = y;
}

void TRBtree::RightRotate(TNode& curNode) {
    TNode* y = curNode.left;
    curNode.left = y->right;
    if(y->right != this->nil) {
        y->right->parent = &curNode;
    }
    y->parent = curNode.parent;
    if(curNode.parent == this->nil) {
        this->root = y;
    } else if(&curNode == curNode.parent->right) {
        curNode.parent->right = y;
    } else {
        curNode.parent->left = y;
    }
    y->right = &curNode;
    curNode.parent = y;
}

void TRBtree::RBInsertFixup(TNode* curNode) {
    while(curNode->parent->color == RED) {
        if(curNode->parent == curNode->parent->parent->left) {
            TNode* y = curNode->parent->parent->right;
            if(y->color == RED) {
                curNode->parent->color = BLACK;
                y->color = BLACK;
                curNode->parent->parent->color = RED;
                curNode = curNode->parent->parent;
            } else {
                if(curNode == curNode->parent->right) {
                    curNode = curNode->parent;
                    LeftRotate(*curNode);
                }
                curNode->parent->color = BLACK;
                curNode->parent->parent->color = RED;
                RightRotate(*(curNode->parent->parent));
            }
        } else {
            TNode* y = curNode->parent->parent->left;
            if(y->color == RED) {
                curNode->parent->color = BLACK;
                y->color = BLACK;
                curNode->parent->parent->color = RED;
                curNode = curNode->parent->parent;
            } else {
                if(curNode == curNode->parent->left) {
                    curNode = curNode->parent;
                    RightRotate(*curNode);
                }
                curNode->parent->color = BLACK;
                curNode->parent->parent->color = RED;
                LeftRotate(*(curNode->parent->parent));
            }
        }
    }
    this->root->color = BLACK;
}

TRBtree::TNode* TRBtree::Search(const char* pattern) {
    TNode* tmp = this->root;
    while(tmp != this->nil) {
        if(!strcmp(tmp->key, pattern)) {
            return tmp;
        } else if(strcmp(tmp->key, pattern) < 0) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return nullptr;
}

TRBtree::TNode* TRBtree::FindMin(TNode* curNode) {
    while(curNode->left != this->nil) {
        curNode = curNode->left;
    }
    return curNode;
}

void TRBtree::RBTransPlant(TNode* old, TNode* upd) {
    if(old->parent == this->nil) {
        this->root = upd;
    } else if(old == old->parent->left) {
        old->parent->left = upd;
    } else {
        old->parent->right = upd;
    }
    upd->parent = old->parent;
}

void TRBtree::RBDelete(TNode* curNode) {
    TNode* transNode = curNode;
    TNode* childOfTrans = nullptr;
    bool yOrigColor = transNode->color;
    if(curNode->left == this->nil) {
        childOfTrans = curNode->right;
        RBTransPlant(curNode, curNode->right);
    } else if(curNode->right == this->nil) {
        childOfTrans = curNode->left;
        RBTransPlant(curNode, curNode->left);
    } else {
        transNode = FindMin(curNode->right);
        yOrigColor = transNode->color;
        childOfTrans = transNode->right;
        if(transNode->parent == curNode) {
            childOfTrans->parent = transNode;
        } else {
            RBTransPlant(transNode, transNode->right);
            transNode->right = curNode->right;
            transNode->right->parent = transNode;
        }
        RBTransPlant(curNode, transNode);
        transNode->left = curNode->left;
        transNode->left->parent = transNode;
        transNode->color = curNode->color;
    }
    if(yOrigColor == BLACK) {
        RBDeleteFixup(childOfTrans);
    }
    delete curNode;
}

void TRBtree::RBDeleteFixup(TNode* curNode) {
    while(curNode != this->root && curNode->color == BLACK) {
        if(curNode == curNode->parent->left) {
            TNode* bro = curNode->parent->right;
            if(bro->color == RED) {
                bro->color = BLACK;
                curNode->parent->color = RED;
                LeftRotate(*(curNode->parent));
                bro = curNode->parent->right;
            }
            if(bro->left->color == BLACK && bro->right->color == BLACK) {
                bro->color = RED;
                curNode = curNode->parent;
            } else {
                if(bro->right->color == BLACK) {
                    bro->left->color = BLACK;
                    bro->color = RED;
                    RightRotate(*bro);
                    bro = curNode->parent->right;
                }
                bro->color = curNode->parent->color;
                curNode->parent->color = BLACK;
                bro->right->color = BLACK;
                LeftRotate(*(curNode->parent));
                curNode = this->root;
            }
        } else {
            TNode* bro = curNode->parent->left;
            if(bro->color == RED) {
                bro->color = BLACK;
                curNode->parent->color = RED;
                RightRotate(*(curNode->parent));
                bro = curNode->parent->left;
            }
            if(bro->right->color == BLACK && bro->left->color == BLACK) {
                bro->color = RED;
                curNode = curNode->parent;
            } else {
                if(bro->left->color == BLACK) {
                    bro->right->color = BLACK;
                    bro->color = RED;
                    LeftRotate(*bro);
                    bro = curNode->parent->left;
                }
                bro->color = curNode->parent->color;
                curNode->parent->color = BLACK;
                bro->left->color = BLACK;
                RightRotate(*(curNode->parent));
                curNode = this->root;
            }
        }
    }
    curNode->color = BLACK;
}

void TRBtree::Serialize(const char* buffer) {
    ofstream output(buffer);
    if(output.is_open()) {
        Serialize(output, this->root);
        cout << "OK\n";
    } else {
        // cout << "ERROR: Couldn't create file\n";
        cout << "OK\n";
    }
    output.close();
}

void TRBtree::Serialize(ofstream& output, TNode* root) {
    if(root == this->nil) {
        output << LEAF << " ";
        return;
    }
    output << root->key << " " << root-> value << " " << root->color << " ";
    Serialize(output, root->left);
    Serialize(output, root->right);
}

void TRBtree::Deserialize(const char* buffer) {
    ifstream input(buffer);
    if(input.is_open()) {
        DeleteTree(this->root);
        this->root = this->nil;
        Deserialize(input, this->root);
        cout << "OK\n";
    } else {
        // cout << "ERROR: Couldn't load file\n";
        cout << "OK\n";
    }
    root->parent = this->nil;
    input.close();
}

void TRBtree::Deserialize(ifstream& input, TNode*& root) {
    char buffer[256];
    ulli value = 0;
    bool color = RED;
    if(input.peek() == EOF || (input >> buffer && !strcmp(buffer, "-1"))) {
        return;
    }

    input >> value >> color;
    char* tmpKey = new char[strlen(buffer) + 1];
    strcpy(tmpKey, buffer);

    root = new TNode(color, value, tmpKey);
    root->left = this->nil;
    root->right = this->nil;
    Deserialize(input, root->left);
    Deserialize(input, root->right);
    root->left->parent = root;
    root->right->parent = root;
}

void TRBtree::DeleteTree(TNode* root) {
    if(root == this->nil) {
        return;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

void ToLower(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; ++i) {
         if (buffer[i] <= 'Z' && buffer[i] >= 'A') {
            buffer[i] = buffer[i] - 'A' + 'a';
         }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    TRBtree tree;
    char buffer[257];
    ulli value;
    while((cin>>buffer) && (buffer[0] != EOF))
    {
        TRBtree::TNode* tmp = nullptr;
        TRBtree::TNode* temp = new TRBtree::TNode;
        switch (buffer[0])
        {
            case '+': {
                cin >> buffer;
                ToLower(buffer);
                cin >> value;
                temp->key = new char[strlen(buffer) + 1];
                strcpy(temp->key, buffer);
                temp->value = value;
                temp->color = TRBtree::RED;
                if(!tree.Search(buffer)) {
                    tree.Insert(*temp);
                    cout << "OK\n";
                } else {
                    cout << "Exist\n";
                }
                break;
            }
            case '-': {
                cin >> buffer;
                ToLower(buffer);
                tmp = tree.Search(buffer);
                if(tmp) {
                    tree.RBDelete(tmp);
                    cout << "OK\n";
                } else {
                    cout << "NoSuchWord\n";
                }
                break;
            }
            case '!': {
                cin >> buffer;
                if (buffer[0] == 'L') {
                    cin >> buffer;
                    tree.Deserialize(buffer);
                    break;
                } else if (buffer[0] == 'S') {
                    cin >> buffer;
                    tree.Serialize(buffer);
                    break;
                }
                break;
            }
            default: {
                ToLower(buffer);
                tmp = tree.Search(buffer);
                if (tmp) {
                    cout << "OK: " << tmp->value << "\n";
                } else {
                    cout << "NoSuchWord\n";
                }
                break;
            }
        }
    }
    return 0;
}