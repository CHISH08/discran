#include <cctype>
#include <time.h>
#include <map>
#include "RB_tree.hpp"
using namespace std;

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
    map<char*, ulli> m;
    char buffer[257];
    ulli value;
    clock_t tStart;
    int count_flag = 0;
    ofstream MyFile1("res1.txt");
    while(cin>>buffer)
    {
        TRBtree::TNode* tmp = nullptr;
        TRBtree::TNode* temp = new TRBtree::TNode;
        switch (buffer[0])
        {
            case '+': {
                cin >> buffer;
                ToLower(buffer);
                cin >> value;
                tStart = clock();
                temp->key = new char[strlen(buffer) + 1];
                strcpy(temp->key, buffer);
                temp->value = value;
                temp->color = TRBtree::RED;
                if(!tree.Search(buffer)) {
                    tree.Insert(*temp);
                    cout << "OK_Add1\n";
                } else {
                    cout << "Exist\n";
                }
                MyFile1 << (double)(clock() - tStart) << ' ';
                clock_t t2Start = clock();
                m[buffer] = value;
                cout << "OK_Add2\n";
                MyFile1 << (double)(clock() - t2Start) << '\n';
                break;
            }
            case '-': {
                cin >> buffer;
                ToLower(buffer);
                tStart = clock();
                tmp = tree.Search(buffer);
                if(tmp) {
                    tree.RBDelete(tmp);
                    cout << "OK_Del1\n";
                } else {
                    cout << "NoSuchWord\n";
                }
                MyFile1 << (double)(clock() - tStart) << ' ';
                clock_t t2Start = clock();
                m.erase(buffer);
                cout << "OK_Del2\n";
                MyFile1 << (double)(clock() - t2Start) << '\n';
                break;
            }
            case '!': {
                cin >> buffer;
                if (buffer[0] == 'L') {
                    cin >> buffer;
                    tree.Load(buffer);
                    break;
                } else if (buffer[0] == 'S') {
                    cin >> buffer;
                    tree.Save(buffer);
                    break;
                }
                break;
            }
            default: {
                ToLower(buffer);
                tStart = clock();
                tmp = tree.Search(buffer);
                if (tmp) {
                    cout << "OK1: " << tmp->value << "\n";
                } else {
                    cout << "NoSuchWord\n";
                }
                MyFile1 << (double)(clock() - tStart) << ' ';
                clock_t t2Start = clock();
                cout << "OK2: " << m[buffer] << '\n';
                MyFile1 << (double)(clock() - t2Start) << '\n';
                break;
            }
        }
    }
    return 0;
}