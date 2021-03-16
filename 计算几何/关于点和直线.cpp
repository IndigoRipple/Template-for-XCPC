// ���ڵ��ֱ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;
typedef long long ll;
const double PI = 3.1415927;
const double EPS=1e-10;
struct point{
    double x,y;
	/*��������*/
    point(){}
    point(double x,double y):x(x),y(y){} 
    point(const point & p):x(p.x),y(p.y){}
    point operator +(point p){
        return point(x+p.x,y+p.y);
    }
    point operator-(point p){
        return point(x-p.x,y-p.y);
    }
    point operator*(double d){
        return point(x*d,y*d);
    }
    double operator*(point p){  // �ڻ� ���
        return x*p.x+ y*p.y;
    }
    double operator^(point p){//  ��� ���
        return x*p.y-y*p.x;
    }
 
    friend ostream& operator<<(ostream& os,const point& p ){
        os<<p.x<<" "<<p.y<<endl;
        return os;
    }
    friend istream& operator>>(istream& is, point&p) {
        is>>p.x>>p.y;
        return is;
    }
   /*�������*/
	double dist(point p){   // p1.dist(p2)
        return sqrt( (x-p.x)*(x-p.x)+ (y-p.y)*(y-p.y) );
    }
};
/*���㽻��(�����ĵ㣩*/
point intersecting(point p1,point p2,point q1,point q2){ 
    double d1=( (q2-q1)^(q1-p1) );
    double d2=( (q2-q1)^(p2-p1) );
    return p1+ (p2-p1)*(d1/d2) ;
}
struct Line{
    point st , ed ;
    Line(){}
    Line(point s, point e){
        st = s ;
        ed = e ;
    }
	/*�ж�ֱ���Ƿ�ƽ��*/
    bool par(Line l){
        return ((ed - st)^(l.ed - l.st)) == 0 ;
    }
	/*�ж�ֱ���Ƿ���*/
    bool onl(Line l){
        return (((ed - st)^(l.ed - st)) == 0 ) && (((ed -st)^(l.ed - st)) == 0) ;
    }
    bool ons(point Q){
	/*�жϵ��Ƿ����߶���  �����˵� */
		if((Q.x - st.x) * (ed.y - st.y) == (ed.x - st.x) * (Q.y - st.y)  //���   //��֤Q��������st,ed֮��   
		&& min(st.x , ed.x) <= Q.x && Q.x <= max(st.x , ed.x)      
		&& min(st.y , ed.y) <= Q.y && Q.y <= max(st.y , ed.y))  
        return true;  
		else  
        return false;
	}
	bool perpendicular(Line l){//�ж�����ֱ���Ƿ�ֱ ��ֱ����1  Ҳ���԰�����ֱ�߻����ĸ��� 
		return ((ed-st)*(l.ed-l.st)==0);
	}
	/*�����ֱ�ߵĽ���*/
    point intersectionode(Line l){
        double t = (l.ed - l.st)^(l.st - st) ;
        double t1 = (l.ed - l.st)^(ed - st) ;
        return st + (ed - st) * (t / t1) ;
    }
	/*����ֱ�ߣ������ĵ㣩*/
    void read(){
        scanf("%lf%lf%lf%lf" , &st.x, &st.y ,&ed.x ,&ed.y);
    }
};
/*����ʸ��p��ģ*/
double Norm(point p) 
{   
    return sqrt(p.x * p.x + p.y * p.y);   
}
/*����㵽ֱ����̾���*/
double disptoline(point p,Line l){
    return fabs( ((p-l.st)^(p-l.ed)) / l.st.dist(l.ed));  
}  
 
/*����㵽ֱ�������*/
point ptoline(Line l,point p){   
		Line l1; 
    	l1.st=l1.ed=p; 
   		l1.ed.x+=l.st.y-l.ed.y,l1.ed.y+=l.ed.x-l.st.x; 
		return l.intersectionode(l1);  
}
 
/*����㵽�߶������*/
point ptoseg(Line l,point p){ 
    Line l1;  
    l1.st=l1.ed=p;
    l1.ed.x+=l.st.y-l.ed.y,l1.ed.y+=l.ed.x-l.st.x;  
    if ( ((p-l1.ed)^(p-l.ed)) * ((p-l1.ed)^(p-l.st)) >EPS)  
        return p.dist(l.st)<p.dist(l.ed)?l.st:l.ed;  
    return l.intersectionode(l1);  
}  
 
/*����㵽�߶���̾���*/
double disptoseg(Line l,point p){  
    Line l1;  
    l1.st=l1.ed=p;
    l1.ed.x+=l.st.y-l.ed.y,l1.ed.y+=l.ed.x-l.st.x;  
	if ( ((p-l1.ed)^(p-l.ed)) * ((p-l1.ed)^(p-l.st)) >EPS)  
        return p.dist(l.st)<p.dist(l.ed)?p.dist(l.st):p.dist(l.ed);  
	return fabs( ((p-l.st)^(p-l.ed)) / l.st.dist(l.ed));  
}  
/*����ֱ�߼н�*/ 
// ����ֵ��0~Pi֮��Ļ���   
double Inclination(Line L1, Line L2)   
{   
    point u = L1.ed - L1.st;   
    point v = L2.ed - L2.st;   
    return acos( (u * v) / (Norm(u)*Norm(v)) );   
}
