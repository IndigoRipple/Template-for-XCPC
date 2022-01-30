int fa[]; // 父亲
int son[]; // 重儿子
int dep[];
int cnt[]; // 该点为根节点的子树大小
int top[]; // 该点所属重链顶上那个点
int dfn[]; // dfs 序

void dfs1(const int& x, vector<set<int>>& sons) {
    for (const auto& i: sons[x]) {
        fa[i] = x;
        dep[i] = dep[x] + 1;
        sons[i].erase(x);
        dfs1(i, sons);
        cnt[x] += cnt[i];
        if (cnt[i] > cnt[son[x]]) son[x] = i;
    }
    sons[x].erase(son[x]);
}

// 第一次调用传入 dfn_ 值为 0
void dfs2(const int& x, const vector<set<int>>& sons, int& dfn_) {
    top[x] = x == son[fa[x]] ? top[fa[x]] : x;
    dfn[x] = mx[x] = ++dfn_;
    if (son[x]) {
        dfs2(son[x], sons, dfn_);
        mx[x] = max(mx[x], mx[son[x]]);
    }
    for (const auto& i: sons[x]) {
        dfs2(i, sons, dfn_);
        mx[x] = max(mx[x], mx[i]);
    }
}

void init(const int& n, const int& root) {
    iota(fa + 1, fa + (n + 1), 1);
    fill(cnt + 1, cnt + (n + 1), 1);
    fa[root] = root;
}