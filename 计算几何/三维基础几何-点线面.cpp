// 三维计算几何.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>  
#define eps 1e-8  
#define zero(x) (((x)>0?(x):-(x))<eps)  
struct point{
	double x,y,z;
};  
struct line{
	point a,b;
};  
struct plane{
	point a,b,c;
};  
/*向量长度*/
double vlen(point a){
	return sqrt((a.x)*(a.x)+(a.y)*(a.y)+(a.z)*(a.z));
}
/*直线长度*/
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
/*叉积*/
point xmult(point a,point b){  
    point ret;  
    ret.x=a.y*b.z-a.z*b.y;  
    ret.y=a.z*b.x-a.x*b.z;  
    ret.z=a.x*b.y-a.y*b.x;  
    return ret;  
}  
/*点积*/
double dmult(point a,point b){  
    return a.x*b.x+a.y*b.y+a.z*b.z;  
}  
/*矢差*/
point subt(point a,point b){  
    point ret;  
    ret.x=a.x-b.x;  
    ret.y=a.y-b.y;  
    ret.z=a.z-b.z;  
    return ret;  
}  
/*平面法向量*/////////////////////////////////////////////////////////////////////////////////////////////////////////
//给出平面
point pvec(plane s){  
    return xmult(subt(s.a,s.b),subt(s.b,s.c));  
}  
//给出三点
point pvec(point s1,point s2,point s3){  
    return xmult(subt(s1,s2),subt(s2,s3));  
}  
/*判三点共线*/
int dots_inline(point p1,point p2,point p3){  
    return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;  
}  
/*判四点共面*/
int dots_onplane(point a,point b,point c,point d){  
    return zero(dmult(pvec(a,b,c),subt(d,a)));  
}  
/*判点是否在线段上*/
//包括端点和共线  
 //给定点线
int dot_online_in(point p,line l){  
    return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&  
        (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;  
}  
 //给定三点
int dot_online_in(point p,point l1,point l2){  
    return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&  
        (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;  
}    
//不包括端点  
 //给定点线
int dot_online_ex(point p,line l){  
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&  
        (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));  
}  
 //给定三点
int dot_online_ex(point p,point l1,point l2){  
    return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&  
        (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));  
}  
  
  
/*判点是否在空间三角形上*//////////////////////////////////////////////////////////////////////////////////////////
//包括边界
 //给定点面
int dot_inplane_in(point p,plane s){  
    return zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));  
}  
 //给定四点
int dot_inplane_in(point p,point s1,point s2,point s3){  
    return zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-  
        vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));  
}  
  
  
/*判点是否在空间三角形上,不包括边界,三点共线无意义  *//////////////////////////////////////////////////////////////
 //给定点面
int dot_inplane_ex(point p,plane s){  
    return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;  
}  
 //给定四点
int dot_inplane_ex(point p,point s1,point s2,point s3){  
    return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&  
        vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;  
}  
  
  
/*判两点在线段同侧,点在线段上返回0,不共面无意义  */////////////////////////////////////////////////////////////////
int same_side(point p1,point p2,line l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))>eps;  
}  
int same_side(point p1,point p2,point l1,point l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))>eps;  
}  
  
  
/*判两点在线段异侧,点在线段上返回0,不共面无意义  */
int opposite_side(point p1,point p2,line l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))<-eps;  
}  
int opposite_side(point p1,point p2,point l1,point l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))<-eps;  
}  
  
  
/*判两点在平面同侧,点在平面上返回0  */
int same_side(point p1,point p2,plane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))>eps;  
}  
int same_side(point p1,point p2,point s1,point s2,point s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))>eps;  
}  
  
  
/*判两点在平面异侧,点在平面上返回0  */
int opposite_side(point p1,point p2,plane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))<-eps;  
}  
int opposite_side(point p1,point p2,point s1,point s2,point s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))<-eps;  
}  
  
  
/*判两直线平行  *////////////////////////////////////////////////////////////////////////////////////////////////
int parallel(line u,line v){  
    return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;  
}  
int parallel(point u1,point u2,point v1,point v2){  
    return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;  
}  
  
  
/*判两平面平行  */
int parallel(plane u,plane v){  
    return vlen(xmult(pvec(u),pvec(v)))<eps;  
}  
int parallel(point u1,point u2,point u3,point v1,point v2,point v3){  
    return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;  
}  
  
  
/*判直线与平面平行  */
int parallel(line l,plane s){  
    return zero(dmult(subt(l.a,l.b),pvec(s)));  
}  
int parallel(point l1,point l2,point s1,point s2,point s3){  
    return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));  
}  
  
  
/*判两直线垂直  */
int perpendicular(line u,line v){  
    return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));  
}  
int perpendicular(point u1,point u2,point v1,point v2){  
    return zero(dmult(subt(u1,u2),subt(v1,v2)));  
}  
  
  
/*判两平面垂直  */
int perpendicular(plane u,plane v){  
    return zero(dmult(pvec(u),pvec(v)));  
}  
int perpendicular(point u1,point u2,point u3,point v1,point v2,point v3){  
    return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));  
}  
  
  
/*判直线与平面平行 */ 
int perpendicular(line l,plane s){  
    return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;  
}  
int perpendicular(point l1,point l2,point s1,point s2,point s3){  
    return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;  
}  
  
  
/*判两线段相交,包括端点和部分重合  *//////////////////////////////////////////////////////////////////////////////////
//给定两线
int intersect_in(line u,line v){  
    if (!dots_onplane(u.a,u.b,v.a,v.b))  
        return 0;  
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))  
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);  
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);  
}  
//给定四点
int intersect_in(point u1,point u2,point v1,point v2){  
    if (!dots_onplane(u1,u2,v1,v2))  
        return 0;  
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))  
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);  
    return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);  
}  
  
  
/*判两线段相交,不包括端点和部分重合 */ 
//给定两线
int intersect_ex(line u,line v){  
    return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);  
} 
//给定四点
int intersect_ex(point u1,point u2,point v1,point v2){  
    return dots_onplane(u1,u2,v1,v2)&&opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);  
}  
  
  
/*判线段与空间三角形相交,包括交于边界和(部分)包含  */
//给定线面
int intersect_in(line l,plane s){  
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&  
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);  
}  
//给定五点
int intersect_in(point l1,point l2,point s1,point s2,point s3){  
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&  
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);  
}  
  
  
/*判线段与空间三角形相交,不包括交于边界和(部分)包含  */
//给定线面
int intersect_ex(line l,plane s){  
    return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&  
        opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);  
}  
//给定五点
int intersect_ex(point l1,point l2,point s1,point s2,point s3){  
    return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&  
        opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);  
}  
  
  
/*计算两直线交点*/////////////////////////////////////////////////////////////////////////////////////
//若平行会出错
 //给定两线
