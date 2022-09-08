// Tarjan
// 跑完之后，low 相同的结点属于同一个分量
vector<int> nxt[];
int dfn[], low[];
bool in_stack[];

void dfs(int x, int& dfn_) {
    in_stack[x] = 1;
    dfn[x] = low[x] = ++dfn_;
    for (auto i: nxt[x]) {
        if (!dfn[i]) {
            dfs(i, dfn_);
            low[x] = min(low[x], low[i]);
        } else if (in_stack[i]) {
            low[x] = min(low[x], dfn[i]);
        }
    }
    in_stack[x] = 0;
}

void tarjan() {
    int dfn_ = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, dfn_);
        }
    }
}