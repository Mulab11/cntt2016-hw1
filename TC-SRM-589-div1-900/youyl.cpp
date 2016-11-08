#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct FlippingBitsDiv1
{
	int tmp[1200],str[1200],cnt[(1<<17)];
	inline int cnnt(int x)
	{
		int ss=0;
		while (x!=0)
		{
			ss++;
			x-=(x&(-x));
		}
		return ss;
	}
	inline void init()// calculate the number of steps required to get a certain situation
	{
		for (int i=0;i<(1<<17);i++)
		{
			int res=0;
			for (int j=0;j<17;j++)
			{
				if((i&(1<<j))!=0)
				{
					res^=((1<<(j+1))-1);
				}
			}
			cnt[res]=cnnt(i);
		}
	}
	int dp[1200][2];
	inline int firstpart(int n,int m)// if m is less than or equal to 17
	{
		int ans=n;
		for (int mask=0;mask<(1<<m);mask++)
		{
			int co=0;
			for (int i=1;i<=m;i++)
			{
				if((mask&(1<<(i-1)))!=0)tmp[i]=1;
				else tmp[i]=0;
			}
			for (int i=m+1;i<=n;i++)
			{
				tmp[i]=tmp[(i-1)%m+1];
			}
			for (int i=1;i<=n;i++)
			{
				tmp[i]=tmp[i]^str[i];
			}
			for (int i=(n/m)*m+1;i<=n;i++)
			{
				co+=tmp[i];
			}
			for (int i=1;i<=n/m+1;i++)
			{
				dp[i][0]=n;
				dp[i][1]=n;
			}
			dp[n/m+1][0]=0;
			for (int i=n/m;i>=1;i--)
			{
				int c0=0,c1=0;
				for (int j=i*m-m+1;j<=i*m;j++)
				{
					if(tmp[j]==0)c0++;
					else c1++;
				}
				dp[i][0]=min(dp[i+1][0],dp[i+1][1]+1)+c1;
				dp[i][1]=min(dp[i+1][0]+1,dp[i+1][1])+c0;
			}
			ans=min(ans,co+min(dp[1][0],dp[1][1]));
		}return ans;
	}
	inline int solve2(int n,int m)// solve the situation if we can only flip one bit
	{
		int ans=0;
		for (int i=1;i<=m;i++)
		{
			int c0=0;
			int c1=0;
			for (int j=0;j<=n/m;j++)
			{
				if(j*m+i<=n)
				{
					if(tmp[j*m+i]==0)c0++;
					else c1++;
				}
			}
			ans+=min(c0,c1);
		}return ans;
	}
	inline int secondpart(int n,int m)// if n/m is less than or equal to 17
	{
		int t=n/m,ans=n;
		for (int mask=0;mask<(1<<t);mask++)
		{
			for (int i=1;i<=n;i++)
			{
				tmp[i]=str[i];
			}
			for (int i=0;i<t;i++)
			{
				if((mask&(1<<i))!=0)
				{
					for (int j=i*m+1;j<=i*m+m;j++)
					{
						tmp[j]=1-tmp[j];
					}
				}
			}
			ans=min(ans,cnt[mask]+solve2(n,m));
		}return ans;
	}
	inline int getmin(vector<string>s,int m)
	{
		init();
		string stp;
		stp="";
		int n=s.size();
		for (int i=0;i<n;i++)
		{
			stp+=s[i];// concatenate the strings
		}
		n=stp.length();
		for (int i=0;i<n;i++)
		{
			str[i+1]=stp[i]-'0';
		}
		if(m<=17)// into 2 different situation
		{
			return firstpart(n,m);
		}
		else
		{
			return secondpart(n,m);
		}
	}
};