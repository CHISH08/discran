#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Piec {
	int l;
	int r;
	int ind;
};

bool oper(Piec &a, Piec &b) {
	return a.ind < b.ind;
}

void alg(vector<Piec> &pie, int m) {
	vector<Piec> answer;
	Piec begin;
	begin.l = 0;
	begin.r = 0;
	answer.push_back(begin);
	while (answer.back().r < m) {
		int max = 0;
		int index = -1;
		for (int i = 0; i < pie.size(); i++) {
			if (pie[i].l <= answer.back().r && pie[i].r > answer.back().r) {
				if (pie[i].r > max) {
					max = pie[i].r;
					index = i;
				}
			}
		}
		if (index == -1) {
			// cout << "0\n";
			return;
		} else {
			answer.push_back(pie[index]);
		}
	}

	sort(answer.begin() + 1, answer.end(), oper);
	// cout << answer.size() - 1 << '\n';
	// for (int i = 1; i < answer.size(); i++) {
	// 	cout << answer[i].l << " " << answer[i].r << '\n';
	// }
	return;

}

int main() {
	auto start_time = chrono::steady_clock::now();
	int n, m;
	cin >> n;
	vector<Piec> pie(n);
	for (int i = 0; i < n; i++) {
		pie[i].ind = i;
		cin >> pie[i].l >> pie[i].r; 
	}
	cin >> m;
	cout << "Count of numbers: " << n << '\n';
	cout << "m: " << m << '\n';
	alg(pie, m);
	auto end_time = chrono::steady_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    cout << "Time: " << elapsed_ns.count() << " ns\n";
	return 0;
}