//01背包
for(int i = 1; i <= n; i++)
  for(int j = V; j >=c[i]; j--)
    f[j] = max(f[j], f[j - c[i]] + w[i]);
//完全背包（无限件）
for (int i = 1; i <= n; i++)
  for (int j = c[i]; j <= V; j++)
    f[j] = max(f[j], f[j - c[i]] + w[i]);
//多重背包（有限件）
for (int i = 1; i <= n; i++) {
    int num = min(p[i], V / c[i]); // V/c[i]是最多能放多少个进去，优化上界
    for (int k = 1; num > 0; k <<= 1) { 
        if (k > num) k = num;
        num -= k;
        for (int j = V; j >= c[i] * k; j--) // 01背包
            f[j] = max(f[j], f[j - c[i] * k] + w[i] * k);
    }
}
//混合背包
for (int i = 1; i <= n; i++) {
  cin >> c >> w >> p;
  if (p == 0) //完全背包
    for (int j = c; j <= V; j++)
      f[j] = max(f[j], f[j - c] + w);
  else if (p == -1) //01背包
    for (int j = V; j >= c; j--)
      f[j] = max(f[j], f[j - c] + w);
  else { //多重背包二进制优化
    int num = min(p, V / c);
    for (int k = 1; num > 0; k <<= 1) {
      if (k > num) k = num;
      num -= k;
      for (int j = V; j >= c * k; j--)
        f[j] = max(f[j], f[j - c * k] + w * k);
    }
  }
}
//二重费用背包
for (int i = 1; i <= n; i++)
  for (int j = V; j >= c[i]; j--)//费用1
    for (int k = M; k >= g[i]; k--)//费用2
      f[j][k] = max(f[j][k], f[j - c[i]][k - g[i]] + w[i]);
//分组背包（组内最多选一件）
for (int i = 1; i <= n; i++) {
  cin >> s; // 第i组的物品数量
  for (int j = 1; j <= s; j++) cin >> c[j] >> w[j]; //组中每个物品的属性
    for (int j = V; j >= 0; j--)
      for (int k = 1; k <= s; k++)
        if (j >= c[k])
        f[j] = max(f[j], f[j - c[k]] + w[k]);
        // 由于每组物品只能选一个，所以可以覆盖之前组内物品最优解的来取最大值
}
//01背包第k优解
int kth(int n, int V, int k) {
    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= w[i]; j--) {
            for (int l = 1; l <= k; l++) {
                a[l] = f[j][l];
                b[l] = f[j - w[i]][l] + v[i];
            }
            a[k + 1] = -1;
            b[k + 1] = -1;
            int x = 1, y = 1, o = 1;
            while (o != k + 1 and (a[x] != -1 or b[y] != -1)) {
                if (a[x] > b[y]) f[j][o] = a[x], x++;
                else f[j][o] = b[y], y++;
                if (f[j][o] != f[j][o - 1]) o++;
            }
        }
    }
    return f[V][k];
}



