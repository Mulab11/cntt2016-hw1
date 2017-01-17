#include<bits/stdc++.h>
#define c(x,y) (x>=0&&y>=0&&x<n&&y<m)
using namespace std;
long long s;
class HyperKnight
{
	public:
		long long countCells(int a,int b,int n,int m,int k)
		{
			int x[6]={0,a,b,n,n-a,n-b},y[6]={0,a,b,m,m-a,m-b},i=0,j,d,e,t;
			for(sort(x,x+6),sort(y,y+6);i<5;i++)for(j=0;j<5;s+=1ll*!t*(x[i+1]-x[i])*(y[j+1]-y[j]),j++)for(t=k,d=-a;d<=a;d+=a+a)for(e=-b;e<=b;e+=b+b)t-=c(x[i]+d,y[j]+e)+c(x[i]+e,y[j]+d); 
			return s;
		}
};
