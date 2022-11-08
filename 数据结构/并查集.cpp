int fa[];
int cnt[]; // 各连通块大小

int find(const int& x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void uni(int u, int v) {
    u = find(u); v = find(v);
    if (u != v) {
        fa[v] = u;
        cnt[u] += cnt[v];
    }
}

int main() {
    int n, m;
    cin >> n >> m; // n 为点数，m 为边数
    iota(fa, fa + (n + 1), 0); // fa[i] = i
    fill(cnt, cnt + (n + 1), 1); // cnt[i] = 1
    while (m--) {
        int u, v;
        cin >> u >> v;
        uni(u, v);
    }
}