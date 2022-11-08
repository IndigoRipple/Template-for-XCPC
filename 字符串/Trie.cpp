// 字典树的根是 0
int nxt[][26], cnt;
bool exist[];

void insert(char s[], int n) {
    int p = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (!nxt[p][c]) nxt[p][c] = ++cnt;  // 如果没有，就添加结点
        p = nxt[p][c];
    }
    exist[p] = 1;
}

bool find(char s[], int n) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (!nxt[p][c]) return 0;
        p = nxt[p][c];
    }
    return exist[p];
}