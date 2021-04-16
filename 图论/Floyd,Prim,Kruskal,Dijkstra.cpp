#include<iostream>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;
#define maxn 25000//最大结点数
#define maxm 50000//最大边数
//链式前向星
int head[maxn],k=1;//0说明没有下一个值
struct edge{
	int u,v,w;//起点为u，终点为v,权值为c
	int next;//下一个值位置
}edg[maxm]={};
void add(int u,int v,int w){
	edg[++k].v=v;
	edg[k].w=w;
	edg[k].next=head[u];
	head[u]=k;
}
//Floyd 邻接矩阵
int edge[maxn][maxn];
int dis[maxn][maxn];
void Floyd(int n){
	memcpy(dis,edge,sizeof(edge));
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
}

//Prim 最小生成树 堆优化

typedef pair<int,int>pii;
priority_queue<pii,vector<pii>,greater<pii>>q;
int Dis[maxn],Vis[maxn];
int n,cnt,sum=0;//n为图中结点数
void Prim(){
	Dis[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()&&cnt<n){
		int d=q.top().first,u=q.top().second;
		q.pop();
		if(Vis[u])continue;
		cnt++;
		sum+=d;
		Vis[u]=1;
		for(int i=head[u];i!=-1;i=edg[i].next)
			if(edg[i].w<Dis[edg[i].v]){
				Dis[edg[i].v]=edg[i].w;
				q.push(make_pair(Dis[edg[i].v],edg[i].v));
			}
	}
}
void Prim_slove(){
	int Q;int ax,bx,cx;
	memset(Dis,127,sizeof(Dis));
	memset(head,-1,sizeof(head));
	cin>>n>>Q;
	int cnt=0;
	for(int i=1;i<=Q;i++){
		cin>>ax>>bx>>cx;
		add(ax,bx,cx);
		add(bx,ax,cx);
	}
	Prim();
	if(cnt==n)cout<<sum;
	else cout<<"orz";
	return ;
}

//Kruskal 路径压缩并查集
int n,m,sum=0,k=0;
int fat[maxn]={};
struct kr_edge{
	int u,v,w;
}kr_edg[maxm];
bool kr_cmp(kr_edge a,kr_edge b){
	return a.w<b.w;
}
int father(int x){
	while(x!=fat[x]){
		fat[x]=fat[fat[x]];
		x=fat[x];
	}
	return x;

}
void unionn(int x,int y){
	fat[father(y)]=father(x);
}
void Kruskal(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>kr_edg[i].u>>kr_edg[i].v>>kr_edg[i].w;
	}
	sort(kr_edg+1,kr_edg+1+m,kr_cmp);
	for(int i=1;i<=m;i++){
		if(k==n-1)break;
		if(father(kr_edg[i].u)!=father(kr_edg[i].v)){
		sum+=kr_edg[i].w;
		k++;
		}
	}
	cout<<sum;
	return;
}

//Dijkstra 堆优化
struct node{
	int dis,pos;
}nod;
int n,m,cnt,s;//s代表起点
int d[maxn]={};
void Dijkstra(){
	priority_queue<node>q;
	for(int i=1;i<=n;i++)d[i]=1e9;
	d[s]=0;node temp={0,s};
	q.push(temp);
	while(!q.empty()){
		int k=q.top().pos;
		int dk=q.top().dis;
		q.pop();
		if(dk!=d[k])continue;
		for(int e=head[k];e;e=edg[e].next){
			if(d[edg[e].v]>d[k]+edg[e].w){
				d[edg[e].v]=d[k]+edg[e].w;
				node now={d[edg[e].v],edg[e].v};
				q.push(now);
			}
		}
	}
	//可由此输出路径
	for(int i=1;i<=n;i++)cout<<d[i]<<' ';
	return;
}
