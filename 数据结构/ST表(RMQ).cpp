//求最大值，初始化和查询取max
//求最小值，初始化和查询取min
//原数组下标从1开始使用
const int N = 5e4+7;
int dp[N][22];
int mm[N];
//初始化ST表
void initRMQ(int n,int g[]) { //n数组长度 g数组名称
	mm[0] = -1;
	for(int i = 1; i <= n; i++) {
		mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
		dp[i][0] = g[i];
	}
	for(int j = 1; j <= mm[n];j++)
		for(int i = 1; i + (1<<j) -1 <= n; i++)
			dp[i][j] = max(dp[i][j-1],dp[i+(1<<j-1)][j-1]);//最小值时此处取min
}
//查询ST表
int rmq(int x,int y) { //x左端点 y右端点
	int k = mm[y-x+1];
	return max(dp[x][k],dp[y-(1<<k)+1][k]);//最小值时此处取min
}
