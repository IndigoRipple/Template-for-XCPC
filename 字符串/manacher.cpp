char s[]; // 下标从 1 开始
int len[]; // 中心为 i 的回文串的最长回文串的右边界到 i 的距离
           // 字符串有插入 # 的话就是中心为 i 的最长回文串的长度

int n, n_; // 字符串长度、预处理后字符串长度
cin >> n >> &s[1];
n_ = n * 2 + 1;
for (int i = n; i > 0; i--) { // 预处理开始
    s[i * 2] = s[i];
    s[i * 2 + 1] = '#';
}
s[0] = '@'; // @ 和 $ 是越界标记
s[1] = '#';
s[n_ + 1] = '$'; // 预处理结束
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