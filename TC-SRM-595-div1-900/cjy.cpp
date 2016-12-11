#include<bits/stdc++.h>
using namespace std;
struct P
{
	int x,y;
	P operator -(const P &a)const{return P{x-a.x,y-a.y};}
	int operator *(const P &a)const{return x*a.y-y*a.x;}
}a[55],b;
int i,j,k,n,t;
double s,r;
int C(int a,int b,int c){return a<=b&&b<=c||c<=b&&b<=a;}
class Constellation
{
	public:
		double expectation(vector<int>x,vector<int>y,vector<int>p)
		{
			n=x.size();
			for(;i<n;i++)a[i]=P{x[i],y[i]};
			for(i=0;i<n;i++)for(j=0;j<n;j++)if(i!=j)//考虑每组原点三角形的贡献			
			{
				r=1;b=a[j]-a[i];
				for(k=0;k<n;k++)if(i!=k&&j!=k)if(t=b*(a[k]-a[i]),t>0||!t&&C(x[i],x[k],x[j])&&C(y[i],y[k],y[j]))r*=1-.001*p[k];
				s+=r*(a[j]*a[i])*.000001*p[i]*p[j];
			}
			return s/2;
		}
};
