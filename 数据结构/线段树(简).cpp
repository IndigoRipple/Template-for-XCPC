const int N = 4e5+7;
int n,m;
long long a[N*4],sum[N*4],mx[N*4],tag[N*4];
//sum[x]表示x节点代表的区间和， mx[x]代表最大值，tag[x]是x节点的懒标记，代表区间加合
//上传标记
void pushup(int x){
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
    sum[x]=sum[x<<1]+sum[x<<1|1];
}
//建树
void build(int l,int r, int x=1){
    if(l==r){
        mx[x]=a[l];sum[x]=a[l];
        return;
    }
    int mid = l+r>>1;
    build(l,mid,x<<1);
    build(mid+1,r,x<<1|1);
    pushup(x);
}
//单点加
void updata(int l,int r,int pos,int k,int x=1){//在a[pos]上加k. x是当前节点的编号
    if(l==r){
        mx[x]+=k;sum[x]+=k;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid) updata(l,mid,pos,k,x<<1);
    else updata(mid+1,r,pos,k,x<<1|1);
    pushup(x);
}
//区间最大值
int query(int l,int r,int ll,int rr,int x=1){//l r是当前区间 ll rr是查询区间
    if(rr<l || ll>r) return 0;//不相交
    if(l>=ll && r<=rr) return mx[x];//当前区间被查询区间所包含
    //其他情况
    int mid=(l+r)/2;
    return max(query(l,mid,ll,rr,x<<1),query(mid+1,r,ll,rr,x<<1|1));
}
//标记下传(lazytag懒标记)
void pushdown(int l,int r,int x){
    if(tag[x]){
        int mid=(l+r)/2,ls=x*2,rs=x*2+1;
        tag[ls]+=tag[x];
        mx[ls]+=tag[x];
        sum[ls]+=tag[x]*(mid-l+1);
        tag[rs]+=tag[x];
        mx[rs]+=tag[x];
        sum[rs]+=tag[x]*(r-mid);
        tag[x]=0;
    }
}
//区间加
void updata_(int l, int r, int ll, int rr,int k,int x=1){
    if(ll>r || rr<l) return;
    if(l>=ll && r<=rr){
        tag[x]+=k;
        mx[x]+=k;
        sum[x]+=k*(r-l+1);
        return;
    }
    pushdown(l,r,x);
    int mid=l+r>>1;
    updata_(l,mid,ll,rr,k,x<<1);
    updata_(mid+1,r,ll,rr,k,x<<1|1);
    pushup(x);
}
//区间和
long long query_(int l,int r,int ll,int rr,int x=1){
    if(rr<l || ll>r) return 0;//不相交
    if(l>=ll && r<=rr) return sum[x];//当前区间被查询区间所包含
    pushdown(l,r,x);
    int mid=(l+r)/2;
    long long ans=query_(l,mid,ll,rr,x<<1)+query_(mid+1,r,ll,rr,x<<1|1);
    pushup(x);
    return ans;
}
