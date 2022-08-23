int a[], // 待处理数组
    f[], // a[i] 结尾的最长 LIS 的长度
    g[]; // 长度为 i 的 LIS 中，最后一个数最小的数

fill(g + 1, g + (n + 1), inf); // g[1...n] = inf
for (int i = 1; i <= n; ++i) {
    // LIS 相邻元素可以相等的话改成 upper_bound()
    int k = lower_bound(g + 1, g + (n + 1), a[i]) - g;
    f[i] = k;
    g[k] = a[i];
}