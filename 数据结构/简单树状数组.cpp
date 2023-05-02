//单点修改+区间查询
#define lowbit(x) (x&(-x))
void updata(int x,int k){//单点修改
	for(;x<=n;x+=lowbit(x))
		t[x]+=k;
}
int query(int x){//[1,x]区间和
	int ans=0;
	for(;x;x-=lowbit(x))
		ans=ans+tree[x];
	return ans;
}
int getsum(int x, int y){//求区间[l, r]内的元素总和
	return ask(y)-ask(x - 1);
}


//区间修改 + 区间查询
#define int long long
#define lowbit(x) (x&(-x))
int sum1[N], sum2[N];
void add(int x, int d){ //对sum1数组和sum2数组进行维护
	for (int i = x; i <= n; i += lowbit(i)) {
		sum1[i] += d; sum2[i] += x * d;
	}
}
void range_add(int l, int r, int d){ //差分思想进行区间加
	add(l, d); add(r + 1, -d);
}
int ask(int x){ //求[1, x]内的所有元素之和
	int res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		res += (x + 1) * sum1[i] - sum2[i];
	}
	return res;
}
int range_ask(ll l, ll r){//求区间[l, r]内所有元素之和
	return ask(r) - ask(l - 1);
}
