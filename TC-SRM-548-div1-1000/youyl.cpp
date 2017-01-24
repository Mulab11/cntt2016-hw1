#include<cstdio>
using namespace std;
const long long mod=1000000007;
struct KingdomAndCities
{
	long long dp[60][60];
	long long C[2510][2510],ans;
	inline void init()
	{
		C[0][0]=1;
		for (int i=1;i<=2500;i++)// get C(i,j)
		{
			C[i][0]=1;
			for (int j=1;j<=i;j++)
			{
				C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
			}
		}
		for (int i=1;i<=50;i++)// get the number of ways to make a connected graph with i points and j edges
		{
			for (int j=0;j<=50;j++)
			{
				dp[i][j]=C[C[i][2]][j];
				for (int ia=1;ia<i;ia++)
				{
					for (int ja=0;ja<=j;ja++)
					{
						dp[i][j]-=((C[i-1][ia-1]*dp[ia][ja]%mod)*C[C[i-ia][2]][j-ja]%mod);
						dp[i][j]+=mod;
						dp[i][j]%=mod;
					}
				}
			}
		}
	}
	inline long long calc1(long long x,long long y)// numbers of ways to connect 2 restricted point to 2 component
	{
		return ((x*y*x*y)%mod+(C[x][2]*x*y*2)%mod+(C[y][2]*x*y*2)%mod)%mod;
	}
	inline long long calc2(long long x,long long y,long long z)// numbers of ways to connect 2 restricted point to 3 component
	{
		return (2*(x+y+z)*x*y*z)%mod;
	}
	inline long long calc3(long long x,long long y)// numbers of ways to connect 2 connected restricted point to 2 component
	{
		return (2*x*y)%mod;
	}
	inline int howMany(int n, int m, int k)
	{
		init();
		if(n-1>k)return 0;
		if(k>C[n][2])return 0;
		if(m>n)return 0;
		if(n<=2)
		{
			if(m==0)return 1;
			return 0;
		}
		ans=0;
		if(m==0)
		{
			return dp[n][k];
		}
		else if(m==1)
		{
			if(k>=2)
			{
				ans+=dp[n-1][k-2]*C[n-1][2]%mod;// 2 component
				ans%=mod;
				for (int i=1;i<n-1;i++)// 3 component
				{
					for (int j=0;j<=k-2;j++)
					{
						ans+=((dp[i][j]*i%mod)*(dp[n-i-1][k-j-2]*(n-i-1)%mod)%mod)*C[n-2][i-1]%mod;
						ans%=mod;
					}
				}
			}
			return ans;
		}
		else
		{
			if(k>=3)// the 2 restricted points are connected
			{
				ans+=(dp[n-2][k-3]*(n-2)%mod)*(n-2)%mod;// 3 component
				ans%=mod;
				for (int i=1;i<n-2;i++)// 4 component
				{
					for (int j=0;j<=k-3;j++)
					{
						ans+=((dp[i][j]*dp[n-2-i][k-3-j]%mod)*C[n-3][i-1]%mod)*calc3(i,n-2-i)%mod;
						ans%=mod;
					}
				}
			}
			if(k>=4)// the 2 restricted points are unconnected
			{
				ans+=(dp[n-2][k-4]*C[n-2][2]%mod)*C[n-2][2]%mod;// 3 component
				ans%=mod;
				for (int i=1;i<n-2;i++)// 4 component
				{
					for (int j=0;j<=k-4;j++)
					{
						ans+=(((dp[i][j]*dp[n-2-i][k-4-j]%mod)*C[n-3][i-1]%mod)*calc1(i,n-2-i)%mod);
						ans%=mod;
					}
				}
				for (int ia=1;ia<n-2;ia++)// 5 component
				{
					for (int ja=0;ja<=k-4;ja++)
					{
						for (int ib=1;ib<n-2-ia;ib++)
						{
							for (int jb=0;jb<=k-4-ja;jb++)
							{
								ans+=((((dp[ia][ja]*dp[ib][jb]%mod)*dp[n-2-ia-ib][k-4-ja-jb]%mod)*C[n-3][ia-1]%mod)*C[n-3-ia][ib-1]%mod)*calc2(ia,ib,n-2-ia-ib)%mod;
								ans%=mod;
							}
						}
					}
				}
			}
			return ans;
		}
	}
};