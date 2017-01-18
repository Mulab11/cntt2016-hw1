#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const double eps=1e-13;
const double pi=acos(-1.0);
int i,j,m,n,p,k,tot;
double x[N],y[N],r[N],rr[N];
struct Seg{
	double x,y;
}A[N];
double sqr(double v)
{
		return v*v;
}
void Push(double x,double y) //加入一条覆盖的弧 
{
		if (x<-pi) A[++tot]=(Seg){pi+(x+pi),pi},x=-pi;
		if (y>pi)  A[++tot]=(Seg){-pi,y-2*pi},y=pi;
		A[++tot]=(Seg){x,y};
}
inline bool cmp(Seg a,Seg b)
{
	 return a.x<b.x;
}
double check(double v)
{
		int i;
		tot=0;
		for (i=0;i<n;++i) rr[i]=r[i]+v; rr[0]=r[0];
		for (i=1;i<n;++i)
		{
				double dis=x[i]*x[i]+y[i]*y[i];
				if (dis>sqr(rr[0]+rr[i])) continue;
				if (dis>=sqr(rr[0])+sqr(rr[i])) //如果不会经过圆的话,直接算中间的cos 
				{
					double str=atan2(y[i],x[i]);
					double p=(dis+sqr(rr[0])-sqr(rr[i]))/(2.*rr[0]*sqrt(dis)); 
					p=acos(p);
					Push(str-p,str+p);
				}
				else //否则需要先走到切点，在计算剩余部分的角度 
				{
					double str=atan2(y[i],x[i]);
					double bt=acos(rr[0]/sqrt(dis));
					double gm=(rr[i]-sqrt(dis-rr[0]*rr[0]))/rr[0];
					if (bt+gm>=pi) return 0;
					Push(str-bt-gm,str+bt+gm);
				}
		}
				if (!tot) return 1;
				sort(A+1,A+tot+1,cmp);
				if (abs(A[1].x-(-pi))>eps) return 1; 
				for (i=2;i<=tot;++i) //判断是否完全覆盖 
				{
					  if (A[i].x-A[1].y>eps) return 1;
					  A[1].y=max(A[1].y,A[i].y);
				}
				if (abs(pi-A[1].y)>eps) return 1;
				return 0; 
}
class CircusTents
{
	public:
		double findMaximumDistance(vector <int> x, vector <int> y, vector <int> rad)
		{
			 n=(int)x.size();
			 for (i=1;i<n;++i) x[i]-=x[0],y[i]-=y[0];
			 for (i=0;i<n;++i) ::x[i]=x[i],::y[i]=y[i],::r[i]=rad[i];
			 double l=0.,r=1e5,mid=0;
			 for (i=1;i<=200;++i)
			 { 
			 		mid=(l+r)/2.; //二分最远的最近距离 
 			 		if (check(mid)) l=mid; else r=mid;
			 }
			 return l;
		}
};
