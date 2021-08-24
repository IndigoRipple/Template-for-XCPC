// ConsoleApplication16.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
#define zero(x) (((x)>0?(x):-(x))<eps) 
#define eps 1e-8  
#define INF 1e6;
//规定:
//1.打&&代表为类内成员函数
//2.不要试图代入奇怪的数据



//0------基础函数                                    |  
//0.1------向量运算                                  |
//  0.1.1--向量加减,伸缩&&                           |
//  0.1.2--向量叉乘&&                                |
//  0.1.3--向量点乘&&                                |
//  0.1.4--两点距离&&                                |
//  0.1.5--向量叉积                                  | 需要模板0.1.1/0.1.2
//  0.1.6--向量点积                                  | 需要模板0.1.1/0.1.3
//0.2------计算前置模板                              |
//  0.2.1--判断两点是否共线（三点版本）              |
//  0.2.2--两直线交点（四点版本）                    |

//1------平面直线与点                                |
//1.0------直线类                                    | 此章剩下部分需包涵0.1/1.0
//1.1------直线与点的关系                            |
//  1.1.1--判断是否平行&&                            |
//  1.1.2--判断是否共线（直线版本）&&                |
//  1.1.3--判断是否在线段上（包括端点）&&            |
//  1.1.4--判断是否垂直&&                            |
//1.2------直线与点的数值计算                        |
//  1.2.1--两直线交点（两直线版本）&&                |
//  1.2.2--矢量的模                                  |
//  1.2.3--点到直线最短距离                          |
//  1.2.4--点到直线最近点                            |
//  1.2.5--点到线段最近点                            |
//  1.2.6--求两直线夹角                              |
//1.3------三角形                                    |
//  1.3.1--外心                                      | 需要模板1.2.1
//  1.3.2--内心                                      | 需要模板1.2.1
//  1.3.3--重心                                      | 需要模板1.2.1
//  1.3.4--垂心                                      | 需要模板1.2.1
//  1.3.5--费马点                                    | 需要模板0.1.4

//2------多边形                                      |
//2.1------多边形基础判断与计算                      |
//  2.1.1--点是否在多边形内部                        | 需要模板0.2.1
//2.2------凸包问题                                  |
//  2.2.1--求凸包(返回点的数量）                     | 需要模板0.1.1/0.1.2/0.1.4/0.1.5
//  2.2.2--求凸包面积                                | 需要模板0.1.1/0.1.2/0.1.5
//  2.2.3--求凸包周长                                | 需要模板0.1.4
//  2.2.4--求凸包重心                                | 需要模板0.1.1/0.1.2/0.1.5
//  2.2.5--求面积最大三角形                          | 需要模板0.1.1/0.1.2/0.1.5
//  2.2.6--求面积最小环绕矩形                        | 需要模板0.1.1/0.1.2/0.1.3/0.1.4/0.1.5
//  2.2.7--求周长最小环绕矩形                        | 需要模板0.1.1/0.1.2/0.1.3/0.1.4/0.1.5
//2.3-------旋转卡壳                                 |
//  2.3.1--求凸包直径-最大点对距离                   | 需要模板0.1.1/0.1.2/0.1.4/0.1.5

//3------圆                                          |
//3.1------圆的基础基础判断                          |
//  3.1.1--三点求圆心                                |
//  3.1.2--判断与直线相交相切                        | 需要模板0.1.1/0.1.2/0.1.4/0.1.5/1.2.3
//  3.1.3--判断与线段相交相切                        | 需要模板0.1.1/0.1.2/0.1.4/0.1.5/1.2.3
//  3.1.4--判断与圆相交相切                          | 需要模板0.1.4
//3.2------圆的计算                                  |
//  3.2.1--计算圆上到点的最近点                      | 需要模板0.1.4
//  3.2.2--计算线段与圆的交点                        | 需要模板0.1.4/0.2.2
//  3.2.3--计算圆与圆的交点                          | 需要模板0.1.4/0.2.2/3.2.2
//  3.2.4--计算两圆相交部分面积                      |
//  3.2.5--将向量旋转一定角度                        |
//  3.2.6--计算圆外一点做直线与圆的切点              | 需要模板3.2.5
//3.3------最小圆覆盖                                |
//  3.3.1--最小圆覆盖基础模板                        | 需要模板0.1.4/3.1.1

//4------构造                                        |
//4.1------网格                                      |
//  4.1.1--多边形上的格点数                          |
//  4.1.2--多边形内的格点数                          |

