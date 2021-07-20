// Tarjan
// 跑完之后，low 相同的结点属于同一个分量
vector<vector<int>> nxt;
int n, dfn[], low[]; // n 是结点数
struct _ {
    int id, visiting;
};

void tarjan() {
    int dfncnt = 0;
    stack<_> s;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) {
            dfn[i] = low[i] = ++dfncnt;
            s.push({i, -1});
            while (!s.empty()) {
                _& st = s.top();
                if (st.visiting >= 0) low[st.id] = min(low[st.id], low[nxt[st.id][st.visiting]]);
                ++st.visiting;
                if (st.visiting >= nxt[st.id].size()) {
                    s.pop();
                    continue;
                }
                if (!dfn[nxt[st.id][st.visiting]]) {
                    dfn[nxt[st.id][st.visiting]] = low[nxt[st.id][st.visiting]] = ++dfncnt;
                    s.push({nxt[st.id][st.visiting], -1});
                }
            }
        }
}