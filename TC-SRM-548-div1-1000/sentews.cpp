#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,k,temp;
int f[55][2555]={},c[2555][2555]={};
const int codeforces=1000000007;
void getc()
{
	c[1][0]=1;c[1][1]=1;c[0][0]=1;
	for(int i=2;i<=2552;i++)
		c[i][0]=1;
	for(int i=2;i<=2522;i++)
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%codeforces;
}
int gets(int a){return a*(a-1)/2;}
class KingdomAndCities
{
	public:
		int howMany(int N, int M, int K)
		{
			n=N,m=M,k=K;
			getc();//计算组合
			if(n==2&&m==0&&k==1)return 1;
			if(n-1>k||n>n*(n-1)/2||n<=m)
				return 0;
			for(int i=1;i<=n;i++)//计算m=0的情况
				for(int j=i-1;j<=min(i*(i-1)/2,k);j++)
				{
					f[i][j]=c[gets(i)][j];
					for(int p=1;p<i;p++)
						for(int q=p-1;q<=min(gets(p),j);q++)
							f[i][j]=(f[i][j]-1LL*c[i-1][p-1]*f[p][q]%codeforces*c[gets(i-p)][j-q]%codeforces+codeforces)%codeforces;
				}
			if(m==0)
				return f[n][k];
			if(m==1)
			{
				temp=0;
				for(int i=1;i<=n-2;i++)
					for(int j=0;j<=k-2;j++)
						temp=(temp+1LL*i*(n-1-i)*c[n-2][i-1]%codeforces*f[i][j]%codeforces*f[n-1-i][k-2-j])%codeforces;
				temp=(temp+1LL*c[n-1][2]*f[n-1][k-2])%codeforces;
				return temp;
			}
			temp=0;
			temp=(temp+1LL*c[n-2][2]*c[n-2][2]%codeforces*f[n-2][k-4])%codeforces;
			for(int i=1;i<=n-4;i++)//3groups --1-- --2--
				for(int j=1;j+i<=n-3;j++)
					for(int ii=0;ii<=k-4;ii++)
						for(int jj=0;ii+jj<=k-4;jj++)
							temp=(temp+1LL*f[i][ii]*c[n-3][i-1]%codeforces*i%codeforces*(n-2)*2%codeforces*f[j][jj]%codeforces*f[n-2-i-j][k-4-ii-jj]%codeforces*c[n-3-i][j-1]%codeforces*j%codeforces*(n-2-i-j))%codeforces;
			for(int i=1;i<=n-3;i++)//2groups --1-- --2--
				for(int j=0;j<=k-4;j++)
					temp=(temp+1LL*f[i][j]*f[n-2-i][k-4-j]%codeforces*c[n-3][i-1]%codeforces*i*(n-2-i)%codeforces*(i*(n-2-i)+(c[i][2]+c[n-2-i][2])*2))%codeforces;
			n--,k--;
			for(int i=1;i<=n-2;i++)
				for(int j=0;j<=k-2;j++)
					temp=(temp+1LL*i*2*(n-1-i)*c[n-2][i-1]%codeforces*f[i][j]%codeforces*f[n-1-i][k-2-j])%codeforces;
			temp=(temp+1LL*(n-1)*(n-1)*f[n-1][k-2])%codeforces;
			return temp;
		}
};
