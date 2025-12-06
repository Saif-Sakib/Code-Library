#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
	ll m, b;                                        // y = m * x + b
	ll eval(ll x) const { return m * x + b; }
};

class LiChaoTree {
public:
	LiChaoTree(ll minX, ll maxX, bool queryMin = true)
		: L(minX), R(maxX), isMinQuery(queryMin), root(nullptr) {}

	void addLine(ll m, ll b) { insertLine(root, L, R, {m, b}); }

	void addSegmentLine(ll ql, ll qr, ll m, ll b) {
		ql = max(ql, L);
		qr = min(qr, R);
		if (ql > qr) return;
		insertSegment(root, L, R, ql, qr, {m, b});
	}

	ll query(ll x) const { return query(root, L, R, x); }

private:
	static constexpr ll INF = 1LL << 62;

	struct Node {
		Line line;
		Node *left, *right;
		explicit Node(const Line &ln) : line(ln), left(nullptr), right(nullptr) {}
	};

	ll L, R;
	bool isMinQuery;
	Node *root;

	ll neutralValue() const { return isMinQuery ? INF : -INF; }

	bool better(ll a, ll b) const { return isMinQuery ? (a < b) : (a > b); }

	ll best(ll a, ll b) const { return better(a, b) ? a : b; }

	Line neutralLine() const { return {0, neutralValue()}; }

	void insertLine(Node *&node, ll l, ll r, Line ln) {
		if (!node) {
			node = new Node(ln);
			return;
		}
		ll mid = l + ((r - l) >> 1);
		bool midBetter = better(ln.eval(mid), node->line.eval(mid));
		if (midBetter) swap(node->line, ln);
		if (l == r) return;
		bool leftBetter = better(ln.eval(l), node->line.eval(l));
		bool rightBetter = better(ln.eval(r), node->line.eval(r));
		if (leftBetter != midBetter) insertLine(node->left, l, mid, ln);
		else if (rightBetter != midBetter) insertLine(node->right, mid + 1, r, ln);
	}

	void insertSegment(Node *&node, ll l, ll r, ll ql, ll qr, const Line &ln) {
		if (qr < l || r < ql) return;
		if (!node) node = new Node(neutralLine());
		if (ql <= l && r <= qr) {
			insertLine(node, l, r, ln);
			return;
		}
		ll mid = l + ((r - l) >> 1);
		insertSegment(node->left, l, mid, ql, qr, ln);
		insertSegment(node->right, mid + 1, r, ql, qr, ln);
	}

	ll query(Node *node, ll l, ll r, ll x) const {
		if (!node) return neutralValue();
		ll res = node->line.eval(x);
		if (l == r) return res;
		ll mid = l + ((r - l) >> 1);
		if (x <= mid) return best(res, query(node->left, l, mid, x));
		return best(res, query(node->right, mid + 1, r, x));
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Example usage:
	// Q operations on Li Chao tree over x in [0, 1e6].
	int Q;
	cin >> Q;
	LiChaoTree cht(0, 1'000'000);                    // default is min queries
	while (Q--) {
		int type;
		cin >> type;
		if (type == 1) {
			ll m, b;
			cin >> m >> b;
			cht.addLine(m, b);
		} else if (type == 2) {
			ll l, r, m, b;
			cin >> l >> r >> m >> b;
			cht.addSegmentLine(l, r, m, b);
		} else {
			ll x;
			cin >> x;
			cout << cht.query(x) << '\n';
		}
	}
	return 0;
}