//5------三维几何                                    |
//5.0------三维点类                                  | 此章剩下部分默认需包涵5.0和5.1的全部模板
//5.1------三维基础函数                              |
//  5.1.1--向量长度                                  |
//  5.1.2--线段长度                                  |
//  5.1.3--叉积                                      |
//  5.1.4--点积                                      |
//  5.1.5--矢差                                      |
//5.2------共面共线关系                              |
//  5.2.1--平面法向量                                | 
//  5.2.2--判断三点共线                              | 
//  5.2.3--判断四点共面                              | 需要模板5.2.1
//  5.2.4--判断点是否在线段上                        |
//   5.2.4.1-包括端点和共线                          | 
//   5.2.4.2-不包括端点                              | 需要模板5.2.4.1
//  5.2.5--判断点是否在空间三角形上                  |
//   5.2.5.1-包括边界                                |
//   5.2.5.2-不包括边界                              | 需要模板5.2.5.1
//5.3------拓扑关系                                  |
//  5.3.1--两点在线段同侧                            |
//  5.3.2--两点在线段异侧                            |
//  5.3.3--两点在平面同侧                            |
//  5.3.4--两点在平面异侧                            |
//5.4------平行垂直相交关系                          | 
//  5.4.1--两线平行                                  |
//  5.4.2--两面平行                                  | 需要模板5.2.1
//  5.4.3--线面平行                                  | 需要模板5.2.1
//  5.4.4--两线垂直                                  |
//  5.4.5--两面垂直                                  | 需要模板5.2.1
//  5.4.6--线面垂直                                  | 需要模板5.2.1
//5.5------空间线段                                  |
//  5.5.1--判断两线段相交                            |
//   5.5.1.1-包括端点和共线                          | 需要模板5.2.1/5.2.2/5.2.3/5.3.1/5.2.4.1
//   5.5.1.2-不包括端点                              | 需要模板5.2.2/5.3.2
//  5.5.2--判断线段与空间三角形相交                  |
//   5.5.5.1-包括边界和部分包含                      | 需要模板5.3.1
//   5.5.5.2-不包括边界和部分包含                    | 需要模板5.3.2
//5.6------空间几何计算                              |
//  5.6.1--计算两直线交点                            |
//  5.6.2--计算直线与平面交点                        | 需要模板5.2.1
//  5.6.3--计算两面交线                              | 需要模板5.4.3/5.6.1
//  5.6.4--计算点面距离                              | 需要模板5.2.1
//  5.6.5--计算点线距离                              |
//  5.6.6--计算两直线夹角cos值                       |
//  5.6.7--计算两面夹角cos值                         | 需要模板5.2.1
//  5.6.8--计算直线与平面夹角sin值                   | 需要模板5.2.1




//0------基础函数
struct point{
	double x;double y;
	point(){}
    point(double x,double y):x(x),y(y){} 
    point(const point & p):x(p.x),y(p.y){}
//0.1------向量运算 
//0.1.1--向量加减,伸缩
	point operator +(point p){
        return point(x+p.x,y+p.y);
    }
    point operator-(point p){
        return point(x-p.x,y-p.y);
    }
	point operator*(double d){
        return point(x*d,y*d);
    }
	 point operator /(double p){
        return point(x/p,y/p);
    }
//0.1.2--向量叉乘
	double operator^(point p){
        return x*p.y-y*p.x;
    }
//0.1.3--向量点乘
	double operator*(point p){ 
        return x*p.x+ y*p.y;
    }
//0.1.4--两点距离
	double dist(point p){   
        return sqrt( (x-p.x)*(x-p.x)+ (y-p.y)*(y-p.y) );
 }
};
//0.1.5--向量叉积 
double cross(point p0,point a,point b)
{
    return (a-p0)^(b-p0);
}
//0.1.6--向量点积
double dot(point p0,point a,point b)
{
    return (a-p0)*(b-p0);
}



//0.2------计算前置模板
//0.2.1--判断两点是否共线（三点版本）
bool onLine(point q,point x1,point x2)
{
	const double esp=1e-8;
	if(abs((x2.y-q.y)*(x1.x-q.x)-(x1.y-q.y)*(x2.x-q.x))<esp){
		/*如果判断是否在直线上，则这里直接return true*/
		if(q.x<=x1.x&&q.x>=x2.x&&q.y<=x1.y&&q.y>=x2.y)
			return true;
		if(q.x>=x1.x&&q.x<=x2.x&&q.y>=x1.y&&q.y<=x2.y)
			return true;
		return false;
	}
	return false;
}
//0.2.2--两直线交点（四点版本）
point intersecting(point p1,point p2,point q1,point q2){ 
    double d1=( (q2-q1)^(q1-p1) );
    double d2=( (q2-q1)^(p2-p1) );
    return p1+ (p2-p1)*(d1/d2) ;
}






