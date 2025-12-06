#include <bits/stdc++.h>
using namespace std;

long long bigmod(long long b, long long e, long long mod) {
    if (e == 0) return 1 % mod;          
    long long half = bigmod(b, e / 2, mod);
    long long res = (half * half) % mod;
    if (e % 2 == 1)
        res = (res * b) % mod;
    return res;
}

struct Combi {
    long long mod;
    vector<long long> fact, invFact;

    Combi(int _n, long long m = 1000000007LL) : mod(m) {
        fact.resize(_n + 1);
        invFact.resize(_n + 1);

        fact[0] = 1;
        for (int i = 1; i <= _n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        invFact[_n] = bigmod(fact[_n], mod - 2, mod);

        for (int i = _n - 1; i >= 0; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
        }
    }

    long long nCr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
    }

    long long nPr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[n - r] % mod;
    }
};

// Combi val(200005); // Defaults to 1e9+7
// cout << val.nCr(10, 2) << endl;