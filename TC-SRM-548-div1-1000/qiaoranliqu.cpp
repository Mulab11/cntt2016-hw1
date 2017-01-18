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

#define N 55
#define M 200005
#define seed 23333
#define Mo 1000000007

using namespace std;
int i,j,m,n,p,k,C[N*N][N*N],B[N][N],K,l;
void jia(int &x,int y)
{
		x+=y; if (x>=Mo) x-=Mo;
}
void jian(int &x,int y)
{
		x-=y; if (x<0) x+=Mo;
}
int gao(int x)
{
		return 1ll*x*(x-1)/2; 
}
int sqr(int x)
{
		 return 1ll*x*x%Mo; 
}
class KingdomAndCities{
	public:
		int howMany(int nc, int mc, int k)
		{
				n=nc; m=mc; ::k=k;
				for (i=0;i<N*N;++i)
				{
					 C[i][0]=1;
					 for (j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mo;
				}
				for (i=1;i<=n;++i)  //预处理i个点j条边的无向简单连通图个数 
	  				for (j=0;j<=min(i*(i-1)/2,k);++j)
	  			{
	  				B[i][j]=C[i*(i-1)/2][j];
	  				for (K=1;K<i;++K)
	  		  			for (l=0;l<=j;++l)
	  		     		jian(B[i][j],1ll*B[K][l]*C[(i-K)*(i-K-1)/2][j-l]%Mo*C[i-1][K-1]%Mo);
	  			}
	  			if (m==0) return B[n][k];
	  			if (m==1)
	  			{
	  				  int ans=1ll*B[n-1][k-2]*gao(n-1)%Mo; //其他点构成一个联通块 
					  for (j=1;j<=n-2;++j) //其他点构成两个联通块 
					  	for (K=0;K<=k-2;++K)
					  jia(ans,1ll*B[j][K]*B[n-1-j][k-2-K]%Mo*C[n-2][j-1]%Mo*j*(n-1-j)%Mo);
					  return ans;
	  			}
	  			int ans=0;
	  			//处理两个点连在一起的情况 
	  			if (n>=2&&k>=3)	
	  			ans=1ll*B[n-2][k-3]*(n-2)*(n-2)%Mo;
	  			for (j=1;j<=n-3;++j)
	  				for (K=0;K<=k-3;++K)
	  					jia(ans,1ll*B[j][K]*B[n-2-j][k-3-K]%Mo*C[n-3][j-1]%Mo*j*(n-2-j)*2%Mo);
	  			//处理分开的情况 
	  			if (n>=2&&k>=4) //1个联通块 
				jia(ans,1ll*B[n-2][k-4]*sqr(gao(n-2))%Mo);
				for (j=1;j<=n-3;++j) //2个联通块 
					for (K=0;K<=k-4;++K)
					{
							int sum=1ll*B[j][K]*B[n-2-j][k-4-K]%Mo*C[n-3][j-1]%Mo;
							jia(ans,1ll*sum*sqr(gao(n-2))%Mo);
							jian(ans,1ll*sum*sqr(gao(j)+gao(n-2-j))%Mo);
					}
				//3个联通块 
				for (i=1;i<=n-3;++i)
					for (K=0;K<=k-4;++K)
						for (j=1;i+j<=n-3;++j)
							for (l=0;l+K<=k-4;++l)
						{
								int p=n-2-i-j;
								jia(ans,1ll*B[i][K]*B[j][l]%Mo*B[p][k-K-l-4]%Mo*
										C[n-2][i]%Mo*C[n-2-i][j]%Mo*
										i*sqr(j)*p%Mo); 
						}
				return ans;
	  }
}FFT;

int main()
{
	  cout<<FFT.howMany(23,2,29)<<endl;	 
}