//1------平面直线与点
//1.0--直线类  
struct Line{
    point st , ed ;
    Line(){}
    Line(point s, point e){
        st = s ;
        ed = e ;
    }



//1.1------直线与点的关系  
//1.1.1--判断是否平行
bool par(Line l){
  return ((ed - st)^(l.ed - l.st)) == 0;
}
//1.1.2--判断是否共线
bool onl(Line l){
        return (((ed - st)^(l.ed - st)) == 0 ) && (((ed -st)^(l.ed - st)) == 0) ;
 }
//1.1.3--判断是否在线段上
 bool ons(point Q){
		if((Q.x - st.x) * (ed.y - st.y) == (ed.x - st.x) * (Q.y - st.y)  //叉乘   //保证Q点坐标在st,ed之间   
		&& min(st.x , ed.x) <= Q.x && Q.x <= max(st.x , ed.x)      
		&& min(st.y , ed.y) <= Q.y && Q.y <= max(st.y , ed.y))  
        return true;  
		else  
        return false;
	}
//1.1.4--判断是否垂直
 bool perpendicular(Line l){
		return ((ed-st)*(l.ed-l.st)==0);
}



//1.2------直线与点的数值计算
//1.2.1--两直线交点
point intersectionode(Line l){
        double t = (l.ed - l.st)^(l.st - st) ;
        double t1 = (l.ed - l.st)^(ed - st) ;
        return st + (ed - st) * (t / t1) ;
}
};
//1.2.2--矢量的模
double Norm(point p) 
{   
    return sqrt(p.x * p.x + p.y * p.y);   
}
//1.2.3--点到线最短距离
double disptoline(point p,Line l){
    return fabs( ((p-l.st)^(p-l.ed)) / l.st.dist(l.ed));  
}
double disptoline(point p,point a,point b){  
    return fabs(cross(b,p,a))/a.dist(b);  
} 
//1.2.4--点到直线最近点
point ptoline(Line l,point p){   
		Line l1; 
    	l1.st=l1.ed=p; 
   		l1.ed.x+=l.st.y-l.ed.y,l1.ed.y+=l.ed.x-l.st.x; 
		return l.intersectionode(l1);  
}
//1.2.5--点到线段最近点
point ptoseg(Line l,point p){ 
    Line l1;  
    l1.st=l1.ed=p;
    l1.ed.x+=l.st.y-l.ed.y,l1.ed.y+=l.ed.x-l.st.x;  
    if ( ((p-l1.ed)^(p-l.ed)) * ((p-l1.ed)^(p-l.st)) >eps)  
        return p.dist(l.st)<p.dist(l.ed)?l.st:l.ed;  
    return l.intersectionode(l1);  
}  
//1.2.6--求两直线夹角
double Inclination(Line L1, Line L2)   
{   
    point u = L1.ed - L1.st;   
    point v = L2.ed - L2.st;   
    return acos( (u * v) / (Norm(u)*Norm(v)) );   
}




//1.3------三角形
//1.3.1--外心
point circumcenter(point a,point b,point c){  
    Line u,v;  
    u.st.x=(a.x+b.x)/2;  
    u.st.y=(a.y+b.y)/2;  
    u.ed.x=u.st.x-a.y+b.y;  
    u.ed.y=u.st.y+a.x-b.x;  
    v.st.x=(a.x+c.x)/2;  
    v.st.y=(a.y+c.y)/2;  
    v.ed.x=v.st.x-a.y+c.y;  
    v.ed.y=v.st.y+a.x-c.x;  
    return u.intersectionode(v);  
}   
//1.3.2--内心 
point incenter(point a,point b,point c){  
    Line u,v;  
    double m,n;  
    u.st=a;  
    m=atan2(b.y-a.y,b.x-a.x);  
    n=atan2(c.y-a.y,c.x-a.x);  
    u.ed.x=u.st.x+cos((m+n)/2);  
    u.ed.y=u.st.y+sin((m+n)/2);  
    v.st=b;  
    m=atan2(a.y-b.y,a.x-b.x);  
    n=atan2(c.y-b.y,c.x-b.x);  
    v.ed.x=v.st.x+cos((m+n)/2);  
    v.ed.y=v.st.y+sin((m+n)/2);  
    return u.intersectionode(v); 
}   
//1.3.3--重心
point perpencenter(point a,point b,point c){  
    Line u,v;  
    u.st=c;  
    u.ed.x=u.st.x-a.y+b.y;  
    u.ed.y=u.st.y+a.x-b.x;  
    v.st=b;  
    v.ed.x=v.st.x-a.y+c.y;  
    v.ed.y=v.st.y+a.x-c.x;  
    return u.intersectionode(v);   
}  
//1.3.4--垂心
point barycenter(point a,point b,point c){  
    Line u,v;  
    u.st.x=(a.x+b.x)/2;  
    u.st.y=(a.y+b.y)/2;  
    u.ed=c;  
    v.st.x=(a.x+c.x)/2;  
    v.st.y=(a.y+c.y)/2;  
    v.ed=b;  
     return u.intersectionode(v);   
}    
//1.3.5--费马点
point fermentpoint(point a,point b,point c){  
    point u,v;  
    double step=fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);  
    int i,j,k;  
    u.x=(a.x+b.x+c.x)/3;  
    u.y=(a.y+b.y+c.y)/3;  
    while (step>1e-10)  
        for (k=0;k<10;step/=2,k++)  
            for (i=-1;i<=1;i++)  
                for (j=-1;j<=1;j++){  
                    v.x=u.x+step*i;  
                    v.y=u.y+step*j;  
                    if (u.dist(a)+u.dist(b)+u.dist(c)>v.dist(a)+v.dist(b)+v.dist(c))  
                        u=v;  
                }  
    return u;  
}  
  




