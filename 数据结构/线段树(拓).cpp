//维护区间加法 乘法 赋值 最值
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int inf = 1e16;
const int N = 1e5 + 7;
int n,m;
int a[N*4],sum[N*4],max_[N*4];
struct LazyTag{
    int add,mul,col;//三种懒标记
}tag[N*4];

void pushup(int x) { //上传标记
    sum[x] = sum[x<<1] + sum[x<<1|1];
    max_[x] = max(max_[x<<1],max_[x<<1|1]);
}
void build(int x,int l,int r) {//建树
    if(l == r){
        sum[x] = a[l];
        max_[x] = max(max_[x<<1],max_[x<<1|1]);
        return;
    }
    int mid = (l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void pushdown(int x,int l,int r) {//下放标记
    int ls = x<<1,rs = x<<1|1,mid = (l+r)>>1;
    if(tag[x].col != -1){//有赋值标记
        int c = tag[x].col;
        tag[ls].add = tag[rs].add = 0;
        tag[ls].mul = tag[rs].mul = 1;
        sum[ls] = c * (mid - l + 1);
        sum[rs] = c * (r - mid );
        tag[ls].col = tag[rs].col = c;
        max_[ls] = max_[rs] = c;
        tag[x].col = -1;
    }
    if(tag[x].mul != 1){ //有乘法标记
        int c = tag[x].mul;
        tag[ls].mul *= c;
        tag[rs].mul *= c;
        sum[ls] *= c;
        sum[rs] *= c;
        max_[ls] *= c;
        max_[rs] *= c;
        tag[ls].add *= c;
        tag[rs].add *= c;
        tag[x].mul = 1;
    }
    if(tag[x].add > 0){ //有加法标记
        int c = tag[x].add;
        tag[ls].add += c;
        tag[rs].add += c;
        sum[ls] += c * (mid - l + 1);
        sum[rs] += c * (r - mid);
        max_[ls] += c;
        max_[rs] += c;
        tag[x].add = 0;
    }
    return;
}
void updata_col(int x,int l,int r,int ll,int rr,int k) { //将[ll,rr]赋值为k
    if(r < ll || l > rr) return;
    if(l >= ll && r <= rr){
        sum[x] = k * (r - l + 1);
        max_[x] = k;
        tag[x].mul = 1;
        tag[x].add = 0;
        tag[x].col = k;
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    updata_col(x<<1,l,mid,ll,rr,k);
    updata_col(x<<1|1,mid+1,r,ll,rr,k);
    pushup(x);
}

void updata_mul(int x,int l,int r,int ll,int rr,int k) { //将[ll,rr]乘以k
    if(r < ll || l > rr) return;
    if(l >= ll && r <= rr){
        sum[x] = sum[x] * k;
        max_[x] = max_[x] * k;
        tag[x].mul = tag[x].mul * k;
        tag[x].add = tag[x].add * k;
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    updata_mul(x<<1,l,mid,ll,rr,k);
    updata_mul(x<<1|1,mid+1,r,ll,rr,k);
    pushup(x);
}
void updata_add(int x,int l,int r,int ll,int rr,int k) { //将[ll,rr]加上k
    if(r < ll || l > rr) return;
    if(l >= ll && r <= rr){
        sum[x] = sum[x] + k * (r - l + 1);
        max_[x] = max_[x] + k;
        tag[x].add = tag[x].add + k;
        return;
    }
    pushdown(x,l,r);
    int mid = (l+r)>>1;
    updata_add(x<<1,l,mid,ll,rr,k);
    updata_add(x<<1|1,mid+1,r,ll,rr,k);
    pushup(x);
}
int query(int x,int l,int r,int ll,int rr) {//查询区间和
    if(r < ll || l > rr) return 0;
    if(l >= ll && r <= rr){
        return sum[x];
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    return query(x<<1,l,mid,ll,rr)+query(x<<1|1,mid+1,r,ll,rr);
}

int query_mx(int x,int l,int r,int ll,int rr) {//查询区间最值
    if(r < ll || l > rr) return -inf;
    if(l >= ll && r <= rr){
        return max_[x];
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    return max(query_mx(x<<1,l,mid,ll,rr),query_mx(x<<1|1,mid+1,r,ll,rr));
}

void init() { //初始化
    cin>>n>>m;
    for(int i = 1;i <= 4 * n;i++) tag[i].mul = 1;
    for(int i = 1;i <= 4 * n;i++) tag[i].col = -1;
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    build(1,1,n);
}
