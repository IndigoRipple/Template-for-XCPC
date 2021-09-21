#include<bits/stdc++.h>
#include<set>
using namespace std;
int n,m;
struct node{
	int l,r;
	mutable int v;
	node(int ll,int rr=-1,int val=0):l(ll),r(rr),v(val) {} 
	bool operator < (const node &orz)const{
		return l<orz.l;
	} 
}; 
set<node> s;
auto split(int pos){
	auto it=s.lower_bound(node(pos));
	if(it!=s.end() && it->l==pos) return it;
	--it;
	int l=it->l,r=it->r,v=it->v;
	s.erase(it);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;
}
void assign(int l,int r,int val){
    auto itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,val));
} 
/*
int qsum(int ll,int rr){
    int res=0;
    auto itr=split(rr+1),itl=split(ll);
    for(;itl!=itr;++itl) res+=(itl->r-itl->l+1)*itl->v;
    return res;
}
void rev(int ll,int rr)
{
    auto itr=split(rr+1),itl=split(ll);
    for(;itl!=itr; ++itl)
        (itl->v) ^= 1;
} 
int  cnt(int ll,int rr){
	auto itr=split(rr+1),itl=split(ll);
	int t=0,ans=0;
    for(;itl!=itr; ++itl){
    	if(itl->v==false){
			ans=max(ans,t);	
			t=0;
		}
		else {
			t+=(itl->r-itl->l+1);
		}
	}
	return max(ans,t);
} 
*/
int main(){
	cin>>n>>m;
	int v;
	for(int i=0;i<n;i++){
		scanf("%d",&v);
		s.insert(node(i,i,v));
	}
	s.insert(node(n,n,0));
	while(m--){
		int opt,a,b;
		scanf("%d %d %d",&opt,&a,&b);
		/*
		if(opt==0){
			assign(a,b,0);
		}
		else if(opt==1){
			assign(a,b,1);
		}
		else if(opt==2){
			rev(a,b);
		} 
		else if(opt==3){
			cout<<qsum(a,b);
			if(m!=1)cout<<endl; 
		}
		else if(opt==4){
			cout<<cnt(a,b);
			if(m!=1)cout<<endl;
		}
		*/
	}
	
	return 0;
}