//2------多边形 

//2.1------多边形基础判断与计算
//2.1.1--点是否在多边形内部
bool in_the_area(point q,point area[],int n) //area需逆时针排序
{
	int ans=0;
	double x;
	for(int i=1;i<=n;i++){
		point p1=area[i];
		point p2=area[i+1];
		if(onLine(q,p1,p2))return true;
		if(q.y<min(p1.y,p2.y))continue;
		if(q.y>=max(p1.y,p2.y))continue;
		x=(q.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
		if(x>q.x)ans++;
	}
	return(ans%2==1);
}
//2.1.2--求凸多边形面积
double area(point s[],int n)
{
	double ret=0;
	s[n+1]=s[1];
	for(int i=1;i<=n;i++)
		ret+=s[i]^s[i+1];
	return fabs(ret/2);
}



//2.2------凸包问题 
//2.2.1--求凸包
point p[233]={};//存储题目所给点
//前置函数 极角排序
bool cmp(point a,point b)
{
	double temp=cross(p[0],a,b);
	if(temp>0)return 1;
	else if(fabs(temp)<eps&&p[0].dist(a)<p[0].dist(b))return 1;
	else return 0;
}
void sortpoint(int n)
{
	int i,k;
	point start;
	start=p[0];
	k=0;
	for(i=1;i<n;i++){
		if((start.y>p[i].y)||(fabs(start.y-p[i].y)<eps&&start.x>p[i].x))	{
			start=p[i];
			k=i;
		}
	}
	p[k]=p[0];
	p[0]=start;
	sort(p+1,p+n,cmp);
}
//去重
void be_weight(int val){
	int temp=val;
	int n=1;
	for(int i=1;i<temp;i++)
	{
		if(fabs(p[i-1].x-p[i].x)<eps&&fabs(p[i-1].y-p[i].y)<eps)
			continue;
		p[n++]=p[i];
	}
}
int convexhull(point p[],point ch[],int n)
{
	int i;
	int cnt=0;
	if(n==1){
		ch[0]=p[0];
		cnt=1;
	}
	else
		if(n==2){
			ch[0]=p[0];
			ch[1]=p[1];
			ch[2]=p[2];
			cnt=2;
		}
	else{
			ch[0]=p[n-1];
			ch[1]=p[0];
			ch[2]=p[1];
			cnt=2;
			for(i=2;i<n;i++){
				while(cross(ch[cnt-1],ch[cnt],p[i])<0)//弹出不合法点
					cnt--;
				ch[++cnt]=p[i];
			}
		}
		return cnt;
}
//2.2.2--求凸包面积
double area(int cnt,point ch[])
{
	double sum=0;
	point p(0,0);
	for(int i=1;i<=cnt;i++)
		sum+=cross(p,ch[i-1],ch[i]);
	return fabs(sum/2.0);
}
//2.2.3--求凸包周长
double perimeter(int cnt,point ch[])
{
	double sum=0;
	for(int i=1;i<=cnt;i++)
		sum+=ch[i-1].dist(ch[i]);
	return sum;
}
//2.2.4--求凸包重心
point bartcenter(int n,point p[])
{
	double sum=0;
	point ret(0.0,0.0);
		for(int i=2;i<n;i++)
		{
			double area=cross(p[0],p[i-1],p[i]);
			sum+=area;
			ret=ret+(p[0]+p[i-1]+p[i])/3.0*area;
		}
		ret=ret/sum;
		return ret;
}
//2.2.5--求面积最大三角形 
double maxtriangle(int cnt,point p[])
{
    double maxn=0;
    int j=1;
    int k=1;
    for(int i=1;i<=cnt;i++)
    {
        while(fabs(cross(p[i-1],p[j%cnt],p[(k+1)%cnt]))>fabs(cross(p[i-1],p[j%cnt],p[k%cnt])))
            k++;
        maxn=max(maxn,fabs(cross(p[i-1],p[j%cnt],p[k%cnt])));
        while(fabs(cross(p[i-1],p[(j+1)%cnt],p[k%cnt]))>fabs(cross(p[i-1],p[j%cnt],p[k%cnt])))
            j++;
        maxn=max(maxn,fabs(cross(p[i-1],p[j%cnt],p[k%cnt])));
    }
    return maxn/2.0;
}
//2.2.6--求面积最小环绕矩形
double minrectangleS(int cnt,point q[])
{
   double S=INF;
    if(cnt<=2)
    {
        if(cnt==1)
           return 0.0;
        else
           return 0.0;
    }

    int j,k,r;
    double h,w;
    j=k=r=1;
    for(int i=1;i<=cnt;i++)
    {
        double L=q[i-1].dist(q[i]);
        while(fabs(cross(q[i-1],q[i],q[(j+1)%cnt]))>fabs(cross(q[i-1],q[i],q[j%cnt])))
            j++;
        h=fabs(cross(q[i-1],q[i],q[j%cnt]))/L;
        while(dot(q[i-1],q[i],q[(k+1)%cnt])>dot(q[i-1],q[i],q[k%cnt]))
            k++;
        if(i==1)
            r=k;
        while(dot(q[i-1],q[i],q[(r+1)%cnt])<=dot(q[i-1],q[i],q[r%cnt]))
            r++;
        w=(dot(q[i-1],q[i],q[k%cnt])-dot(q[i-1],q[i],q[r%cnt]))/L;
        S=min(S,w*h);
    }
    return S;
}
//2.2.7--求周长最小环绕矩形
double minrectangleC(int cnt,point q[])
{
	double C=INF;
    if(cnt<=2)
    {
        if(cnt==1)
           return 0.0;
        else
           return 2*p[0].dist(p[1]);
    }

    int j,k,r;
    double h,w;
    j=k=r=1;
    for(int i=1;i<=cnt;i++)
    {
        double L=q[i-1].dist(q[i]);
        while(fabs(cross(q[i-1],q[i],q[(j+1)%cnt]))>fabs(cross(q[i-1],q[i],q[j%cnt])))
            j++;
        h=fabs(cross(q[i-1],q[i],q[j%cnt]))/L;
        while(dot(q[i-1],q[i],q[(k+1)%cnt])>dot(q[i-1],q[i],q[k%cnt]))
            k++;
        if(i==1)
            r=k;
        while(dot(q[i-1],q[i],q[(r+1)%cnt])<=dot(q[i-1],q[i],q[r%cnt]))
            r++;
        w=(dot(q[i-1],q[i],q[k%cnt])-dot(q[i-1],q[i],q[r%cnt]))/L;
        C=min(C,(w+h)*2);
    }
   return C;
}



//2.3-------旋转卡壳
//2.3.1--求凸包直径-最大点对距离
double diameter(int cnt,point p[])
{
	double maxn=0;
	int j=1;
	for(int i=1;i<cnt;i++)
	{
		while(fabs(cross(p[i-1],p[i],p[(j+1)%cnt]))>fabs(cross(p[i-1],p[i],p[j%cnt])))
			j++;
		maxn=max(maxn,p[i-1].dist(p[j%cnt]));
		maxn=max(maxn,p[i].dist(p[j%cnt]));
	}
	return maxn;
}




//3------圆

//3.1------圆的基础基础判断与计算 
//3.1.1--三点求圆心 
point geto(point p1,point p2,point p3)
{
	point res;
	double a=p2.x-p1.x;
	double b=p2.y-p1.y;
	double c=p3.x-p2.x;
	double d=p3.y-p2.y;
	double e=(p2.x)*(p2.x)+(p2.y)*(p2.y)-(p1.x)*(p1.x)-(p1.y)*(p1.y);
	double f=(p3.x)*(p3.x)+(p3.y)*(p3.y)-(p2.x)*(p2.x)-(p2.y)*(p2.y);
	res.x=(f*b-e*d)/(c*b-a*d)/2.0;
	res.y=(a*f-e*c)/(a*d-b*c)/2.0;
	return res;
}
//3.1.2--判断与直线相交相切
int intersect_line_circle(point c,double r,point l1,point l2){  
    return disptoline(c,l1,l2)<r+eps;  
}  
//3.1.3--判断与线段相交相切 
int intersect_seg_circle(point c,double r,point l1,point l2){  
    double t1=c.dist(l1)-r,t2=c.dist(l2)-r;  
    point t=c;  
    if (t1<eps||t2<eps)  
        return t1>-eps||t2>-eps;  
    t.x+=l1.y-l2.y;  
    t.y+=l2.x-l1.x;  
    return cross(t,l1,c)*cross(t,l2,c)<eps&&disptoline(c,l1,l2)-r<eps;  
}  
//3.1.4--判断与圆相交相切  
int intersect_circle_circle(point c1,double r1,point c2,double r2){  
    return c1.dist(c2)<r1+r2+eps&&c1.dist(c2)>fabs(r1-r2)-eps;  
}  




//3.2------圆的计算
//3.2.1--计算圆上到点的最近点
point dot_to_circle(point c,double r,point p){  
    point u,v;  
    if (distance(p,c)<eps)  
        return p;  
    u.x=c.x+r*fabs(c.x-p.x)/c.dist(p);  
    u.y=c.y+r*fabs(c.y-p.y)/c.dist(p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);  
    v.x=c.x-r*fabs(c.x-p.x)/c.dist(p);  
    v.y=c.y-r*fabs(c.y-p.y)/c.dist(p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);  
    return u.dist(p)<v.dist(p)?u:v;  
}  
//3.2.2--计算线段与圆的交点
void intersection_line_circle(point c,double r,point l1,point l2,point& p1,point& p2){  
    point p=c;  
    double t;  
    p.x+=l1.y-l2.y;  
    p.y+=l2.x-l1.x;  
    p=intersecting(p,c,l1,l2);  
    t=sqrt(r*r-p.dist(c)*p.dist(c))/l1.dist(l2);  
    p1.x=p.x+(l2.x-l1.x)*t;  
    p1.y=p.y+(l2.y-l1.y)*t;  
    p2.x=p.x-(l2.x-l1.x)*t;  
    p2.y=p.y-(l2.y-l1.y)*t;  
}  
//3.2.3--计算圆与圆的交点 
void intersection_circle_circle(point c1,double r1,point c2,double r2,point& p1,point& p2){  
    point u,v;  
    double t;  
    t=(1+(r1*r1-r2*r2)/c1.dist(c2)/c1.dist(c2))/2;  
    u.x=c1.x+(c2.x-c1.x)*t;  
    u.y=c1.y+(c2.y-c1.y)*t;  
    v.x=u.x+c1.y-c2.y;  
    v.y=u.y-c1.x+c2.x;  
    intersection_line_circle(c1,r1,u,v,p1,p2);  
}  
//3.2.5--将向量旋转一定角度    
point Rotate(point p,double angle) {  
    point res;  
    res.x=p.x*cos(angle)-p.y*sin(angle);  
    res.y=p.x*sin(angle)+p.y*cos(angle);  
    return res;  
} 
//3.2.6--计算圆外一点做直线与圆的切点
void TangentPoint_PC(point poi,point o,double r,point &result1,point &result2) {  
    double line=sqrt((poi.x-o.x)*(poi.x-o.x)+(poi.y-o.y)*(poi.y-o.y));  
    double angle=acos(r/line);  
    point unitvector,lin;  
    lin.x=poi.x-o.x;  
    lin.y=poi.y-o.y;  
    unitvector.x=lin.x/sqrt(lin.x*lin.x+lin.y*lin.y)*r;  
    unitvector.y=lin.y/sqrt(lin.x*lin.x+lin.y*lin.y)*r;  
    result1=Rotate(unitvector,-angle);  
    result2=Rotate(unitvector,angle);  
    result1.x+=o.x;  
    result1.y+=o.y;  
    result2.x+=o.x;  
    result2.y+=o.y;  
    return;  
} 
//3.2.4--计算两圆相交部分面积
double intersect(double x1,double y1,double r1,double x2,double y2,double r2){
	double s,temp,p,l,ans;
	const double pi=acos(-1);
	l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	if(l>=r1+r2)	ans=0;
	else if(l<=abs(r1-r2)){
		if(r1<=r2)	    ans=pi*r1*r1;
		else			ans=pi*r2*r2;
	}
	else{
		p=(l+r1+r2)/2;
		s=2*sqrt(p*(p-l)*(p-r1)*(p-r2));
		if(r1>r2){
			temp=x1;x1=x2;x2=temp;
			temp=y1;y1=y2;y2=temp;
            temp=r1;r1=r2;r2=temp;
		}
		ans=acos((r1*r1+l*l-r2*r2)/(2*r1*l))*r1*r1+acos((r2*r2+l*l-r1*r1)/(2*r2*l))*r2*r2-s;
	}
	return ans;
}




//3.3------最小圆覆盖 
//3.3.1--最小圆覆盖基础模板 
void mincir(point &o,double &r, point p[],int n)
{
	o=p[1];
	r=0;
	for(int i=0;i<n;++i){
		if(p[i].dist(o)-r>eps){
			o=p[i];
			r=0;
			for(int j=0;j<i;j++){
				if(p[j].dist(o)-r>eps){
					o.x=(p[i].x+p[j].x)/2.0;
					o.y=(p[i].y+p[j].y)/2.0;
				r=p[i].dist(p[j])/2.0;
				for(int k=0;k<j;++k)
					if(p[k].dist(o)-r>eps){
						o=geto(p[i],p[j],p[k]);
						r=p[i].dist(o);
					}
				}
			}
		}
	}
}



//4------构造

//4.1------网格
//4.1.1--多边形上的格点数
inline int gcd(int a,int b) {
    int r;while(b>0) {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}
int grid_onedge(int n,point* p){  
    int i,ret=0;  
    for (i=0;i<n;i++)  
        ret+=gcd(abs(p[i].x-p[(i+1)%n].x),abs(p[i].y-p[(i+1)%n].y));  
    return ret;  
}  
//4.1.2--多边形内的格点数
int grid_inside(int n,point* p){  
    int i,ret=0;  
    for (i=0;i<n;i++)  
        ret+=p[(i+1)%n].y*(p[i].x-p[(i+2)%n].x);  
    return (abs(ret)-grid_onedge(n,p))/2+1;  
}



//5------三维几何

//5.0------三维点类
struct zpoint{
	double x,y,z;
};  
struct zline{
	zpoint a,b;
};
struct zplane{
	zpoint a,b,c;
};  




//5.1------三维基础函数
//5.1.1--向量长度 
double vlen(zpoint a){
	return sqrt((a.x)*(a.x)+(a.y)*(a.y)+(a.z)*(a.z));
}
//5.1.1--线段长度 
double dis(zpoint a,zpoint b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
//5.1.3--叉积
zpoint xmult(zpoint a,zpoint b){  
    zpoint ret;  
    ret.x=a.y*b.z-a.z*b.y;  
    ret.y=a.z*b.x-a.x*b.z;  
    ret.z=a.x*b.y-a.y*b.x;  
    return ret;  
}  
//5.1.4--点积
double dmult(zpoint a,zpoint b){  
    return a.x*b.x+a.y*b.y+a.z*b.z;  
}  
//5.1.5--矢差
zpoint subt(zpoint a,zpoint b){  
    zpoint ret;  
    ret.x=a.x-b.x;  
    ret.y=a.y-b.y;  
    ret.z=a.z-b.z;  
    return ret;  
}  




//5.2------共面共线关系
//5.2.1--平面法向量
//给出平面
zpoint pvec(zplane s){  
    return xmult(subt(s.a,s.b),subt(s.b,s.c));  
}  
//给出三点
zpoint pvec(zpoint s1,zpoint s2,zpoint s3){  
    return xmult(subt(s1,s2),subt(s2,s3));  
}  
//5.2.2--判断三点共线
int dots_inline(zpoint p1,zpoint p2,zpoint p3){  
    return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;  
}  
//5.2.3--判断四点共面
int dots_onplane(zpoint a,zpoint b,zpoint c,zpoint d){  
    return zero(dmult(pvec(a,b,c),subt(d,a)));  
}  
//5.2.4--判断点是否在线段上
//5.2.4.1-包括端点和共线
 //给定点线
int dot_online_in(zpoint p,zline l){  
    return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&  
        (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;  
}  
 //给定三点
int dot_online_in(zpoint p,zpoint l1,zpoint l2){  
    return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&  
        (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;  
}    
//5.2.4.2-不包括端点
//给定点线
int dot_online_ex(zpoint p,zline l){  
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&  
        (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));  
}  
 //给定三点
int dot_online_ex(zpoint p,zpoint l1,zpoint l2){  
    return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&  
        (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));  
}  
//5.2.5--判断点是否在空间三角形上
//5.2.5.1-包括边界
 //给定点面
int dot_inplane_in(zpoint p,zplane s){  
    return zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));  
}  
 //给定四点
int dot_inplane_in(zpoint p,zpoint s1,zpoint s2,zpoint s3){  
    return zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-  
        vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));  
}  
//5.2.5.2-不包括边界
 //给定点面
