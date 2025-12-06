long long bigmod(long long b, long long e, long long mod) {
    if (e == 0) return 1 % mod;          
    long long half = bigmod(b, e / 2, mod);
    long long res = (half * half) % mod;
    if (e % 2 == 1)
        res = (res * b) % mod;
    return res;
}
