//平板电视参数介绍
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
// rb_tree_tag 和 splay_tree_tag 选择树的类型(红黑树和伸展树)
T // 自定义数据类型
null_type//无映射（老版本g++为null_mapped_type）
less<T>//Node的排序方式从小到大排序
tree_order_statistics_node_update//参数表示如何更新保存节点信息 tree_order_statistics_node_update会额外获得order_of_key()和find_by_order()两个功能。

ordered_set<Node> Tree;  // Node 自定义struct 注意重载less
Tree.insert(Node);       // 插入
Tree.erase(Node);        // 删除
Tree.order_of_key(Node); // 求Node的排名:当前数小的数的个数 +1
Tree.find_by_order(k);   // 返回排名为k+1的iterator 即有k个Node比*it小
Tree.join(b);            // 将b并入Tree，前提是两棵树类型一致并且二没有重复元素
Tree.split(v, b);        // 分裂，key小于等于v的元素属于Tree，其余属于b
Tree.lower_bound(Node);  // 返回第一个大于等于x的元素的迭代器
Tree.upper_bound(Node);  // 返回第一个大于x的元素的迭代器
//以上的所有操作的时间复杂度均为O(logn)
//注意，插入的元素会去重，如set
ordered_set<T>::point_iterator it=Tree.begin();  // 迭代器
//显然迭代器可以++，--运算


/*
1.插入 xx 数
2.删除 xx 数(若有多个相同的数，因只删除一个)
3.查询 xx 数的排名(排名定义为比当前数小的数的个数 +1+1 )
4.查询排名为 xx 的数
5.求 xx 的前驱(前驱定义为小于 xx，且最大的数)
6.求 xx 的后继(后继定义为大于 xx，且最小的数)
*/


//rb_tree_tag
#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll=long long;

template <class T=int> T rd()
{
    T res=0;T fg=1;
    char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') fg=-1;ch=getchar();}
    while( isdigit(ch)) res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
    return res*fg;
}
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int N=100010;
int n,m;
ll k,ans;
ordered_set<ll> T;
int main()
{
    n=rd();
    for(int i=1;i<=n;i++)
    {
        int op=rd();k=rd<ll>();
        if(op==1) T.insert((k<<20)+i);
        if(op==2) T.erase(T.lower_bound(k<<20));
        if(op==3) printf("%d\n",T.order_of_key((k<<20))+1);
        if(op == 4)ans=*T.find_by_order(k-1),printf("%lld\n",ans>>20);
        if(op == 5)ans=*--T.lower_bound(k<<20),printf("%lld\n",ans>>20);
        if(op == 6)ans=*T.upper_bound((k<<20)+n),printf("%lld\n",ans>>20);
    }
    return 0;
}



//splay_tree_tag
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <ext/pb_ds/assoc_container.hpp> 
using namespace std;
using namespace __gnu_pbds;
#define Node pair<int,int>
map <int,int> s;
tree< Node ,null_type,less< Node >,splay_tree_tag,tree_order_statistics_node_update> T;
int n,op,x;
int main()
{
    scanf("%d",&n);
    for(register int i = 1; i <= n; i++)
        switch(scanf("%d%d",&op,&x), op)
        {
            case 1 :T.insert(Node(x,s[x]++));
                    break;
            case 2 :T.erase(Node(x,--s[x]));
                    break;
            case 3 :printf("%d\n",(int)T.order_of_key(Node(x,0))+1);
                    break;
            case 4 :printf("%d\n",T.find_by_order(x-1)->first);
                    break;
            case 5 :printf("%d\n",T.find_by_order(
                    T.order_of_key(Node(x,0))-1
                                                      )->first);
                    break;
            case 6 :printf("%d\n",T.find_by_order(
                    T.order_of_key(Node(x,s[x]-1))+(T.find(Node(x,0)) == T.end() ? 0 : 1)
                                                      )->first);
                    break;
            default:break;
        }
    return 0;
}
/*
因为tree里不能有相同的数，但是实际会插入相同的数，所以把这些数左移20位在加上一个常数操作（ n < 2 20 n<2^{20} n<220，如果 a < b a<b a<b，那么一定有 { ( a < < 20 ) + n } < { b < < 20 } \{(a<<20) +n\}<\{b<<20\} {(a<<20)+n}<{b<<20}，这样就保证了在不影响相对大小关系的情况下，消除了相同的数。
*/