int dot_inplane_ex(zpoint p,zplane s){  
    return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;  
}  
 //给定四点
int dot_inplane_ex(zpoint p,zpoint s1,zpoint s2,zpoint s3){  
    return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&  
        vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;  
}  



//5.3------拓扑关系
//5.3.1--两点在线段同侧
int same_side(zpoint p1,zpoint p2,zline l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))>eps;  
}  
int same_side(zpoint p1,zpoint p2,zpoint l1,zpoint l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))>eps;  
}  
//5.3.2--两点在线段异侧
int opposite_side(zpoint p1,zpoint p2,zline l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))<-eps;  
}  
int opposite_side(zpoint p1,zpoint p2,zpoint l1,zpoint l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))<-eps;  
}  
//5.3.3--两点在平面同侧
int same_side(zpoint p1,zpoint p2,zplane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))>eps;  
}  
int same_side(zpoint p1,zpoint p2,zpoint s1,zpoint s2,zpoint s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))>eps;  
}  
//5.3.4--两点在平面异侧
int opposite_side(zpoint p1,zpoint p2,zplane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))<-eps;  
}  
int opposite_side(zpoint p1,zpoint p2,zpoint s1,zpoint s2,zpoint s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))<-eps;  
}  



//5.4------平行垂直相交关系 
//5.4.1--两线平行
int parallel(zline u,zline v){  
    return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;  
}  
int parallel(zpoint u1,zpoint u2,zpoint v1,zpoint v2){  
    return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;  
}  
//5.4.2--两面平行
int parallel(zplane u,zplane v){  
    return vlen(xmult(pvec(u),pvec(v)))<eps;  
}  
int parallel(zpoint u1,zpoint u2,zpoint u3,zpoint v1,zpoint v2,zpoint v3){  
    return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;  
}  
//5.4.3--线面平行
int parallel(zline l,zplane s){  
    return zero(dmult(subt(l.a,l.b),pvec(s)));  
}  
int parallel(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));  
}  
//5.4.4--两线垂直
int perpendicular(zline u,zline v){  
    return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));  
}  
int perpendicular(zpoint u1,zpoint u2,zpoint v1,zpoint v2){  
    return zero(dmult(subt(u1,u2),subt(v1,v2)));  
}  
//5.4.5--两面垂直
int perpendicular(zplane u,zplane v){  
    return zero(dmult(pvec(u),pvec(v)));  
}  
int perpendicular(zpoint u1,zpoint u2,zpoint u3,zpoint v1,zpoint v2,zpoint v3){  
    return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));  
}  
//5.4.6--线面垂直
int perpendicular(zline l,zplane s){  
    return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;  
}  
int perpendicular(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;  
}  



