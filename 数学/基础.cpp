int gcd(int a, int b) {
    while (b) tie(a, b) = make_tuple(b, a % b);
    return a;
}

int power(int x, int n) {
    int ret = 1;
    x %= mod;
    while (n) {
        if (n & 1) ret = ret * x % mod;
        x = 1LL * x * x % mod;
        n >>= 1;
    }
    return ret;
}

using matrix = vector<vector<int>>;
matrix operator*(const matrix& a, const matrix& b) {
    int n = a.size();
    matrix ret(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) ret[i][k] += a[i][j] * b[j][k] % mod;
            ret[i][k] %= mod;
        }
    }
    return ret;
}
matrix power(matrix x, int p) {
    int n = x.size();
    matrix ret(n, vector<int>(n));
    for (int i = 0; i < n; ++i) ret[i][i] = 1;
    while (p) {
        if (p & 1) ret = ret * x;
        x = x * x;
        p >>= 1;
    }
    return ret;
}

// ax + by = gcd(a, b)
int exgcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1;
    while (b) {
        int t = a / b;
        tie(x, x1) = make_tuple(x1, x - t * x1);
        tie(y, y1) = make_tuple(y1, y - t * y1);
        tie(a, b) = make_tuple(b, a - t * b);
    }
    return a;
}

// p 要是质数
inline int inv(const int& x) {
    return power(x, mod - 2);
}

int C(const int& n, int m) { // 硬算版
    m = min(m, n - m);
    if (m < 0) return 0;
    int ret = 1;
    for (int i = 0; i < m; ++i) ret = 1LL * ret * (n - i) % mod * inv(i + 1) % mod;
    return ret;
}
int C(const int& n, const int& m) { // 递归版
    return min(m, n - m) < 0 ? 0 : fact[n] * inv(fact[m]) % mod * inv(fact[n - m]) % mod;
}

int A(const int& n, const int& m) { // 硬算版
    int ret = 1;
    for (int i = 0; i < m; ++i) ret = 1LL * ret * (n - i) % mod;
    return ret;
}

bool notprime[];
int prime[], primecnt = 0;
void sieve(const int& n) {
    for (int i = 2; i <= n; ++i) {
        if (!notprime[i]) prime[primecnt++] = i;
        for (int j = 0; j < primecnt && 1LL * i * prime[j] <= n; ++j) {
            notprime[i * prime[j]] = 1;
            if (!(i % prime[j])) break;
        }
    }
}

// 模意义下的快速乘
long long multi(const long long& x, const long long& y) {
    long long temp = (long double)x / mod * y;
    long long res = (unsigned long long)x * y - (unsigned long long)temp * mod;
    return (res + mod) % mod;
}