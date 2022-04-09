#include <iostream>
#include<algorithm>
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<queue>
#define rep(i , x , n)  for(int i = x ; i <= (n) ; i ++)
#define per(i , n , x)  for(int i = n ; i >= (x) ; i --)
#define ll long long
#define ft first
#define sd second
using namespace std;
const int maxn = 2e5 + 5;
int n;
struct point
{
    ll x, y;
    bool operator < (const point& s) const
    {
        if (x != s.x)  return x < s.x;
        else  return y < s.y;
    }
} p[maxn];

ll multi(point p0, point p1, point p2)
{
    ll x1, y1, x2, y2;
    x1 = p1.x - p0.x, y1 = p1.y - p0.y;
    x2 = p2.x - p0.x, y2 = p2.y - p0.y;
    return x1 * y2 - x2 * y1;
}

ll area(point p0, point p1, point p2)
{
    point o = { 0,0 };
    ll sum = 0;
    sum = multi(o, p0, p1)+multi(o, p1, p2)+multi(o, p2, p0);
    return abs(sum);
}
struct Convex_hull
    //前置条件 定义n（点的数量） p【】（点数组）
    //sta按顺序存储凸包端点的下标
{
    int cnt, sta[maxn];
    void init()
    {
        cnt = 0;
    }
    void solve()  //注意左下角的点存储了两次 分别是数组中的第一个点和最后一个点 
    {
        sort(p + 1, p + n + 1);
        sta[++cnt] = 1;
        rep(i, 2, n)
        {
            //假如想让凸包的边上有多个点，那就把 <= 改成 < 
            while (cnt >= 2 && multi(p[sta[cnt - 1]], p[sta[cnt]], p[i]) <= 0)
                cnt--;
            sta[++cnt] = i;
        }
        int temp = cnt;
        per(i, n - 1, 1)
        {
            while (cnt > temp && multi(p[sta[cnt - 1]], p[sta[cnt]], p[i]) <= 0)
                cnt--;
            sta[++cnt] = i;
        }
        rep(i, 1, cnt - 1)  sta[i + (cnt - 1)] = sta[i];
    }
   
} convex_hull;
