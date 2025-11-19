#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int>a;

class SegTree {
public:
    int n;                    
    vector<ll> tree;

    SegTree(int size) { n = size; tree.assign(4 * n, 0LL); }

    void build(int node, int st, int en) {
        if (st == en) { tree[node] = a[st]; return; }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int node, int st, int en, int l, int r) {
        if (st > r || en < l) return 0;
        if (st >= l && en <= r) return tree[node];
        int mid = (st + en) / 2;
        ll q1 = query(node * 2, st, mid, l, r);
        ll q2 = query(node * 2 + 1, mid + 1, en, l, r);
        return q1 + q2;
    }

    void update(int node, int st, int en, int idx, ll val) {
        if (st == en) { tree[node] = val; return; }
        int mid = (st + en) / 2;
        if (idx <= mid) update(node * 2, st, mid, idx, val);
        else            update(node * 2 + 1, mid + 1, en, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
};

class LazySegTree {
public:
    int n;                   
    vector<ll> tree;
    vector<ll> lazyAdd;
    vector<ll> lazySet; 
    vector<bool> hasSet;

    LazySegTree(int size) { 
        n = size;
        tree.assign(4 * n, 0LL);
        lazyAdd.assign(4 * n, 0LL);
        lazySet.assign(4 * n, 0LL);
        hasSet.assign(4 * n, 0); 
    }

    void build(int node, int st, int en) {
        if (st == en) { tree[node] = a[st]; return; }
        int mid = (st + en) / 2;
        build(node * 2, st, mid);
        build(node * 2 + 1, mid + 1, en);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void set(int node, int st, int en, int l, int r, ll val){
        if(st>r || en<l)return;
        if(st>=l && en<=r){
            tree[node] = (en-st+1) * val;
            hasSet[node] = 1;
            lazySet[node] = val;
            lazyAdd[node] = 0;
            return;
        }
        push(node, st, en);
        int mid = (st+en)/2;
        set(node*2, st, mid, l, r, val);
        set(node*2+1, mid+1, en, l, r, val);
        tree[node] = tree[node*2] + tree[2*node+1];
    }

    void add(int node, int st, int en, int l, int r, ll val) {
        if (st > r || en < l) return;
        if (st >= l && en <= r) {
            tree[node] += (en - st + 1) * val;
            lazyAdd[node] += val;
            return;
        }
        push(node, st, en);
        int mid = (st + en) / 2;
        add(node * 2, st, mid, l, r, val);
        add(node * 2 + 1, mid + 1, en, l, r, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int node, int st, int en, int l, int r) {
        if (st > r || en < l) return 0;
        if (st >= l && en <= r) return tree[node];
        push(node, st, en);
        int mid = (st + en) / 2;
        return query(node * 2, st, mid, l, r) + query(node * 2 + 1, mid + 1, en, l, r);
    }

    void push(int node, int st, int en) {
        if (st == en) return;
        int lc = node * 2, rc = node * 2 + 1;
        int mid = (st + en) / 2;

        if (hasSet[node]) {
            ll v = lazySet[node];
            tree[lc] = (ll)(mid - st + 1) * v;
            hasSet[lc] = 1;
            lazySet[lc] = v;
            lazyAdd[lc] = 0;
            tree[rc] = (ll)(en - mid) * v;
            hasSet[rc] = 1;
            lazySet[rc] = v;
            lazyAdd[rc] = 0;
            hasSet[node] = 0;
        }

        if (lazyAdd[node] != 0) {
            ll v = lazyAdd[node];
            tree[lc] += (ll)(mid - st + 1) * v;
            tree[rc] += (ll)(en - mid) * v;
            lazyAdd[lc] += v;
            lazyAdd[rc] += v;
            lazyAdd[node] = 0;
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
            ll ans = seg.query(1, 0, n-1, l, r);
            cout<<ans<<'\n';
        }
    }
}
