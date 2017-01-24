#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
int n,zero,dp[3000],res,ans;
vector<pair<int,int> >useful;
set<int>mp;
inline int fab(int x)
{
	if(x>0)return x;
	return -x;
}
inline int calc(int x)
{
	return fab(2*x-n*n);
}
struct KingdomAndDice
{
	inline double newFairness(vector<int>firstdie,vector<int>seconddie,int x)
	{
		sort(seconddie.begin(),seconddie.end());
		n=firstdie.size();
		for (int i=1;i<=n;i++)
		{
			mp.insert(firstdie[i-1]);
			if(firstdie[i-1]==0)
			{
				zero++;
			}
		}
		seconddie.push_back(x+1);
		for (int i=1;i<=n;i++)// get the useable numbers
		{
			int lb=seconddie[i-1],rb=seconddie[i];
			int flg=0;
			for (int j=lb+1;j<rb;j++)
			{
				if(mp.find(j)==mp.end())
				{
					if(flg==zero)break;
					useful.push_back(make_pair(j,i));
					flg++;
				}
			}
		}
		dp[0]=0;
		for (int i=1;i<=n*n;i++)
		{
			dp[i]=zero+1;
		}
		for (int i=0;i<useful.size();i++)// get the min number of 0 to get a sum of i
		{
			for (int j=n*n;j>=1;j--)
			{
				if(useful[i].second<=j)dp[j]=min(dp[j],dp[j-useful[i].second]+1);
			}
		}
		res=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if(firstdie[i-1]>seconddie[j-1])res++;
			}
		}
		ans=0;
		for (int i=1;i<=n*n;i++)// get the answer
		{
			if(zero<dp[i])continue;
			if(calc(ans+res)>calc(i+res))ans=i;
		}
		return ((ans+res)*1.0)/(n*n);
	}
};
