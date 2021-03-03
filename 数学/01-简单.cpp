int gcd(int a, int b) {
    while (b) tie(a, b) = make_tuple(b, a % b);
    return a;
}

int power(int x, int n) {
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
int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1;
    while (b) {
        int t = a / b;
        tie(x, x1) = make_tuple(x1, x - t * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a, b) = make_tuple(b, a - q * b);
    }
    return a;
}