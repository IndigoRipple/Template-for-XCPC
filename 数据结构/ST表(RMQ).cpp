//求最大值，初始化和查询取max
//求最小值，初始化和查询取min
//原数组下标从1开始使用
const int N = 1e5+7;
int st[N][32];
int Log2[N];
//初始化ST表
void initRMQ(int n,int g[]) { //n数组长度 g数组名称
	Log2[1]=0;
	for(int i=2; i <= n; i++) {
		Log2[i]=Log2[i-1];
		if((1 << Log2[i] + 1) == i) {
			++Log2[i];
		}
	}
	for(int i = 1; i <= n; i++)	st[i][0]=g[i];
	for(int j = 1; j <= 21; j++) 
		for(int i = 1; (i + (1 << j) - 1) <= n; i++)
			st[i][j] = max (st[i][j-1], st[i + (1 << (j-1) )][j-1]); //最小值max修改为min
}
//查询ST表
int query_min(int l,int r) { //l左端点 r右端点
	int len = r - l + 1, k = Log2[len];
	return max(st[l][k],st[r - (1<<k) + 1][k]); //最小值max修改为min
}
