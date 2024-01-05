#include <cstdlib>
#include<bits/stdc++.h>
using namespace std;

int main() {
    for (int n = 10; n <= 10000; n *= 10) {
        for (int m = 1; m <= n; m *= 10) {
            string command = "./a.out < ../test/testN" + to_string(n) + "M" + to_string(m) + ".txt";
            const char *cmd = command.c_str();
            auto start_time = chrono::steady_clock::now();
            system(cmd);
            auto end_time = chrono::steady_clock::now();
            auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "n = " << n << ", m = " << m << " time: " << elapsed_ns.count() << " ns\n";
        }
    }
    return 0;
}