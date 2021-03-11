// ��ά���㼸��.cpp : �������̨Ӧ�ó������ڵ㡣
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
/*��������*/
double vlen(point a){
	return sqrt((a.x)*(a.x)+(a.y)*(a.y)+(a.z)*(a.z));
}
/*ֱ�߳���*/
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
/*���*/
point xmult(point a,point b){  
    point ret;  
    ret.x=a.y*b.z-a.z*b.y;  
    ret.y=a.z*b.x-a.x*b.z;  
    ret.z=a.x*b.y-a.y*b.x;  
    return ret;  
}  
/*���*/
double dmult(point a,point b){  
    return a.x*b.x+a.y*b.y+a.z*b.z;  
}  
/*ʸ��*/
point subt(point a,point b){  
    point ret;  
    ret.x=a.x-b.x;  
    ret.y=a.y-b.y;  
    ret.z=a.z-b.z;  
    return ret;  
}  
/*ƽ�淨����*/////////////////////////////////////////////////////////////////////////////////////////////////////////
//����ƽ��
point pvec(plane s){  
    return xmult(subt(s.a,s.b),subt(s.b,s.c));  
}  
//��������
point pvec(point s1,point s2,point s3){  
    return xmult(subt(s1,s2),subt(s2,s3));  
}  
/*�����㹲��*/
int dots_inline(point p1,point p2,point p3){  
    return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;  
}  
/*���ĵ㹲��*/
int dots_onplane(point a,point b,point c,point d){  
    return zero(dmult(pvec(a,b,c),subt(d,a)));  
}  
/*�е��Ƿ����߶���*/
//�����˵�͹���  
 //��������
int dot_online_in(point p,line l){  
    return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&  
        (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;  
}  
 //��������
int dot_online_in(point p,point l1,point l2){  
    return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&  
        (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;  
}    
//�������˵�  
 //��������
int dot_online_ex(point p,line l){  
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&  
        (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));  
}  
 //��������
int dot_online_ex(point p,point l1,point l2){  
    return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&  
        (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));  
}  
  
  
/*�е��Ƿ��ڿռ���������*//////////////////////////////////////////////////////////////////////////////////////////
//�����߽�
 //��������
int dot_inplane_in(point p,plane s){  
    return zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));  
}  
 //�����ĵ�
int dot_inplane_in(point p,point s1,point s2,point s3){  
    return zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-  
        vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));  
}  
  
  
/*�е��Ƿ��ڿռ���������,�������߽�,���㹲��������  *//////////////////////////////////////////////////////////////
 //��������
int dot_inplane_ex(point p,plane s){  
    return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;  
}  
 //�����ĵ�
int dot_inplane_ex(point p,point s1,point s2,point s3){  
    return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&  
        vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;  
}  
  
  
/*���������߶�ͬ��,�����߶��Ϸ���0,������������  */////////////////////////////////////////////////////////////////
int same_side(point p1,point p2,line l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))>eps;  
}  
int same_side(point p1,point p2,point l1,point l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))>eps;  
}  
  
  
/*���������߶����,�����߶��Ϸ���0,������������  */
int opposite_side(point p1,point p2,line l){  
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))<-eps;  
}  
int opposite_side(point p1,point p2,point l1,point l2){  
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))<-eps;  
}  
  
  
/*��������ƽ��ͬ��,����ƽ���Ϸ���0  */
int same_side(point p1,point p2,plane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))>eps;  
}  
int same_side(point p1,point p2,point s1,point s2,point s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))>eps;  
}  
  
  
/*��������ƽ�����,����ƽ���Ϸ���0  */
int opposite_side(point p1,point p2,plane s){  
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))<-eps;  
}  
int opposite_side(point p1,point p2,point s1,point s2,point s3){  
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))<-eps;  
}  
  
  
/*����ֱ��ƽ��  *////////////////////////////////////////////////////////////////////////////////////////////////
int parallel(line u,line v){  
    return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;  
}  
int parallel(point u1,point u2,point v1,point v2){  
    return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;  
}  
  
  
/*����ƽ��ƽ��  */
int parallel(plane u,plane v){  
    return vlen(xmult(pvec(u),pvec(v)))<eps;  
}  
int parallel(point u1,point u2,point u3,point v1,point v2,point v3){  
    return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;  
}  
  
  
/*��ֱ����ƽ��ƽ��  */
int parallel(line l,plane s){  
    return zero(dmult(subt(l.a,l.b),pvec(s)));  
}  
int parallel(point l1,point l2,point s1,point s2,point s3){  
    return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));  
}  
  
  
/*����ֱ�ߴ�ֱ  */
int perpendicular(line u,line v){  
    return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));  
}  
int perpendicular(point u1,point u2,point v1,point v2){  
    return zero(dmult(subt(u1,u2),subt(v1,v2)));  
}  
  
  
/*����ƽ�洹ֱ  */
int perpendicular(plane u,plane v){  
    return zero(dmult(pvec(u),pvec(v)));  
}  
int perpendicular(point u1,point u2,point u3,point v1,point v2,point v3){  
    return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));  
}  
  
  
/*��ֱ����ƽ��ƽ�� */ 
int perpendicular(line l,plane s){  
    return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;  
}  
int perpendicular(point l1,point l2,point s1,point s2,point s3){  
    return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;  
}  
  
  
/*�����߶��ཻ,�����˵�Ͳ����غ�  *//////////////////////////////////////////////////////////////////////////////////
//��������
int intersect_in(line u,line v){  
    if (!dots_onplane(u.a,u.b,v.a,v.b))  
        return 0;  
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))  
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);  
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);  
}  
//�����ĵ�
int intersect_in(point u1,point u2,point v1,point v2){  
    if (!dots_onplane(u1,u2,v1,v2))  
        return 0;  
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))  
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);  
    return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);  
}  
  
  
/*�����߶��ཻ,�������˵�Ͳ����غ� */ 
//��������
int intersect_ex(line u,line v){  
    return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);  
} 
//�����ĵ�
int intersect_ex(point u1,point u2,point v1,point v2){  
    return dots_onplane(u1,u2,v1,v2)&&opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);  
}  
  
  
/*���߶���ռ��������ཻ,�������ڱ߽��(����)����  */
//��������
int intersect_in(line l,plane s){  
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&  
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);  
}  
//�������
int intersect_in(point l1,point l2,point s1,point s2,point s3){  
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&  
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);  
}  
  
  
/*���߶���ռ��������ཻ,���������ڱ߽��(����)����  */
//��������
int intersect_ex(line l,plane s){  
    return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&  
        opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);  
}  
//�������
int intersect_ex(point l1,point l2,point s1,point s2,point s3){  
    return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&  
        opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);  
}  
  
  
/*������ֱ�߽���*/////////////////////////////////////////////////////////////////////////////////////
//��ƽ�л����
 //��������
