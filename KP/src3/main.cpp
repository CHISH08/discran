#include <iostream>
#include <sstream>
#include <unordered_map>
#include <queue>
using namespace std;

queue<short int> intersection(queue<short int> a, queue<short int> b) {
    queue<short int> intersect;
    while (!(a.empty() || b.empty())) {
        if (a.front() < b.front()) {
            a.pop();
        } else if (a.front() > b.front()) {
            b.pop();
        } else {
            intersect.push(a.front());
            a.pop();
            b.pop();
        }
    }
    return intersect;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int M, N;
    string text;
    unordered_map<string, queue<short int>> dict;
    cin >> N;
    getline(cin, text);
    for (int i = 0; i < N; ++i) {
        getline(cin, text);
        istringstream iss(text);
        while (iss >> text) {
            queue<short int> *part = &dict[text]; 
            if ((*part).empty() || ((*part).back() != i)) {
                (*part).push(i);
            }
        }
    }

    cin >> M;
    getline(cin, text);
    for (int i = 0; i < M; ++i) {
        string text;
        getline(cin, text);
        istringstream iss(text);
        iss >> text;
        queue<short int> prev = dict[text];
        while (iss >> text) {
            queue<short int> cur = dict[text];
            prev = intersection(prev, cur);
        }
        cout << prev.size() << ' ';
        while (!prev.empty()) {
            cout << prev.front() << ' ';
            prev.pop();
        }
        cout << '\n';
    }
}
