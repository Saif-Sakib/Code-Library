#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = (ll)1e9 + 7;
using Mat = vector<vector<ll>>;

Mat mk_id(int n) {
    Mat id(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) id[i][i] = 1;
    return id;
}
 
Mat matmul(const Mat &A, const Mat &B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    Mat C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

Mat matexp(Mat base, ll exp) {
    if (exp == 0) return mk_id(base.size());
    Mat half = matexp(base, exp / 2);
    Mat res = matmul(half, half);
    if (exp & 1LL) res = matmul(res, base);
    return res;
}

// Example: Mat fib = {{1,1},{1,0}}; auto kth = matexp(fib, n-1); answer = kth[0][0];
