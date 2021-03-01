const int N = 4e5+7;
int n,m;
long long a[N],sum[N],mx[N],tag[N];
//sum[x]表示x节点代表的区间和， mx[x]代表最大值，tag[x]是x节点的懒标记，代表区间加合 
//上传标记 
void pushup(int x){
    mx[x]=max(mx[x*2],mx[x*2+1]);
    sum[x]=sum[x*2]+sum[x*2+1];
}
//建树 
void build(int x,int l,int r){
    if(l==r){
        mx[x]=a[l];sum[x]=a[l];
        return;
    }
    int mid = (l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
//单点加 
void updata(int x,int l,int r,int pos,int k){//在a[pos]上加k. x是当前节点的编号 
    if(l==r){
        mx[x]+=k;sum[x]+=k;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid) updata(x*2,l,mid,pos,k);
    else updata(x*2+1,mid+1,r,pos,k);
    pushup(x);
}
//区间最大值 
int query(int x,int l,int r,int ll,int rr){//l r是当前区间 ll rr是查询区间 
    if(rr<l || ll>r) return 0;//不相交
    if(l>=ll && r<=rr) return mx[x];//当前区间被查询区间所包含
    //其他情况
    int mid=(l+r)/2;
    return max(query(x*2,l,mid,ll,rr),query(x*2+1,mid+1,r,ll,rr)); 
} 
//标记下传(lazytag懒标记)
void pushdown(int x,int l,int r){
    if(tag[x]){
        int mid=(l+r)/2,ls=x*2,rs=x*2+1;
        tag[ls]+=tag[x];
        mx[ls]+=tag[x];
        sum[ls]+=tag[x]*(mid-l+1);
        tag[rs]+=tag[x];
        mx[rs]+=tag[x];
        sum[rs]+=tag[x]*(r-(mid+1)+1);
        tag[x]=0;
    }
}
//区间加 
void updata_(int x, int l, int r, int ll, int rr,int k){
    if(ll>r || rr<l) return;
    if(l>=ll && r<=rr){
        tag[x]+=k;
        mx[x]+=k;
        sum[x]+=k*(r-l+1);
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)/2;
    updata_(x*2,l,mid,ll,rr,k);
    updata_(x*2+1,mid+1,r,ll,rr,k);
    pushup(x);
}
//区间和 
long long query_(int x,int l,int r,int ll,int rr){
    if(rr<l || ll>r) return 0;//不相交
    if(l>=ll && r<=rr) return sum[x];//当前区间被查询区间所包含
    pushdown(x,l,r);
    int mid=(l+r)/2;
    long long ans=query_(x*2,l,mid,ll,rr)+query_(x*2+1,mid+1,r,ll,rr);
    pushup(x);
    return ans;
}
