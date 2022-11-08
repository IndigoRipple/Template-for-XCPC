// 方法 1
const long long mod = 998244353, // 或 1000000007
    base = 29; // 或 233 / 19260817 / 19491001
int prehash[]; // 前缀的哈希值，下标从 1 开始
for (int i = 1; i <= n; ++i) prehash[i] = (prehash[i - 1] * base + s[i] - 'a' + 1) % mod;
inline int gethash(const int& l, const int& r) { // 闭区间，即 [l, r]
    int ret = (prehash[r] - prehash[l - 1] * power(base, r - l + 1)) % mod; // power() 可以预处理存数组
    return ret < 0 ? ret + mod : ret;
}

// 方法 2，不要用太多 substr()，会 T
size_t gethash(const string& s) {
    return hash<string>()(s);
    // 不调用函数直接写可以这样：
    // hash<string> hh; (这个写一遍就行)
    // size_t Hash = hh(s);
}