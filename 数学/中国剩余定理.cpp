long long crt(const int*& a, const int*& m, const int& n) {
    long long M = accumulate(m, m + n, 1LL, multiplies<long long>()), ans = 0;
    vector<long long> t(n), t_(n);
    for (int i = n - 1; i >= 0; --i) {
        t[i] = M / m[i];
        t_[i] = inv(t[i], m[i]);
    }
    for (int i = n - 1; i >= 0; --i) ans = (ans + t[i] % M * a[i] % M * t_[i] % M) % M;
    return ans;
}