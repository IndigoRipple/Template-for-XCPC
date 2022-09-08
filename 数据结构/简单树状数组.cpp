//单点修改+区间查询
inline int lowbit(int x) // 求二进制下最低位的1
{
    return x & -x;
}

inline void add(int x, int d) //单点修改  给第x号元素 + d
{
    while (x <= n) {
        aa[x] += d;
        x += lowbit(x);
    }
}

inline int ask(int x) // 求从第一个元素 到 第x个元素的总和
{
    int res = 0;
    while (x) {
        res += aa[x];
        x -= lowbit(x);
    }
    return res;
}
inline int getsum(int x, int y) // 求区间[l, r]内的元素总和
{
	return ask(r) - ask(l - 1);
}





//区间修改 + 区间查询
typedef long long ll;
ll sum1[N], sum2[N];

inline int lowbit(int x) // 求二进制下最低位的1
{
	return x & -x;
}

inline void add(ll x, ll d) // 对sum1数组和sum2数组进行维护
{
	for (int i = x; i <= n; i += lowbit(i)) {
		sum1[i] += d; sum2[i] += x * d;
	}
}
inline void range_add(ll l, ll r, ll d) // 差分思想进行区间维护
{
	add(l, d); add(r + 1, -d);
}

inline ll ask(ll x) // 求[1, x]内的所有元素之和
{
	ll res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		res += (x + 1) * sum1[i] - sum2[i];
	}
	return res;
}

inline ll range_ask(ll l, ll r) //求区间[l, r]内所有元素之和
{
	return ask(r) - ask(l - 1);
}
