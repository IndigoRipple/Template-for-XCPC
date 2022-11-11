//分块起手式
int bk=sqrt(n);//块大小
rep(i,1,n){
  bl[i]=(i-1)/bk+1;//块编号
}
rep(i,bl[1],bl[n]){
  l[i]=(i-1)*bk+1;//块左端点
  r[i]=min(i*bk,n);//块右端点
}
void sortbl(int x){//块内排序
  rep(i,l[x],r[x]) b[i]=a[i];
  sort(b+l[x],b+r[x]+1);
}
rep(i,bl[1],bl[n]){//遍历块内排序
  tag[i]=0;
  sortbl(i);
}


//区间加法 询问区间内小于某个值x的元素个数
//vector块
int v[50005],bl[50005],atag[50005];
vector<int>ve[505];
void reset(int x)
{
    ve[x].clear();
    for(int i=(x-1)*blo+1;i<=min(x*blo,n);i++)
        ve[x].push_back(v[i]);
    sort(ve[x].begin(),ve[x].end());
}
void add(int a,int b,int c)
{
    for(int i=a;i<=min(bl[a]*blo,b);i++)
        v[i]+=c;
    reset(bl[a]);
    if(bl[a]!=bl[b])
    {
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
            v[i]+=c;
        reset(bl[b]);
    }
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
        atag[i]+=c;
}
int query(int a,int b,int c)
{
    int ans=0;
    for(int i=a;i<=min(bl[a]*blo,b);i++)
        if(v[i]+atag[bl[a]]<c)ans++;
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
            if(v[i]+atag[bl[b]]<c)ans++;
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
    {
        int x=c-atag[i];
        ans+=lower_bound(ve[i].begin(),ve[i].end(),x)-ve[i].begin();
    }
    return ans;
}
int main()
{
    n=read();blo=sqrt(n);
    for(int i=1;i<=n;i++)v[i]=read();
    for(int i=1;i<=n;i++)
    {
        bl[i]=(i-1)/blo+1;
        ve[bl[i]].push_back(v[i]);
    }
    for(int i=1;i<=bl[n];i++)
        sort(ve[i].begin(),ve[i].end());
    for(int i=1;i<=n;i++)
    {
        int f=read(),a=read(),b=read(),c=read();
        if(f==0)add(a,b,c);
        if(f==1)printf("%d\n",query(a,b,c*c));
    }
    return 0;
}


//区间加法 询问区间内小于某个值x的前驱（比其小的最大元素）。
//set块
int n,blo;
int v[100005],bl[100005],atag[100005];
set<int>st[105];
void add(int a,int b,int c)
{
    for(int i=a;i<=min(bl[a]*blo,b);i++)
    {
        st[bl[a]].erase(v[i]);
        v[i]+=c;
        st[bl[a]].insert(v[i]);
    }
    if(bl[a]!=bl[b])
    {
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
        {
            st[bl[b]].erase(v[i]);
            v[i]+=c;
            st[bl[b]].insert(v[i]);
        }
    }
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
        atag[i]+=c;
}
int query(int a,int b,int c)
{
    int ans=-1;
    for(int i=a;i<=min(bl[a]*blo,b);i++)
    {
        int val=v[i]+atag[bl[a]];
        if(val<c)ans=max(val,ans);
    }
    if(bl[a]!=bl[b])        
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)        
        {
            int val=v[i]+atag[bl[b]];
            if(val<c)ans=max(val,ans);
        }
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
    {
        int x=c-atag[i];
        set<int>::iterator it=st[i].lower_bound(x);
        if(it==st[i].begin())continue;
        --it;
        ans=max(ans,*it+atag[i]);
    }
    return ans;
}
int main()
{
    n=read();blo=1000;
    for(int i=1;i<=n;i++)v[i]=read();
    for(int i=1;i<=n;i++)
    {
        bl[i]=(i-1)/blo+1;
        st[bl[i]].insert(v[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int f=read(),a=read(),b=read(),c=read();
        if(f==0)add(a,b,c);
        if(f==1)printf("%d\n",query(a,b,c));
    }
    return 0;
}


//区间开方 区间求和
/*思路：下取整开方，而一个数经过几次开方之后，它的值就会变成 0 或者 1。如果涉及了一些完整的块，这些块经过几次操作以后就会都变成 0 / 1，于是我们采取一种分块优化的暴力做法，只要每个整块暴力开方后，记录一下元素是否都变成了 0 / 1，区间修改时跳过那些全为 0 / 1 的块即可。*/
void solve_sqrt(int x)
{
    if(flag[x])return;
    flag[x]=1;
    sum[x]=0;
    for(int i=(x-1)*blo+1;i<=x*blo;i++)
    {
        v[i]=sqrt(v[i]),sum[x]+=v[i];
        if(v[i]>1)flag[x]=0;
    }
}
void add(int a,int b,int c)
{
    for(int i=a;i<=min(bl[a]*blo,b);i++)
    {
        sum[bl[a]]-=v[i];
        v[i]=sqrt(v[i]);
        sum[bl[a]]+=v[i];
    }
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
        {
            sum[bl[b]]-=v[i];
            v[i]=sqrt(v[i]);
            sum[bl[b]]+=v[i];
        }
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
        solve_sqrt(i);
}
int query(int a,int b)
{
    int ans=0;
    for(int i=a;i<=min(bl[a]*blo,b);i++)
        ans+=v[i];
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
            ans+=v[i];
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
        ans+=sum[i];
    return ans;
}


//区间众数
int n,blo,id;
int v[50005],bl[50005];
int f[505][505];
map<int,int>mp;
int val[50005],cnt[50005];
vector<int>ve[50005];
void pre(int x)
{   
    memset(cnt,0,sizeof(cnt));
    int mx=0,ans=0;
    for(int i=(x-1)*blo+1;i<=n;i++)
    {       
        cnt[v[i]]++;        
        int t=bl[i];
        if(cnt[v[i]]>mx||(cnt[v[i]]==mx&&val[v[i]]<val[ans]))
            ans=v[i],mx=cnt[v[i]];
        f[x][t]=ans;
    }
}
int query(int l,int r,int x)
{
    int t=upper_bound(ve[x].begin(),ve[x].end(),r)-lower_bound(ve[x].begin(),ve[x].end(),l);
    return t;
}
int query(int a,int b)
{
    int ans,mx;
    ans=f[bl[a]+1][bl[b]-1];
    mx=query(a,b,ans);
    for(int i=a;i<=min(bl[a]*blo,b);i++)
    {
        int t=query(a,b,v[i]);
        if(t>mx||(t==mx&&val[v[i]]<val[ans]))ans=v[i],mx=t;
    }
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
        {
            int t=query(a,b,v[i]);
            if(t>mx||(t==mx&&val[v[i]]<val[ans]))ans=v[i],mx=t;
        }
    return ans;
}
int main()
{
    n=read();
    blo=200;
    for(int i=1;i<=n;i++)
    {
        v[i]=read();
        if(!mp[v[i]])
        {
            mp[v[i]]=++id;
            val[id]=v[i];
        }
        v[i]=mp[v[i]];
        ve[v[i]].push_back(i);
    }
    for(int i=1;i<=n;i++)bl[i]=(i-1)/blo+1;
    for(int i=1;i<=bl[n];i++)pre(i);
    for(int i=1;i<=n;i++)
    {
        int a=read(),b=read();
        if(a>b)swap(a,b);
        printf("%d\n",val[query(a,b)]);
    }
    return 0;
}