point intersection(line u,line v){  
    point ret=u.a;  
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))  
            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));  
    ret.x+=(u.b.x-u.a.x)*t;  
    ret.y+=(u.b.y-u.a.y)*t;  
    ret.z+=(u.b.z-u.a.z)*t;  
    return ret;  
}  
 //�����ĵ�
point intersection(point u1,point u2,point v1,point v2){  
    point ret=u1;  
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))  
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));  
    ret.x+=(u2.x-u1.x)*t;  
    ret.y+=(u2.y-u1.y)*t;  
    ret.z+=(u2.z-u1.z)*t;  
    return ret;  
}  
  
  
/*����ֱ����ƽ�潻��*/
//��ƽ�й��߻����
 //��������
point intersection(line l,plane s){  
    point ret=pvec(s);  
    double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/  
        (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));  
    ret.x=l.a.x+(l.b.x-l.a.x)*t;  
    ret.y=l.a.y+(l.b.y-l.a.y)*t;  
    ret.z=l.a.z+(l.b.z-l.a.z)*t;  
    return ret;  
}  
 //�������
point intersection(point l1,point l2,point s1,point s2,point s3){  
    point ret=pvec(s1,s2,s3);  
    double t=(ret.x*(s1.x-l1.x)+ret.y*(s1.y-l1.y)+ret.z*(s1.z-l1.z))/  
        (ret.x*(l2.x-l1.x)+ret.y*(l2.y-l1.y)+ret.z*(l2.z-l1.z));  
    ret.x=l1.x+(l2.x-l1.x)*t;  
    ret.y=l1.y+(l2.y-l1.y)*t;  
    ret.z=l1.z+(l2.z-l1.z)*t;  
    return ret;  
}  
  
  
/*������ƽ�潻��*/
//ƽ���غϻ����
 //��������
line intersection(plane u,plane v){  
    line ret;  
    ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.c);  
    ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.c);  
    return ret;  
}  
 //��������
line intersection(point u1,point u2,point u3,point v1,point v2,point v3){  
    line ret;  
    ret.a=parallel(v1,v2,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v1,v2,u1,u2,u3);  
    ret.b=parallel(v3,v1,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v3,v1,u1,u2,u3);  
    return ret;  
}  
  
  
/*�㵽ֱ�߾��� */////////////////////////////////////////////////////////////////////////////////////////////
//��������
double ptoline(point p,line l){  
    return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/dis(l.a,l.b);  
}  
//��������
double ptoline(point p,point l1,point l2){  
    return vlen(xmult(subt(p,l1),subt(l2,l1)))/dis(l1,l2);  
}  
  
  
/*�㵽ƽ�����  */
//��������
double ptoplane(point p,plane s){  
    return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));  
}  
//�����ĵ�
double ptoplane(point p,point s1,point s2,point s3){  
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));  
}  
  
  
/*ֱ�ߵ�ֱ�߾���  */
//��������
double linetoline(line u,line v){  
    point n=xmult(subt(u.a,u.b),subt(v.a,v.b));  
    return fabs(dmult(subt(u.a,v.a),n))/vlen(n);  
}  
//�����ĵ�
double linetoline(point u1,point u2,point v1,point v2){  
    point n=xmult(subt(u1,u2),subt(v1,v2));  
    return fabs(dmult(subt(u1,v1),n))/vlen(n);  
}  
  
  
/*��ֱ�߼н�cosֵ *//////////////////////////////////////////////////////////////////////////////////////// 
//��������
double angle_cos(line u,line v){  
    return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));  
}  
//�����ĵ�
double angle_cos(point u1,point u2,point v1,point v2){  
    return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));  
}  
  
  
/*��ƽ��н�cosֵ  */
//��������
double angle_cos(plane u,plane v){  
    return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));  
}  
//��������
double angle_cos(point u1,point u2,point u3,point v1,point v2,point v3){  
    return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));  
}  
  
  
/*ֱ��ƽ��н�sinֵ */ 
//��������
double angle_sin(line l,plane s){  
    return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));  
}  
//��������
double angle_sin(point l1,point l2,point s1,point s2,point s3){  
    return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));  
} 