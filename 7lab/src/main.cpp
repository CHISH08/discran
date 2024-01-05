#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

struct par {
    char y;
    long long val = 0;
};

int main(){
    auto start_time = chrono::steady_clock::now();
	long long n;
	cin >> n;
    cout << "Number: " << n << '\n';
	vector<par> x(n+1);
    for (long long i = n; i >= 2; --i) {

        if ((i != n) && (x[i].val == 0)) {
            continue;
        }

        x[i].val += i;
        if ((i % 3 == 0) && ((x[i/3].val == 0) || (x[i/3].val > x[i].val))) {
            x[i/3].val = x[i].val;
            x[i/3].y = '3';
        }
        if ((i % 2 == 0) && ((x[i/2].val == 0) || (x[i/2].val > x[i].val))) {
            x[i/2].val = x[i].val;
            x[i/2].y = '2';
        }
        if ((i > 2) && ((x[i-1].val == 0) || (x[i-1].val > x[i].val))) {
            x[i-1].val = x[i].val;
            x[i-1].y = '1';
        }
    }

    // cout << x[1].val << "\n";

    long long i = 1;
    vector<string> vec;

    while (i != n) {

        if (x[i].y == '3') {
            vec.push_back("/3 ");
            i *= 3;
        } else if (x[i].y == '2') {
            vec.push_back("/2 ");
            i *= 2;
        } else {
            vec.push_back("-1 ");
            ++i;
        }
    }

    // for (int i = vec.size()-1; i >= 0; --i) {
    //     cout << vec[i];
    // }
    // cout << "\n";
    auto end_time = chrono::steady_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    cout << "Time: " << elapsed_ns.count() << " ns\n";

    return 0;
}