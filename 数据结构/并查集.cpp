int fa[], cnt[]; // cnt 数组用于统计各个连通块里面的数据

void rar(const int& n) { for (int i = n; i > 0; --i) fa[i] = fa[fa[i]]; }

int main() {
    int n, m;
    cin >> n >> m; // n 为点数，m 为边数
    for (int i = n; i > 0; --i) fa[i] = i;
    while (m--) {
        int u, v;
        cin >> u >> v;
        while (u != fa[u]) u = fa[u];
        while (v != fa[v]) v = fa[v];
        if (u > v) swap(u, v);
        fa[v] = u;
        // magic_num 随便取，略大于根号 m，是 2 的幂的话 if 括号里面可以换成位运算
        if (!(m % magic_num)) rar(n);
    }
    int blockcnt = 0; // 连通块数量
    for (int i = 1; i <= n; ++i)
        if (fa[i] == i) {
            ++blockcnt;
            // cnt[i] 是这个连通块的数据
        } else cnt[fa[i]] += cnt[i]; // 把连通块里面各个点的数据传给根节点
}