// 用的 Trie 那里的字典树
int fail[];

struct _ {
    int pos, fa, ch;
};

queue<_> q;
for (int i = 0; i < 26; i++) {
    if (nxt[0][i]) {
        q.push({nxt[0][i], 0, i});
    }
}
while (!q.empty()) {
    auto qf = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
        if (nxt[qf.pos][i]) {
            q.push({nxt[qf.pos][i], qf.pos, i});
        }
    }
    if (qf.fa) {
        qf.fa = fail[qf.fa];
        while (qf.fa) {
            if (nxt[qf.fa][qf.ch]) {
                fail[qf.pos] = nxt[qf.fa][qf.ch];
                break;
            } else qf.fa = fail[qf.fa];
        }
    }
    if (!fail[qf.pos] && nxt[0][qf.ch] && nxt[0][qf.ch] != qf.pos) fail[qf.pos] = nxt[0][qf.ch];
}