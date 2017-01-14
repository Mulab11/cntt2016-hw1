#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int M=1000000007;

inline void up(int &x,const int &y)
{x=(x+y)%M;}

class LISNumber
{
	public:
	int n;
	int f[1500][2],g[1500][2];
	int card[55],sum[55];
	
	int fpw(int a,int b)
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	int count(vector<int> cardsnum,int K)
	{
		n=cardsnum.size();
		for(int i=1;i<=n;i++)
			card[i]=cardsnum[i-1],sum[i]=sum[i-1]+card[i];
		f[0][1]=1;
		//f[k][t]:
		//there are k continuous pairs (a,b) satisfying a>=b
		//t = 1 means that the last element of the sequence is i
		//t = 0 means that the last element of the sequence is not i
		for(int i=1;i<=n;i++)
		{
			for(int j=1+(i==1);j<=card[i];j++)
			{
				for(int k=0;k<=sum[i];k++)
				{
					//We use x and y to represent any number less than i, x>y
					int t=sum[i-1]+j;
					if(k-(j-1)>0)//insert i between (x,y)
						up(g[k][0],(LL)(k-(j-1))*f[k][0]%M);
					if(t-1-(k-(j-1))>0)//insert i into any other position except the end of the sequence
						up(g[k+1][0],(LL)(t-1-(k-(j-1)))*f[k][0]%M);
					up(g[k][1],f[k][0]);//add i at the end of the sequence
					if(k-(j-2)>0)//insert i between (x,y)
						up(g[k][1],(LL)(k-(j-2))*f[k][1]%M);
					if(t-(k-(j-2))>0)//insert i into any other position
						up(g[k+1][1],(LL)(t-(k-(j-2)))*f[k][1]%M);
				}
				for(int k=0;k<=sum[i];k++)
				{
					f[k][0]=g[k][0],g[k][0]=0;
					f[k][1]=g[k][1],g[k][1]=0;
				}
			}
			for(int k=1;k<=sum[i];k++)
				f[k][0]=(f[k][0]+f[k][1])%M,f[k][1]=0;
		}
		int ans=f[K-1][0]+f[K-1][1];//notice: if there is only one card, f[K-1][1] won't be 0.
		//Because we think about only one card each step, a situation may be counted more than one time.
		//In fact because cards can be added in any order so the answer should be divided by \prod cardsnum_i!
		for(int i=1;i<=n;i++)
			for(int j=1;j<=card[i];j++)
				ans=(LL)ans*fpw(j,M-2)%M;
		return ans;
	}
};

