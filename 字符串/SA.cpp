char s[N]; // 下标从 1 开始
int sa[N], // sa[i] 表示排名第 i 的后缀是从第几个字符开始
    oldsa[N], // 上一次排序后的 sa 数组
    rnk[N], // 第 i 个字符开始的后缀的当前排名
    oldrnk[N * 2], // 计算新一次倍增后 rnk 数组时的临时数组
    cnt[N], // 基数排序用的 cnt 数组
    rnk_oldsa[N]; // rnk_oldsa[i] = rnk[oldsa[i]]

bool cmp(int x, int y, int z) {
  return oldrnk[x] == oldrnk[y] && oldrnk[x + z] == oldrnk[y + z];
}

cin >> &s[1];
int n = strlen(s + 1), m = 255, p, w, i;
for (i = 1; i <= n; i++) cnt[rnk[i] = s[i]]++;
for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
for (i = n; i >= 1; i--) sa[cnt[rnk[i]]--] = i;
for (w = 1; ; w <<= 1, m = p) {
  for (p = 0, i = n; i > n - w; i--) oldsa[++p] = i;
  for (i = 1; i <= n; i++) {
    if (sa[i] > w) {
      oldsa[++p] = sa[i] - w;
    }
  }
  fill(cnt + 1, cnt + (m + 1), 0); // cnt[1...m] = 0
  for (i = 1; i <= n; i++) cnt[rnk_oldsa[i] = rnk[oldsa[i]]]++;
  for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; i--) sa[cnt[rnk_oldsa[i]]--] = oldsa[i];
  // 把 rnk[1...n] 弄到 oldrnk[1...n]
  move(rnk + 1, rnk + (n + 1), oldrnk + 1);
  for (p = 0, i = 1; i <= n; i++) {
    rnk[sa[i]] = cmp(sa[i - 1], sa[i], w) ? p : ++p;
    if (p == n) {
      for (int j = 1; j <= n; j++) sa[rnk[j]] = j;
      break;
    }
  }
}