#include<bits/stdc++.h>
const long long mod=1234567891;
const int N=2333,M=122;
int m;

class TheBrickTowerHardDivOne
{
	public:


		struct gungnir
		{
			long long a[M][M];

			gungnir operator * (const gungnir &b)
			{
				gungnir c;
				for(int i=1;i<=m;i++)
				{
					for(int j=1;j<=m;j++)
					{
						c.a[i][j]=0;
						for(int k=1;k<=m;k++)
						{
							(c.a[i][j]+=a[i][k]*b.a[k][j])%=mod;
						}
					}
				}
				return c;
			}
		}dp,ini;

		int a[N],c[N];
		long long b[N],e[N];

		int shanquan(int a[])
		{
			int b[9],ans=0,j=1,k=1;
			memset(b,0,sizeof(b));
			b[a[1]]=1;
			for(int i=2;i<5;i++)
			{
				k=std::max(k,a[i]);
				ans=ans*10+(b[a[i]]?b[a[i]]:b[a[i]]=++j);
			}
			return ans;
		}

		long long yamaizumi(int a[],int n,int c)
		{
			int j=0;
			for(int i=1;i<=n;i++)
			{
				if(a[i]>j+1)return 0;
				j=std::max(j,a[i]);
			}
			long long ans=1;
			for(int i=0;i<j;i++)
			{
				(ans*=(c-i))%=mod;
			}
			return ans;
		}

		gungnir moko(gungnir a,long long b)
		{
			gungnir ans;
			memset(ans.a,0,sizeof(ans.a));
			for(int i=1;i<=m;i++)
			{
				ans.a[i][i]=1;
			}
			for(;b;b>>=1)
			{
				if(b&1)ans=ans*a;
				a=a*a;
			}
			return ans;
		}

		long long moko(long long a,long long b)
		{
			long long ans=1;
			for(;b;b>>=1)
			{
				if(b&1)(ans*=a)%=mod;
				(a*=a)%=mod;
			}
			return ans;
		}

		int find(int C, int K, long long H)
		{
			for(int i=0;i<9;i++)
			{
				a[i]=1;
			}
			for(;a[0]<2;)
			{
				int j=shanquan(a);
				b[j]=std::max(b[j],yamaizumi(a,4,C));
				int i;
				for(i=4;a[i]==i;i--)
				{
					a[i]=1;
				}
				a[i]++;
			}
			int n=0;
			memset(c,0,sizeof(c));
			for(int i=1;i<=1000;i++)if(b[i])
			{
				c[i]=++n;
				e[n]=b[i];
			}
			m=n*(K+1)+1;
			for(int i=0;i<9;i++)
			{
				a[i]=1;
			}
			memset(ini.a,0,sizeof(ini.a));
			memset(dp.a,0,sizeof(dp.a));
			for(;a[0]<2;)
			{
				int j=c[shanquan(a)],k=c[shanquan(a+4)],d[9];
				if(j && k)
				{
					long long o=yamaizumi(a,8,C)*moko(e[j],mod-2)%mod;
					int y=j+((a[1]==a[2])+(a[1]==a[3])+(a[4]==a[2])+(a[4]==a[3]))*n;
					if(y<m)ini.a[1][y]=e[j];
					int sum=(a[5]==a[6])+(a[5]==a[7])+(a[8]==a[6])+(a[8]==a[7]);
					for(int i=1;i<5;i++)
					{
						sum+=(a[i]==a[i+4]);
					}
					for(int z=0;z<=K-sum;z++)
					{
						(dp.a[j+z*n][k+(z+sum)*n]+=o)%=mod;
					}
				}
				int i;
				for(i=8;a[i]==i;i--)
				{
					a[i]=1;
				}
				a[i]++;
			}
			for(int i=1;i<=m;i++)
			{
				dp.a[i][m]=1;
			}
			return (ini*moko(dp,H)).a[1][m];
		}
};