//5.5------空间线段
//5.5.1--判断两线段相交
//5.5.1.1-包括端点和共线
//给定两线
int intersect_in(zline u,zline v){  
    if (!dots_onplane(u.a,u.b,v.a,v.b))  
        return 0;  
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))  
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);  
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);  
}  
//给定四点
int intersect_in(zpoint u1,zpoint u2,zpoint v1,zpoint v2){  
    if (!dots_onplane(u1,u2,v1,v2))  
        return 0;  
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))  
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);  
    return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);  
}  
//5.5.1.2-不包括端点
//给定线面
int intersect_in(zline l,zplane s){  
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&  
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);  
}  
//给定五点
int intersect_in(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&  
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);  
}  
//5.5.2--判断线段与空间三角形相交
//5.5.5.1-包括边界和部分包含
int intersect_in(zline l,zplane s){  
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&  
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);  
}  
//给定五点
int intersect_in(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&  
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);  
}  
//5.5.5.2-不包括边界和部分包含
//给定线面
int intersect_ex(zline l,zplane s){  
    return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&  
        opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);  
}  
//给定五点
int intersect_ex(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&  
        opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);  
}  




//5.6------空间几何计算
//5.6.1--计算两直线交点
//若平行会出错
 //给定两线
zpoint intersection(zline u,zline v){  
    zpoint ret=u.a;  
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))  
            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));  
    ret.x+=(u.b.x-u.a.x)*t;  
    ret.y+=(u.b.y-u.a.y)*t;  
    ret.z+=(u.b.z-u.a.z)*t;  
    return ret;  
}  
 //给定四点
