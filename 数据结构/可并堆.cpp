#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int>q;//因为放置和std重复，故需要带上命名空间
__gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> q;//配对堆
__gnu_pbds::priority_queue<int,greater<int>,binary_heap_tag> q;//二叉堆
__gnu_pbds::priority_queue<int,greater<int>,binomial_heap_tag> q;//二项堆
__gnu_pbds::priority_queue<int,greater<int>,rc_binomial_heap_tag> q;//左偏树
__gnu_pbds::priority_queue<int,greater<int>,thin_heap_tag> q;//斐波那契堆
__gnu_pbds::priority_queue<int,greater<int> > q;
/*
        配对堆 二叉堆 二项堆 左偏树 斐波那契堆
push      1     log     1     1       1
pop      log    log    log   log     log
modify	 log     n     log   log      1
erase    log     n     log   log     log
join      1      n     log   log      n
*/
/*
push(): 向堆中压入一个元素，返回该元素位置的迭代器。
pop(): 将堆顶元素弹出。
top(): 返回堆顶元素。
size() 返回元素个数。
empty() 返回是否非空。
modify(point_iterator, const key): 把迭代器位置的 key 修改为传入的 key，并对底层储存结构进行排序。
erase(point_iterator): 把迭代器位置的键值从堆中擦除。
join(__gnu_pbds :: priority_queue &other): 把 other 合并到 *this 并把 other 清空。
*/


/*
luogu P3377
    一开始有 nn 个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：
    1 x y：将第 xx 个数和第 yy 个数所在的小根堆合并（若第 xx 或第 yy 个数已经被删除或第 xx 和第 yy 个数在用一个堆内，则无视此操作）。
    2 x：输出第 xx 个数所在的堆最小数，并将这个最小数删除（若有多个最小数，优先删除先输入的；若第 xx 个数已经被删除，则输出 −1−1 并无视删除操作）。
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>//引用pbds的库的堆
#pragma GCC optimize(3)
using namespace std;
inline char nc(){
  	static char buf[100000],*p1=buf,*p2=buf;
  	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template <typename _Tp>
inline void read(_Tp &x){
    int f=1;x=0;char ch=nc();
  	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=nc();}
  	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=nc();}
  	x*=f;
}
inline void write(long long n){
    if(n==0) return;
    write(n/10);
    putchar(n%10+'0');
}
struct ${
    int s,id;
    inline bool operator < (const $ &p)const{if (s!=p.s)return s>p.s;else return id>p.id;}//注意！由于使用了pbds，只能重载运算符。而且pbds中的堆很毒瘤，它把<重载成>，然后排>，所以重载的时候要注意反着重载
};//结构体，存每个数的数值和id
inline $ g(int a,int b){$ p;p.s=a,p.id=b;return p;}//将2个int转成一个$
__gnu_pbds::priority_queue<$> q[100005];//定义一个pbds的堆
//使用__gnu_pbds::来引用pbds内的内容
int n,m,f[100005],x;
bool s[100005];//如果s[i]==1则i被删除
int find(int n){return f[n]==n?n:f[n]=find(f[n]);}//维护并查集，这里实际上可以路径压缩
int main(){
    read(n),read(m);
    for (int i=1;i<=n;i++)read(x),q[i].push(g(x,i)),f[i]=i;//读入的同时对每个i建一个堆，同时初始化并查集
    while (m--){
        read(x);
        if (x==1){
            int a,b;
            read(a),read(b);
            int fa=find(a),fb=find(b);
            if (fa==fb||s[a]||s[b])continue;//坑点1：注意不要把s[a]||s[b]写成了s[fa]||s[fb]
            if (q[fa].size()>q[fb].size())f[fb]=fa,q[fa].join(q[fb]);//按堆的大小合并
            else f[fa]=fb,q[fb].join(q[fa]);
        }else{
            int a;
            read(a);
            if (s[a]){puts("-1");continue;}
            int fa=find(a);
            write((q[fa].top()).s),puts(""),s[(q[fa].top()).id]=1,q[fa].pop();//同普通堆
        }
    }
}
