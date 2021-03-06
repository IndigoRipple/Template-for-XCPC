int gcd(int a, int b) {
    while (b) tie(a, b) = make_tuple(b, a % b);
    return a;
}

int power(int x, int n, const int& mod = mod) {
    int ret = 1;
    while (n) {
        if (n & 1) ret = 1LL * ret * x % mod;
        x = 1LL * x * x % mod;
        n >>= 1;
    }
    return ret;
}

using matrix = array<array<int, N>, N>;
matrix operator*(const matrix& a, const matrix& b) {
    matrix ret;
    for (auto&& i: ret)
        for (auto&& j: i)
            j = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                ret[i][k] = (ret[i][k] + 1LL * a[i][j] * b[j][k]) % mod;
    return ret;
}
matrix power(matrix x, int n) {
    matrix ret;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            ret[i][j] = i == j;
    while (n) {
        if (n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
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

// p must be a prime
inline int inverse(const int& x) {
    return power(x, mod - 2, mod);
}

int C(const int& n, int m) {
    int ret = 1;
    m = min(m, n - m);
    for (int i = 0; i < m; ++i) ret = 1LL * ret * (n - i) % mod * inverse(i + 1) % mod;
    return ret;
}

int A(const int& n, const int& m) {
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