zpoint intersection(zpoint u1,zpoint u2,zpoint v1,zpoint v2){  
    zpoint ret=u1;  
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))  
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));  
    ret.x+=(u2.x-u1.x)*t;  
    ret.y+=(u2.y-u1.y)*t;  
    ret.z+=(u2.z-u1.z)*t;  
    return ret;  
}  
//5.6.2--计算直线与平面交点
//若平行共线会出错
 //给定线面
zpoint intersection(zline l,zplane s){  
    zpoint ret=pvec(s);  
    double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/  
        (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));  
    ret.x=l.a.x+(l.b.x-l.a.x)*t;  
    ret.y=l.a.y+(l.b.y-l.a.y)*t;  
    ret.z=l.a.z+(l.b.z-l.a.z)*t;  
    return ret;  
}  
 //给定五点
zpoint intersection(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    zpoint ret=pvec(s1,s2,s3);  
    double t=(ret.x*(s1.x-l1.x)+ret.y*(s1.y-l1.y)+ret.z*(s1.z-l1.z))/  
        (ret.x*(l2.x-l1.x)+ret.y*(l2.y-l1.y)+ret.z*(l2.z-l1.z));  
    ret.x=l1.x+(l2.x-l1.x)*t;  
    ret.y=l1.y+(l2.y-l1.y)*t;  
    ret.z=l1.z+(l2.z-l1.z)*t;  
    return ret;  
}  
//5.6.3--计算两面交线
//平行重合会出错
 //给定两面
