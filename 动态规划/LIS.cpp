// 这是下标从 0 开始的版本，可以改成下标从 1 开始

// a 是原数组，f[i] 表示 a[i] 结尾的最长 LIS 的长度，g[i] 表示长度为 i 的 LIS 中，最后一个数最小的数
int a[], f[], g[];

fill(g + 1, g + (n + 1), inf);
for (int i = 0; i < n; ++i) { // 改成下标从 1 开始的话只改这一行
    int k = lower_bound(g + 1, g + (n + 1), a[i]) - g; // LIS 相邻元素可以相等的话改成 upper_bound
    f[i] = k;
    g[k] = f[i];
}