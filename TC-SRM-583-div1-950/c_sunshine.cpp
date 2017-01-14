#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class RandomPaintingOnABoard
{
	public:
	int n,m;
	int P[25][25],SP;
	int w[25],f[1400],g[1400];
	LL cnt[1400];
	double expectedSteps(vector<string> prob)
	{
		//ans = \sum[R is a subset of [0,n-1],C is a subset of [0,m-1] and |R|+|C| \leq n+m]
		//					(-1)^(n+m-|R|-|C|) * 1/(1-\sum (i,j) \in R*C p_{i,j})
		//min(n,m) must be no more than 12
		n=prob.size();
		m=prob[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				SP+=prob[i][j]-'0';
				if(n<m)P[j][i]=prob[i][j]-'0';
				else P[i][j]=prob[i][j]-'0';
			}
		if(n<m)swap(n,m);
		for(int s=0;s<1<<m;s++)//enumerate each case of columns
		{
			for(int i=0;i<n;i++)//add the possibilities of all availible blocks in each row
				for(int j=w[i]=0;j<m;j++)
					if(s>>j&1)w[i]+=P[i][j];
			//We cannot enumerate all cases of rows, but we can use knapsack to coalescence coefficient
			memset(f,0,(SP+1)<<2);
			f[0]=1;
			for(int i=0;i<n;i++)
			{
				for(int k=0;k<=SP;k++)
				{
					if(k+w[i]<=SP)
						g[k+w[i]]-=f[k];
					g[k]+=f[k];
				}
				memcpy(f,g,(SP+1)<<2);
				memset(g,0,(SP+1)<<2);
			}
			int c1=0;
			for(int j=0;j<m;j++)
				c1+=(s>>j&1);
			c1&=1;
			if((n+m)&1)c1^=1;
			//c1 = (n+m-|R|-|C|) (mod 2)
			if(c1&1)
				for(int k=0;k<=SP;k++)
					cnt[k]-=f[k];
			else
				for(int k=0;k<=SP;k++)
					cnt[k]+=f[k];
		}
		//Add all items to the answer
		double ans=0;
		for(int k=0;k<SP;k++)
		{
			double pr=(double)k/SP,ex;
			ex=1.0/(1.0-pr);
			ans-=cnt[k]*ex;
		}
		return ans;
	}
};