zline intersection(zplane u,zplane v){  
    zline ret;  
    ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.c);  
    ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.c);  
    return ret;  
}  
 //给定六点
zline intersection(zpoint u1,zpoint u2,zpoint u3,zpoint v1,zpoint v2,zpoint v3){  
    zline ret;  
    ret.a=parallel(v1,v2,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v1,v2,u1,u2,u3);  
    ret.b=parallel(v3,v1,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v3,v1,u1,u2,u3);  
    return ret;  
}  
//5.6.4--计算点面距离
//给定点面
double ptoplane(zpoint p,zplane s){  
    return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));  
}  
//给定四点
double ptoplane(zpoint p,zpoint s1,zpoint s2,zpoint s3){  
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));  
}  
//5.6.5--计算点线距离
//给定点线
double zptoline(zpoint p,zline l){  
    return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/dis(l.a,l.b);  
}  
//给定三点
double ptoline(zpoint p,zpoint l1,zpoint l2){  
    return vlen(xmult(subt(p,l1),subt(l2,l1)))/dis(l1,l2);  
}  
//5.6.6--计算两直线夹角cos值
//给定两线
double angle_cos(zline u,zline v){  
    return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));  
}  
//给定四点
double angle_cos(zpoint u1,zpoint u2,zpoint v1,zpoint v2){  
    return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));  
}  
//5.6.7--计算两面夹角cos值
//给定两面
double angle_cos(zplane u,zplane v){  
    return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));  
}  
//给定六点
double angle_cos(zpoint u1,zpoint u2,zpoint u3,zpoint v1,zpoint v2,zpoint v3){  
    return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));  
}  
//5.6.8--计算直线与平面夹角sin值
double angle_sin(zline l,zplane s){  
    return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));  
}  
//给定六点
double angle_sin(zpoint l1,zpoint l2,zpoint s1,zpoint s2,zpoint s3){  
    return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));  
} 
