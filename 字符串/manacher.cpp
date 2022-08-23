char s[]; // 下标从 1 开始
int len[]; // 预处理后中心为 i 的回文串的最大（在预处理前的字符串中的）长度

int n, n_; // 字符串长度、预处理后字符串长度
cin >> n >> &s[1];
n_ = n * 2 + 1;
for (int i = n; i > 0; i--) {
    s[i * 2] = s[i];
    s[i * 2 + 1] = '#';
}
s[0] = '@';
s[1] = '#';
s[n_ + 1] = '$';
for (int i = 1, mid = 0, r = 0; i <= n_; i++) {
    if (i <= r) {
        len[i] = min(len[mid * 2 - i], r - i);
    } else {
        len[i] = 0;
        mid = r = i;
    }
    if (i + len[i] == r) {
        mid = i;
        while (s[i + len[i] + 1] == s[i - len[i] - 1]) {
            len[i]++;
            r++;
        }
    }
}