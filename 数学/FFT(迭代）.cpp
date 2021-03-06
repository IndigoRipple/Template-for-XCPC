

#include "stdafx.h"
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const double PI=acos(-1);
const int maxn=1e6+10;
struct complex{
	double R,I;
	complex(){
		R=0.0,I=0.0;
	}
	complex(double r, double i) :R(r), I(i) {}
	};

	complex f[maxn],g[maxn];
	complex operator+(complex a, complex b) { return complex(a.R + b.R, a.I + b.I); }
    complex operator-(complex a, complex b) { return complex(a.R - b.R, a.I - b.I); }
    complex operator*(complex a, complex b) { return complex(a.R * b.R - a.I * b.I, a.R * b.I + a.I * b.R); }
	int rev[maxn],len,lim=1;
	void DFT(complex* a,int opt){
		for(int i=0;i<lim;i++)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(int dep=1;dep<=log(lim)/log(2);dep++){
			int n=1<<dep;
			complex wn=complex(cos(2.0*PI/n),opt*sin(2.0*PI/n));
			for(int k=0;k<lim;k+=n){
				complex w=complex(1,0);
				for(int j=0;j<n/2;j++){
					complex t=w*a[k+j+n/2];
					complex u=a[k+j];
					a[k+j]=u+t;
					a[k+j+n/2]=u-t;
					w=w*wn;
				}
			}
		}
	}
	void FFT(int n,int m)//输出多项式各系数
	{
		for(int i=0;i<=n;i++)
			cin>>f[i].R;
		for(int i=0;i<m;i++)
			cin>>g[i].R;
		while(lim<=n+m)lim<<=1,len++;
		for(int i=1;i<lim;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));//位逆序置换
		}
		DFT(f,1),DFT(g,1);
		for(int i=0;i<=lim;i++){
			cout<<(int)(f[i].R/(double)lim+0.5)<<" ";
		}
		return;
	}
