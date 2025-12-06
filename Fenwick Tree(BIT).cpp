#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
	int n;
	vector<long long> bit;

	Fenwick(int n_) {
		n = n_;
		bit.assign(n + 1, 0);
	}

	void add(int idx, long long delta) {
		for (; idx <= n; idx += idx & -idx) {
			bit[idx] += delta;
		}
	}

	long long sum(int idx) const {
		long long res = 0;
		for (; idx > 0; idx -= idx & -idx) {
			res += bit[idx];
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	if (!(cin >> n >> q)) return 0;
	vector<long long> a(n + 1);
	Fenwick ft(n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		ft.add(i, a[i]);
	}

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int idx;
			long long delta;
			cin >> idx >> delta;
			ft.add(idx, delta);
		} else if (type == 2) {
			int l, r;
			cin >> l >> r;
			long long ans = ft.sum(r);
			if(l!=0)ans-=ft.sum(l-1);
			cout << ans << '\n';
		}
	}
	return 0;
}
