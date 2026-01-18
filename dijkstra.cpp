#include <bits/stdc++.h>
using namespace std;

// define
using ll = long long;
using ld = long double;
const int M = 1e9 + 7;
const int N = 1e6 + 3;
const ll inf = (ll)4e18;

vector<vector<pair<int, ll>>> gp;
vector<ll> dist;

void dijkstra(int src) {
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	dist[src] = 0;
	pq.push({0, src});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d != dist[u]) {
			continue;
		}
		for (auto [v, w] : gp[u]) {
			if (dist[v] > d + w) {
				dist[v] = d + w;
				pq.push({dist[v], v});
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	gp.assign(n, {});
	dist.assign(n, inf);
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		--u;
		--v;
		gp[u].push_back({v, w});             
	}

	int src;
	cin >> src;
	--src;
	dijkstra(src);

	for (int i = 0; i < n; i++) {
		if (dist[i] == inf) {
			cout << "INF\n";
			continue;
		}
		cout << dist[i] << '\n';
	}
	return 0;
}
