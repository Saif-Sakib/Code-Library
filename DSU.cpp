#include <bits/stdc++.h>
using namespace std;
vector<int> par, sz;

void init(int n){
    par.resize(n+1);
    sz.resize(n+1);
    for(int i = 1;i<=n;i++){
        par[i] = i;
        sz[i] = 1;
    }
}

int find(int u){
    if(par[u]==u)return u;
    return par[u] = find(par[u]);
}

void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(a==b)return;
    if(sz[a]<sz[b])swap(a,b);
    par[b] = a;
    sz[a] += sz[b];
}