point intersection(line u,line v){  
    point ret=u.a;  
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))  
            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));  
    ret.x+=(u.b.x-u.a.x)*t;  
    ret.y+=(u.b.y-u.a.y)*t;  
    ret.z+=(u.b.z-u.a.z)*t;  
    return ret;  
}  
 //给定四点
point intersection(point u1,point u2,point v1,point v2){  
    point ret=u1;  
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))  
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));  
    ret.x+=(u2.x-u1.x)*t;  
    ret.y+=(u2.y-u1.y)*t;  
    ret.z+=(u2.z-u1.z)*t;  
    return ret;  
}  
  
  
/*计算直线与平面交点*/
//若平行共线会出错
 //给定线面
point intersection(line l,plane s){  
    point ret=pvec(s);  
    double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/  
        (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));  
    ret.x=l.a.x+(l.b.x-l.a.x)*t;  
    ret.y=l.a.y+(l.b.y-l.a.y)*t;  
    ret.z=l.a.z+(l.b.z-l.a.z)*t;  
    return ret;  
}  
 //给定五点
point intersection(point l1,point l2,point s1,point s2,point s3){  
    point ret=pvec(s1,s2,s3);  
    double t=(ret.x*(s1.x-l1.x)+ret.y*(s1.y-l1.y)+ret.z*(s1.z-l1.z))/  
        (ret.x*(l2.x-l1.x)+ret.y*(l2.y-l1.y)+ret.z*(l2.z-l1.z));  
    ret.x=l1.x+(l2.x-l1.x)*t;  
    ret.y=l1.y+(l2.y-l1.y)*t;  
    ret.z=l1.z+(l2.z-l1.z)*t;  
    return ret;  
}  
  
  
/*计算两平面交线*/
//平行重合会出错
 //给定两面
line intersection(plane u,plane v){  
    line ret;  
    ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.c);  
    ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.c);  
    return ret;  
}  
 //给定六点
line intersection(point u1,point u2,point u3,point v1,point v2,point v3){  
    line ret;  
    ret.a=parallel(v1,v2,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v1,v2,u1,u2,u3);  
    ret.b=parallel(v3,v1,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v3,v1,u1,u2,u3);  
    return ret;  
}  
  
  
/*点到直线距离 */////////////////////////////////////////////////////////////////////////////////////////////
//给定点线
double ptoline(point p,line l){  
    return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/dis(l.a,l.b);  
}  
//给定三点
double ptoline(point p,point l1,point l2){  
    return vlen(xmult(subt(p,l1),subt(l2,l1)))/dis(l1,l2);  
}  
  
  
/*点到平面距离  */
//给定点面
double ptoplane(point p,plane s){  
    return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));  
}  
//给定四点
double ptoplane(point p,point s1,point s2,point s3){  
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));  
}  
  
  
/*直线到直线距离  */
//给定两线
double linetoline(line u,line v){  
    point n=xmult(subt(u.a,u.b),subt(v.a,v.b));  
    return fabs(dmult(subt(u.a,v.a),n))/vlen(n);  
}  
//给定四点
double linetoline(point u1,point u2,point v1,point v2){  
    point n=xmult(subt(u1,u2),subt(v1,v2));  
    return fabs(dmult(subt(u1,v1),n))/vlen(n);  
}  
  
  
/*两直线夹角cos值 *//////////////////////////////////////////////////////////////////////////////////////// 
//给定两线
double angle_cos(line u,line v){  
    return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));  
}  
//给定四点
double angle_cos(point u1,point u2,point v1,point v2){  
    return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));  
}  
  
  
/*两平面夹角cos值  */
//给定两面
double angle_cos(plane u,plane v){  
    return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));  
}  
//给定六点
double angle_cos(point u1,point u2,point u3,point v1,point v2,point v3){  
    return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));  
}  
  
  
/*直线平面夹角sin值 */ 
//给定点面
double angle_sin(line l,plane s){  
    return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));  
}  
//给定六点
double angle_sin(point l1,point l2,point s1,point s2,point s3){  
    return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));  
} 
