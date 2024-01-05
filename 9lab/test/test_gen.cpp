#include<bits/stdc++.h>
#include <fstream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for (int n = 10; n <= 10000; n *= 10) {
        for (int m = 1; m <= n; m *= 10) {
            srand(55);
            ofstream File("testN"+to_string(n)+"M"+to_string(m)+".txt");
            int start = rand() % n + 1, finish = rand() % n + 1;
            File << n << ' ' << m << ' ' << start << ' ' << finish << '\n';
            for (int i = 0; i < m; ++i) {
                int v1 = rand() % n + 1, v2 = rand() % n + 1, w = rand() % 10;
                File << v1 << ' ' << v2 << ' ' << w << '\n';
            }
            File.close();
        }
    }
}
