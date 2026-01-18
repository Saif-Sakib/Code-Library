#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, k;
vector<vector<int>> g;
vector<int> cen, sz, tin, tout, node, dep;
ll ans;

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p || cen[v]) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

int get(int u, int p, int tot) {
    for (int v : g[u]) {
        if (v == p || cen[v]) continue;
        if (sz[v] > tot / 2) return get(v, u, tot);
    }
    return u;
}

int t;
void dfs(int u, int p) {
    node[t] = u;
    tin[u] = t++;
    for (int v : g[u]) {
        if (v == p || cen[v]) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    tout[u] = t - 1;
}

void go(int u) {
    dfs_sz(u, -1);
    int tot = sz[u];
    int c = get(u, -1, tot);
    cen[c] = 1;

    t = 0;
    dep[c] = 0;
    dfs(c, -1);

    vector<int> cnt(tot);
    cnt[0] = 1;
    for (int v : g[c]) {
        if (cen[v]) continue;
        for (int i = tin[v]; i <= tout[v]; ++i) {
            int w = node[i];
            int need = k - dep[w];
            if (need >= 0 && need < tot) ans += cnt[need];
        }
        for (int i = tin[v]; i <= tout[v]; ++i) {
            int w = node[i];
            if (dep[w] < tot) cnt[dep[w]]++;
        }
    }

    for (int v : g[c]) if (!cen[v]) go(v);
}

int main() {
    cin >> n >> k;
    g.assign(n, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cen.assign(n, 0);
    sz.assign(n, 0);
    tin.assign(n, 0);
    tout.assign(n, 0);
    node.assign(n, 0);
    dep.assign(n, 0);
    ans = 0;
    go(0);
    cout << ans << '\n';
    return 0;
}