#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+7;
int n,bk;
int a[N],bl[N],sum[N];
int tag[N];//加法块标记

void add(int l,int r,int x) { //[l,r] 加上x
	int sb = bl[l],tb = bl[r];
	if(sb == tb){
		for(int i = l; i <= r; i++) a[i] += x , sum[sb] += x;
		return;
	}
	for(int i = l; bl[i] == sb; i++) a[i] += x , sum[sb] += x;
	for(int i = sb+1; i <= tb-1; i++) tag[i] += x , sum[i] += bk * x;
	for(int i = r; bl[i] == tb; i--) a[i] += x , sum[tb] += x;
}

long long query(int l,int r){ //查询[l,r]的区间和
	int sb = bl[l],tb = bl[r];
	long long ans = 0;
	if(sb == tb){
		for(int i = l; i <= r; i++) ans += a[i] + tag[sb];
		return ans ;
	}
	for(int i = l; bl[i] == sb; i++) ans += a[i] + tag[sb];
	for(int i = sb+1; i <= tb-1; i++) ans += sum[i];
	for(int i = r; bl[i] == tb; i--) ans += a[i] + tag[tb];
	return ans;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	bk=sqrt(n);//块的大小
	for(int i=1;i<=n;i++){
		cin>>a[i];
		bl[i]=(i-1)/bk+1;
	}
	int opt,l,r,c;
	for(int i=1;i<=n;i++){
		cin>>opt>>l>>r>>c;
		if(opt==0){
			add(l,r,c);
		}
		else{
			cout<<query(r,r)<<"\n";
		}
	}
	return 0;
}
