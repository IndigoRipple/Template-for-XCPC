// 下标从 1 开始
char s1[], s2[]; // s1 待匹配串，s2 模式串
int nxt[]; // 对于 s2 的前缀，其最长且相等的前后缀的长度（不包括本身）
vector<int> ans; // 匹配成功的位置
int n1 = s1.size(), n2 = s2.size();

for (int i = 2, k = 0; i <= n2; i++) { // 计算 nxt[]
    while (k && s2[k + 1] != s2[i]) k = nxt[k];
    if (s2[k + 1] == s2[i]) k++;
    nxt[i] = k;
}
for (int i = 1, imx = n1 - n2 + 1; i <= imx; i++) // 匹配
    for (int j = 1; ; j++)
        if (j > n2) {
            ans.push_back(i);
            break;
        } else if (s1[i + j - 1] != s2[j]) {
            if (j > 1 && nxt[j - 1]) {
                i += j - 1 - nxt[j - 1];
                j = nxt[j - 1] + 1;
                if (i > imx) break;
            } else break;
        }