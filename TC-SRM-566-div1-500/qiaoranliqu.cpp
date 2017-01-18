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

#define N 355
#define M 200005
#define seed 23333
#define Mo 1000000007

using namespace std;
int i,j,m,n,p,k,A[N],B[N],Ans[N];
void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; }
void cheng()
{
	 int C[N]={0},i,j;
	 for (i=0;i<n;++i)
	  for (j=0;j<n;++j)
	    jia(C[(i+j)%n],1ll*Ans[i]*A[j]%Mo);
	 memcpy(Ans,C,sizeof(C));
}
void Cheng()
{
	 int C[N]={0},i,j;
	 for (i=0;i<n;++i)
	  for (j=0;j<n;++j)
	    jia(C[(i+j)%n],1ll*A[i]*A[j]%Mo);
	 memcpy(A,C,sizeof(C));
}
void Count(long long y) //快速幂计算矩乘 
{
	  for (;y;y>>=1)
	  {
	  	  if (y&1) cheng();
	  	  Cheng();
	  }
}
void Baoli(int x)
{
	   for (i=1;i<=x;++i)
	   {
					memset(B,0,sizeof(B));
					for (k=0;k<n;++k)
					for (k=0;k<n;++k)
					{
					  jia(B[(k+i)%n],Ans[k]);
					  if (i%n!=(n-i)%n)
					  jia(B[(n-i+k)%n],Ans[k]);
				    }
					memcpy(Ans,B,sizeof(B));
	   }
}
class PenguinEmperor{
	public:
		int countJourneys(int nc,long long m)
		{
				n=nc;
				A[0]=1;
				for (i=1;i<n;++i) //本题的动态规划方程为f[i][j]->f[i+1][(j+i+1)%n],f[i+1][(j-i-1)%n],那么i在%n域下是一个循环,直接爆即可 
				{
					memset(B,0,sizeof(B));
					for (k=0;k<n;++k)
					{
					  jia(B[(k+i)%n],A[k]);
					  if (i%n!=(n-i)%n)
					  jia(B[(n-i+k)%n],A[k]);
				    }
					memcpy(A,B,sizeof(B));
				}
				Ans[0]=1;
				Count(m/n); Baoli(m%n); //将m分为m/n个大循环和m%n个小循环 
				return Ans[0]; 
		}
}ETT;

int main()
{
	 printf("%d\n",ETT.countJourneys(4,3));
}
