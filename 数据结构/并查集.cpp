int fa[];
int cnt[]; // 各连通块大小

int find(const int& x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
    int n, m;
    cin >> n >> m; // n 为点数，m 为边数
    iota(fa, fa + (n + 1), 0);
    fill(cnt, cnt + (n + 1), 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        fa[u] = find(u); fa[v] = find(v);
        if (cnt[fa[u]] < cnt[fa[v]]) swap(u, v);
        cnt[fa[u]] += cnt[fa[v]];
        fa[fa[v]] = fa[u];
    }
}