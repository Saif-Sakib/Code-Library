#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int>a;

struct Node {
    ll sum;
    Node() { sum = 0; }
};

Node merge(const Node &lhs, const Node &rhs) {
    Node ret;
    ret.sum = lhs.sum + rhs.sum;
    return ret;
}

class SegTree {
public:
    int n;
    vector<Node> seg;

    SegTree(int size) : n(size), seg(4 * size) {}

    void build(int node, int st, int en) {
        if (st == en) { seg[node].sum = a[st]; return; }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    Node query(int node, int st, int en, int l, int r) {
        if (st > r || en < l) return Node();
        if (st >= l && en <= r) return seg[node];
        int mid = (st + en) / 2;
        Node left = query(node * 2, st, mid, l, r);
        Node right = query(node * 2 + 1, mid + 1, en, l, r);
        return merge(left, right);
    }

    void update(int node, int st, int en, int idx, ll val) {
        if (st == en) { seg[node].sum = val; return; }
        int mid = (st + en) / 2;
        if (idx <= mid) update(node * 2, st, mid, idx, val);
        else            update(node * 2 + 1, mid + 1, en, idx, val);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }
};

class LazySegTree {
public:
    int n;
    vector<Node> seg;
    vector<ll> lzAdd; // add value
    vector<ll> lzSet; // assign value
    vector<bool> hasSet;

    LazySegTree(int size)
        : n(size),
          seg(4 * size),
          lzAdd(4 * size, 0LL),
          lzSet(4 * size, 0LL),
          hasSet(4 * size, false) {}

    void build(int node, int st, int en) {
        if (st == en) { seg[node].sum = a[st]; return; }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    void set(int node, int st, int en, int l, int r, ll val){
        if(st>r || en<l)return;
        if(st>=l && en<=r){
            seg[node].sum = (ll)(en - st + 1) * val;
            hasSet[node] = 1;
            lzSet[node] = val;
            lzAdd[node] = 0;
            return;
        }
        push(node, st, en);
        int mid = (st+en)/2;
        set(node*2, st, mid, l, r, val);
        set(node*2+1, mid+1, en, l, r, val);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    void add(int node, int st, int en, int l, int r, ll val) {
        if (st > r || en < l) return;
        if (st >= l && en <= r) {
            seg[node].sum += (ll)(en - st + 1) * val;
            lzAdd[node] += val;
            return;
        }
        push(node, st, en);
        int mid = (st + en) / 2;
        add(node * 2, st, mid, l, r, val);
        add(node * 2 + 1, mid + 1, en, l, r, val);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    Node query(int node, int st, int en, int l, int r) {
        if (st > r || en < l) return Node();
        if (st >= l && en <= r) return seg[node];
        push(node, st, en);
        int mid = (st + en) / 2;
        Node left = query(node * 2, st, mid, l, r);
        Node right = query(node * 2 + 1, mid + 1, en, l, r);
        return merge(left, right);
    }

    void push(int node, int st, int en) {
        if (st == en) return;
        int lc = node * 2, rc = node * 2 + 1;
        int mid = (st + en) / 2;

        if (hasSet[node]) {
            ll v = lzSet[node];
            ll leftLen = mid - st + 1;
            ll rightLen = en - mid;
            seg[lc].sum = leftLen * v;
            hasSet[lc] = 1;
            lzSet[lc] = v;
            lzAdd[lc] = 0;
            seg[rc].sum = rightLen * v;
            hasSet[rc] = 1;
            lzSet[rc] = v;
            lzAdd[rc] = 0;
            hasSet[node] = 0;
        }

        if (lzAdd[node] != 0) {
            ll v = lzAdd[node];
            ll leftLen = mid - st + 1;
            ll rightLen = en - mid;
            seg[lc].sum += leftLen * v;
            seg[rc].sum += rightLen * v;
            lzAdd[lc] += v;
            lzAdd[rc] += v;
            lzAdd[node] = 0;
        }
    }
};


int main(){
    int n, q;
    cin>>n>>q;
    a = vector<int>(n);
    for(int i = 0;i<n;i++){
        cin>>a[i];
    }
    SegTree seg(n);
    seg.build(1,0,n-1);
    while(q--){
        int t;
        cin>>t;
        if(t==1){
            int idx; ll val;
            cin>>idx>>val;
            idx--;
            seg.update(1, 0, n-1, idx, val);
        }
        else{
            int l, r;
            cin>>l>>r;
            l--; r--;
            Node ans = seg.query(1, 0, n-1, l, r);
            cout<<ans.sum<<'\n';
        }
    }
}
