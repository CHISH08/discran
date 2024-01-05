#include <iostream>
#include <vector>
#include <map>
using namespace std;

unsigned int INF = 1e9+1;

void dekstra(int start, int finish, int n, vector<map<int, int>> graph){
    map<unsigned long long, unsigned> matrix;
    matrix[0] = start;
    vector<bool> used (n);
    used[start] = true;
    map<unsigned, unsigned long long> ans;
    ans[start] = 0;
    while (!matrix.empty()) {
        unsigned node = matrix.begin()->second;
        matrix.erase(matrix.begin());
        if (node == finish) {
            break;
        }
        for (auto i: graph[node]) {
            if (!used[i.first] || 
                ans[node] + i.second < ans[i.first])
            {
                matrix[ans[node] + i.second] = i.first;
                ans[i.first] = ans[node] + i.second;
                used[i.first] = true;
            }
        }
    }
    if (!used[finish]) {
        cout << "No solution\n";
    } else {
        cout << ans[finish] << '\n';
    }
}

int main() {
    int n, m, start, finish;
    cin >> n >> m >> start >> finish;
    --start, --finish;
    vector<map<int, int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        --v1, --v2;
        graph[v1][v2] = graph[v2][v1] = w;
    }
    dekstra(start, finish, n, graph);
    return 0;
}