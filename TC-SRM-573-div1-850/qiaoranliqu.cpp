#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 1000000007

using namespace std;

void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; } 
int i,j,m,n,p,k,a[N],fac[N],inv[N];

int C(int x,int y)
{
	 return 1ll*fac[x]*inv[y]%Mo*inv[x-y]%Mo;
}
int calc1() //此时问题转化成每个点会操作m次+1,-1,要求到达同一个点,由于坐标较小,可以直接枚举最后相遇的位置,然后每个点要走的+1,-1数量确定,用组合数计算. 
{
	   int sum=1,ans=0,goal;
	   for (goal=-300000;goal<=300000;++goal)
	   {
	   	sum=1;
	     for (i=0;i<n;++i)
	    {
	   	    int AA=abs(a[i]-goal);
	   	    if (AA>m||(m-AA)&1) { sum=0; break; }
			int rest=AA+(m-AA)/2;
			sum=1ll*sum*C(m,rest)%Mo; 
	    }
	   jia(ans,sum);
       }
	   return ans;
}

int power(int x,int y)
{
	   int sum=1;
	   for (;y;y>>=1)
	   {
	   	   if (y&1) sum=1ll*sum*x%Mo;
	   	   x=1ll*x*x%Mo;
	   }
	   return sum;
}

class WolfPack{
	  public:
	  	int calc(vector<int> x,vector<int> y,int mc)
	  	{
	  		   m=mc; n=x.size();
	  		   fac[0]=1;for (i=1;i<N;++i) fac[i]=1ll*fac[i-1]*i%Mo;
	  		   inv[N-1]=power(fac[N-1],Mo-2);
	  		   for (i=N-1;i;--i) inv[i-1]=1ll*inv[i]*i%Mo;
	  		   //不妨将本题中的坐标转化为(x+y,x-y),此时x,y就相互独立了,可以分别单独计算 
	  		   for (i=0;i<n;++i) a[i]=x[i]+y[i];
			   int ans1=calc1();
			   for (i=0;i<n;++i) a[i]=x[i]-y[i];
			   int ans2=calc1();
			   return 1ll*ans1*ans2%Mo;
		}
};

