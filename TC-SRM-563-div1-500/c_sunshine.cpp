#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class SpellCards
{
	public:
	int n,ans;
	int f[55][55],lv[55],dm[55];
	
	int dp(int x,int k)
	{
		//f[x][k]: We have thought about first x cards, and we still need to remove k cards.
		int &res=f[x][k];
		if(res!=-1)return res;
		if(n-x==k)return res=0;
		res=dp(x+1,max(0,k-1));//Remove the current card.
		if(k+lv[x]<=n-x)//We have enough cards to remove.
			res=max(res,dm[x]+dp(x+1,max(0,k+lv[x]-1)));//Use the current card and the number of cards to remove increases by level[x]-1.
		return res;
	}
	
	int maxDamage(vector<int> level,vector<int> damage)
	{
		n=level.size();ans=0;
		//We can pick the break point and make the cycle into a sequence.
		//Then use DP to solve it.
		for(int p=0;p<n;p++)//pick the break point.
		{
			for(int i=0;i<n;i++)
			{
				lv[i]=level[(p+i)%n];
				dm[i]=damage[(p+i)%n];
			}
			memset(f,-1,sizeof(f));
			ans=max(ans,dp(0,0));
		}
		return ans;
	}
};

