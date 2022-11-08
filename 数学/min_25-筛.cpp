// 质数表下标要从 1 开始，最多筛到 sqrt(n)
// 如果 f() 是个多项式，g[] 和 sum[] 要对每个单项式分别计算，最后合并

const int N, mod; // N = sqrt(max_n from input)
int n, n_sqrt, m, w[N * 2], id1[N], id2[N], g[N * 2], sum[N];
vector<int> prime({0});

int f(int p);

int f_sum(int x); // f[1...x] 的和（全部视为质数计算）

int f_c(int p, int c); // f(power(p, c))

int S(int x, int y) { // ans = S(n, 0) + f(1)
    if (x <= 1 || prime[y] > x) return 0;
    int k = x <= n_sqrt ? id1[x] : id2[n / x];
    int ret = (g[k] - sum[y] + mod) % mod;
    for (int i = y + 1; i < prime.size() && prime[i] * prime[i] <= x; i++) {
        int& I = prime[i];
        for (int c = 2, p_c = I * I; p_c <= x; c++, p_c *= I) {
            ret = (ret + f_c(I, c) + f_c(I, c - 1) * S(x / (p_c / I), i)) % mod;
        }
    }
    return ret;
}

for (int i = 1; i < prime.size(); i++) sum[i] = (sum[i - 1] + f(prime[i])) % mod;
for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    w[++m] = n / l;
    (w[m] <= n_sqrt ? id1[w[m]] : id2[n / w[m]]) = m;
    g[m] = f_sum(w[m]) - f(1);
    if (g[m] < 0) g[m] += mod;
}
for (int j = 1; j < prime.size(); j++) {
    int& J = prime[j];
    for (int i = 1; i <= m && J * J <= w[i]; i++) {
        int k = w[i] / J <= n_sqrt ? id1[w[i] / J] : id2[n / (w[i] / J)];
        g[i] = (g[i] - g[k] + sum[j - 1]) % mod;
        if (g[i] < 0) g[i] += mod;
    }
}