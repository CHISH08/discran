#include<bits/stdc++.h>
#include <fstream>
using namespace std;

int main() {
    for (int n = 10, i=0; n < 1000000; n *= 10, ++i) {
        srand(55);
        ofstream File("test"+to_string(i)+".txt");
        File << n << "\n";
        for (int j = 0; j < n; ++j) {
            int a = rand() % 10000, b = rand() % 10000;
            if (a > b) swap(a,b);
            File << a << " " << b << "\n";
        }
        File << rand() % 10000;
        File.close();
    }
}