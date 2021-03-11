#include<iostream>  
 #include<cmath>  
#include "stdafx.h"
#include <math.h>  
using namespace std;
struct point{
	double x,y;
};  
struct line{point a,b;
};  
  /*求距离*/
double dis(point p1,point p2){  
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));  
}    
 /*求两线交点*/
point in(line u,line v){  
    point ret=u.a;  
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))  
            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));  
    ret.x+=(u.b.x-u.a.x)*t;  
    ret.y+=(u.b.y-u.a.y)*t;  
    return ret;  
}   
/*外心*/  
point circumcenter(point a,point b,point c){  
    line u,v;  
    u.a.x=(a.x+b.x)/2;  
    u.a.y=(a.y+b.y)/2;  
    u.b.x=u.a.x-a.y+b.y;  
    u.b.y=u.a.y+a.x-b.x;  
    v.a.x=(a.x+c.x)/2;  
    v.a.y=(a.y+c.y)/2;  
    v.b.x=v.a.x-a.y+c.y;  
    v.b.y=v.a.y+a.x-c.x;  
    return in(u,v);  
}   
/*内心*/
point incenter(point a,point b,point c){  
    line u,v;  
    double m,n;  
    u.a=a;  
    m=atan2(b.y-a.y,b.x-a.x);  
    n=atan2(c.y-a.y,c.x-a.x);  
    u.b.x=u.a.x+cos((m+n)/2);  
    u.b.y=u.a.y+sin((m+n)/2);  
    v.a=b;  
    m=atan2(a.y-b.y,a.x-b.x);  
    n=atan2(c.y-b.y,c.x-b.x);  
    v.b.x=v.a.x+cos((m+n)/2);  
    v.b.y=v.a.y+sin((m+n)/2);  
    return in(u,v);  
}   
/*垂心*/
point perpencenter(point a,point b,point c){  
    line u,v;  
    u.a=c;  
    u.b.x=u.a.x-a.y+b.y;  
    u.b.y=u.a.y+a.x-b.x;  
    v.a=b;  
    v.b.x=v.a.x-a.y+c.y;  
    v.b.y=v.a.y+a.x-c.x;  
    return in(u,v);  
}  
/*重心*/
point barycenter(point a,point b,point c){  
    line u,v;  
    u.a.x=(a.x+b.x)/2;  
    u.a.y=(a.y+b.y)/2;  
    u.b=c;  
    v.a.x=(a.x+c.x)/2;  
    v.a.y=(a.y+c.y)/2;  
    v.b=b;  
    return in(u,v);  
}    
/*费马点*/
//到三角形三顶点距离之和最小的点  
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
                    if (dis(u,a)+dis(u,b)+dis(u,c)>dis(v,a)+dis(v,b)+dis(v,c))  
                        u=v;  
                }  
    return u;  
}  
  
  
