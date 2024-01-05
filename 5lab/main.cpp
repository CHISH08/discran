#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

const int ALPHABET_SIZE = 27;
const char END_CHAR = '$';
const size_t INTERNAL_NODE = static_cast<size_t>(-1);

class SuffixTree {
public:
    SuffixTree(const string &input) : text(input + END_CHAR) {
        rootNode = new Node(0, 0, INTERNAL_NODE, nullptr);

        activeNode = rootNode;
        activeEdgeIndex = 0;
        activeLength = 0;

        remainingSuffixes = 0;

        globalEnd = -1;
        suffixCount = 0;

        size_t length = text.length();

        for (size_t i = 0; i < length; i++) {
            AddSuffix(i);
        }
    }

    ~SuffixTree() {
        DeleteSubtree(rootNode);
    }

    void AddSuffix(size_t phaseNum) {
        remainingSuffixes++;
        globalEnd++;

        Node *lastAddedInternalNode = nullptr;

        while (remainingSuffixes > 0) {
            if (activeLength == 0) {
                activeEdgeIndex = phaseNum;
            }

            if (activeNode->GetEdge(text, activeEdgeIndex) == nullptr) {
                activeNode->GetEdge(text, activeEdgeIndex) = new Node(phaseNum, &globalEnd, suffixCount, nullptr);

                suffixCount++;
                remainingSuffixes--;

                if (lastAddedInternalNode != nullptr) {  
                    lastAddedInternalNode->suffixLink = activeNode;
                    lastAddedInternalNode = nullptr;
                }
            } else {
                if (TryWalkdown())
                    continue;
                if (GetNextChar() == text[phaseNum]) {
                    if (lastAddedInternalNode != nullptr && activeNode != rootNode) {
                        lastAddedInternalNode->suffixLink = activeNode;
                        lastAddedInternalNode = nullptr;
                    }
                    activeLength++;
                    break;
                } else {
                    Node *toInsert = new Node(phaseNum, &globalEnd, suffixCount, nullptr);
                    suffixCount++;

                    Node *justInserted = CreateInternalNode(toInsert);
                    if (lastAddedInternalNode != nullptr) {
                        lastAddedInternalNode->suffixLink = justInserted;
                    }
                    lastAddedInternalNode = justInserted;
                    remainingSuffixes--;
                }
            }
            if (activeNode == rootNode) {
                if (activeLength > 0) {
                    activeLength--;
                    activeEdgeIndex = phaseNum - remainingSuffixes + 1;
                }
            } else {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    vector<int> GetMatchStatistics(const string &text);
    vector<int> GetMatchStatisticsNaive(const string &text);

private:
    struct Node {
        Node *edges[ALPHABET_SIZE];
        size_t start;
        size_t *end;
        size_t id;
        Node *suffixLink;

        Node(size_t start, size_t *end, size_t id, Node *link)
            : start(start), end(end), id(id), suffixLink(link) {
            for (auto &edge : edges) {
                edge = nullptr;
            }
        }

        Node *&GetEdge(const string &str, size_t edgeIndex) {
            size_t index = (str[edgeIndex] == END_CHAR ? 26 : str[edgeIndex] - 'a');
            return edges[index];
        }

        size_t GetStart() const {
            return start;
        }

        size_t GetEnd() const {
            return id == INTERNAL_NODE ? *end : *end;
        }

        size_t GetLength() const {
            return GetEnd() - GetStart() + 1;
        }

        void Print(const string &str) const {
            for (size_t i = start; i <= GetEnd(); i++) {
                cout << str[i];
            }
            if (id != INTERNAL_NODE) {
                cout << " - " << id;
            }
        }
    };

    string text;
    Node *rootNode;

    Node *activeNode;
    size_t activeEdgeIndex;
    size_t activeLength;

    size_t globalEnd;
    size_t remainingSuffixes;
    size_t suffixCount;

    int TryWalkdown() {
        Node *edge = activeNode->GetEdge(text, activeEdgeIndex);
        size_t edgeLength = edge->GetLength();
        if (activeLength >= edgeLength) {
            activeLength -= edgeLength;
            activeEdgeIndex += edgeLength;
            activeNode = edge;
            return 1;
        }
        return 0;
    }

    char GetNextChar() const {
        size_t index = activeNode->GetEdge(text, activeEdgeIndex)->GetStart() + activeLength;
        return text[index];
    }

    Node *CreateInternalNode(Node *toInsert) {
        Node *edge = activeNode->GetEdge(text, activeEdgeIndex);
        size_t edgeStart = edge->GetStart();
        Node *newInternalNode = new Node(edgeStart, new size_t(edgeStart + activeLength - 1), INTERNAL_NODE, rootNode);
        newInternalNode->GetEdge(text, edgeStart + activeLength) = edge;
        edge->start = edgeStart + activeLength;
        newInternalNode->GetEdge(text, toInsert->GetStart()) = toInsert;
        activeNode->GetEdge(text, activeEdgeIndex) = newInternalNode;
        return newInternalNode;
    }

    void PrintNode(Node *node, int indentLevel) const {
        const int tabIncrement = 3;
        if (node == nullptr)
            return;
        for (int i = 0; i < indentLevel; i++) {
            cout << ' ';
        }
        node->Print(text);
        cout << endl;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            PrintNode(node->edges[i], indentLevel + tabIncrement);
        }
    }

    void DeleteSubtree(Node *node) {
        if (node == nullptr)
            return;
        if (node->id != INTERNAL_NODE) {
            delete node;
            return;
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            DeleteSubtree(node->edges[i]);
        }
        delete node;
    }

    void PrintSuffixLinks(Node *node) const {
        if (node == nullptr)
            return;
        if (node->suffixLink != nullptr) {
            cout << "[ " << node->GetStart() << " , " << node->GetEnd() << " ]"
                 << " --> ";
            Node *sl = node->suffixLink;
            if (sl == rootNode) {
                cout << "ROOT";
            } else if (sl == nullptr) {
                cout << "NULL";
            } else {
                cout << "[ " << sl->GetStart() << " , " << sl->GetEnd() << " ]";
            }
            cout << endl;
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            PrintSuffixLinks(node->edges[i]);
        }
    }
};

vector<int> SuffixTree::GetMatchStatistics(const string &searchText) {
    size_t textLength = searchText.length();
    vector<int> result(textLength);

    Node *currentNode = rootNode;
    Node *nextNode;
    size_t edgeIndex = 0;
    size_t matchedLength = 0;

    size_t searchIndex = 0;

    for (size_t i = 0; i < textLength; i++) {
        if (matchedLength == 0) {
            nextNode = currentNode->GetEdge(searchText, searchIndex);
        } else {
            nextNode = currentNode->GetEdge(text, edgeIndex);
        }

        if (nextNode != nullptr) {
            size_t edgeLength = nextNode->GetLength();
            while (matchedLength > edgeLength) {
                edgeIndex += edgeLength;
                matchedLength -= edgeLength;
                currentNode = nextNode;
                nextNode = nextNode->GetEdge(text, edgeIndex);
                edgeLength = nextNode->GetLength();
            }
            assert(nextNode != nullptr);
            while (true) {
                if (nextNode->GetLength() == matchedLength) {
                    matchedLength = 0;
                    currentNode = nextNode;
                    nextNode = nextNode->GetEdge(searchText, searchIndex);
                }
                if (nextNode == nullptr || text[nextNode->GetStart() + matchedLength] != searchText[searchIndex]) {
                    break;
                }
                matchedLength++;
                searchIndex++;
                if (searchIndex >= textLength) {
                    for (size_t k = i; k < textLength; k++) {
                        result[k] = searchIndex - k;
                    }
                    return result;
                }
            }
            if (nextNode != nullptr) {
                edgeIndex = nextNode->GetStart();
            }
        }

        result[i] = searchIndex - i;

        if (currentNode == rootNode) {
            if (matchedLength > 0) {
                matchedLength--;
                edgeIndex++;
            } else {
                searchIndex++;
            }
        } else {
            currentNode = currentNode->suffixLink;
        }
    }

    return result;
}

int main() {
    clock_t tStart = clock();
    string pattern;
    cin >> pattern;

    SuffixTree tree(pattern);

    string text;
    cin >> text;

    vector<int> matchStatistics = tree.GetMatchStatistics(text);

    size_t patternLength = pattern.length();
    size_t statisticsSize = matchStatistics.size();
    for (size_t i = 0; i < statisticsSize; i++) {
        if (matchStatistics[i] == patternLength) {
            // cout << i + 1 << '\n';
        }
    }
    cout << "Pattern size: " << pattern.size() << "\nText size: " << text.size() << "\nTime: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << '\n';

    return 0;
}