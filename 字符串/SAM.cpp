char s[N]; // 下标从 1 开始
// 字符集过于奇葩的话 nxt 可以改成 map
int nxt[N * 2][26], len[N * 2], fa[N * 2], siz = 1, last = 1;

void append(const int& ch) {
    int p = last;
    int newp = last = ++siz;
    len[newp] = len[p] + 1;
    while (p && !nxt[p][ch]) {
        nxt[p][ch] = newp;
        p = fa[p];
    }
    if (!p) {
        fa[newp] = 1;
        return;
    }
    int q = nxt[p][ch];
    if (len[q] == len[p] + 1) {
        fa[newp] = q;
        return;
    }
    int newq = ++siz;
    fa[newq] = fa[q];
    for (int i = 0; i < 26; i++) nxt[newq][i] = nxt[q][i];
    len[newq] = len[p] + 1;
    fa[q] = fa[newp] = newq;
    while (p && nxt[p][ch] == q) {
        nxt[p][ch] = newq;
        p = fa[p];
    }
}

cin >> &s[1];
int n = strlen(&s[1]);