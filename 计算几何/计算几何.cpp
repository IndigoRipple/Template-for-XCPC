
#include "stdafx.h"
#include<iostream>
#include<cmath>
#include<algorithm>
const int maxn=1e6;
const double eps=1e-8;
#define INF 1e6;
#define ll long long;
using namespace std;
struct point{
	double x,y;
	  point(){}
    point(double _x,double _y):x(_x),y(_y){}
    point operator +(point p)//�����ӷ�
    {
        return point(x+p.x,y+p.y);
    }
    point operator -(point p)//��������
    {
        return point(x-p.x,y-p.y);
    }
    double operator *(point p)//�������
    {
        return x*p.y-y*p.x;
    }
    double operator ^(point p)//�������
    {
        return x*p.x+y*p.y;
    }
    point operator /(double p)//��������
    {
        return point(x/p,y/p);
    }
    point operator *(double p)//�����˷�
    {
        return point(x*p,y*p);
	}
}p[maxn]={};
/*��������*/
double max(double x,double y)
{
    return x>y?x:y;
}
double min(double x,double y)
{
    return x<y?x:y;
}
double cross(point a,point b,point c)//���
{
    return (b-a)*(c-a);
}
double dot(point a,point b,point c)//���
{
    return (b-a)^(c-a);
}
double len(point a)//��������
{
    return sqrt(a^a);
}
double dis(point a,point b)//�������
{
    return len(b-a);

}/*�����*/
void input(int n)
{
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
}

/*�жϵ��Ƿ����߶���*/
bool same_line(point q,point x1,point x2)
{
	const double esp=1e-8;
	if(abs((x2.y-q.y)*(x1.x-q.x)-(x1.y-q.y)*(x2.x-q.x))<esp){
		/*����ж��Ƿ���ֱ���ϣ�������ֱ��return true*/
		if(q.x<=x1.x&&q.x>=x2.x&&q.y<=x1.y&&q.y>=x2.y)
			return true;
		if(q.x>=x1.x&&q.x<=x2.x&&q.y>=x1.y&&q.y<=x2.y)
			return true;
		return false;
	}
	return false;
}

/*�жϵ��Ƿ��ڶ����area�ڲ���area�ڵĵ���ʱ������*/
bool in_the_area(point q,point area[],int n/*����ε������*/)
{
	int ans=0;
	double x;
	for(int i=1;i<=n;i++){
		point p1=area[i];
		point p2=area[i+1];
		if(same_line(q,p1,p2))return true;
		if(q.y<min(p1.y,p2.y))continue;
		if(q.y>=max(p1.y,p2.y))continue;
		x=(q.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
		if(x>q.x)ans++;
	}
	return(ans%2==1);
}

/*���*/
long long crossmulti(point p1,point p2,point p0)
{
	long long x1 = p1.x - p0.x;
    long long y1 = p1.y - p0.y;

    long long x2 = p2.x - p0.x;
    long long y2 = p2.y - p0.y;

    return (x1 * y2 - x2 * y1);
}

/*���������*/
double cross(point x1,point x2)
{
	return x1.x*x2.y-x1.y*x2.x;
}

/*��͹��������*/
double area(point s[],int n)
{
	double ret=0;
	s[n+1]=s[1];
	for(int i=1;i<=n;i++)
		ret+=cross(s[i],s[i+1]);
	return fabs(ret/2);
}
/*���������*/
double getd(point x1,point x2)
{
	return sqrt((x1.x-x2.x)*(x1.x-x2.x)+(x1.y-x2.y)*(x1.y-x2.y));
}

/*������Բ��*/
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

/*��СԲ����*/
void mincir(point &o,double &r, point p[],int n)
{
	o=p[1];
	r=0;
	for(int i=0;i<n;++i){
		if(getd(p[i],o)-r>eps){
			o=p[i];
			r=0;
			for(int j=0;j<i;j++){
				if(getd(p[j],o)-r>eps){
					o.x=(p[i].x+p[j].x)/2.0;
					o.y=(p[i].y+p[j].y)/2.0;
				r=getd(p[i],p[j])/2.0;
				for(int k=0;k<j;++k)
					if(getd(p[k],o)-r>eps){
						o=geto(p[i],p[j],p[k]);
						r=getd(p[i],o);
					}
				}
			}
		}
	}
}

/*͹������*/

//��������,������ͬ�򰴳�������
int cmp(point a,point b)
{
	double temp=cross(p[0],a,b);
	if(temp>0)
		return 1;
	else
		if(fabs(temp)<eps&&dis(p[0],a)<dis(p[0],b))
			return 1;
		else
			return 0;
}
void sortpoint(int n)
{
	int i,k;
	point start;
	start=p[0];
	k=0;
	for(i=1;i<n;i++)
	{
		if((start.y>p[i].y)||(fabs(start.y-p[i].y)<eps&&start.x>p[i].x))	
		{
			start=p[i];
			k=i;
		}
	}
	p[k]=p[0];
	p[0]=start;
	sort(p+1,p+n,cmp);
}
void be_weight(int val)//ȥ��
{
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
	if(n==1)
	{
		ch[0]=p[0];
		cnt=1;
	}
	else
		if(n==2)
		{
			ch[0]=p[0];
			ch[1]=p[1];
			ch[2]=p[2];
			cnt=2;
		}
		else
		{
			ch[0]=p[n-1];
			ch[1]=p[0];
			ch[2]=p[1];
			cnt=2;
			for(i=2;i<n;i++)
			{
				while(cross(ch[cnt-1],ch[cnt],p[i])<0)//�������Ϸ���
					cnt--;
				ch[++cnt]=p[i];
			}
		}
		return cnt;
}

/*��͹���ܳ�*/
double perimeter(int cnt,point ch[])
{
	double sum=0;
	for(int i=1;i<=cnt;i++)
		sum+=dis(ch[i-1],ch[i]);
	return sum;
}

/*��͹�����*/
double area(int cnt,point ch[])
{
	double sum=0;
	point p(0,0);
	for(int i=1;i<=cnt;i++)
		sum+=cross(p,ch[i-1],ch[i]);
	return fabs(sum/2.0);
}

/*����������*/
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

/*��ת����*/
/*��͹��ֱ��-����Ծ���*/
double diameter(int cnt,point p[])
{
	double maxn=0;
	int j=1;
	for(int i=1;i<cnt;i++)
	{
		while(fabs(cross(p[i-1],p[i],p[(j+1)%cnt]))>fabs(cross(p[i-1],p[i],p[j%cnt])))
			j++;
		maxn=max(maxn,dis(p[i-1],p[j%cnt]));
		maxn=max(maxn,dis(p[i],p[j%cnt]));
	}
	return maxn;
}

/*��������������*/
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

/*�������С���ƾ���*/

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
        double L=dis(q[i-1],q[i]);
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

/*���ܳ���С���ƾ���*/
double minrectangleC(int cnt,point q[])
{
	double C=INF;
    if(cnt<=2)
    {
        if(cnt==1)
           return 0.0;
        else
           return 2*dis(p[0],p[1]);
    }

    int j,k,r;
    double h,w;
    j=k=r=1;
    for(int i=1;i<=cnt;i++)
    {
        double L=dis(q[i-1],q[i]);
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
