#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class GooseTattarrattatDiv1
{
	public:
	int f[28],c[28],ans;
	
	int getf(int x)
	{return f[x]?f[x]=getf(f[x]):x;}
	
	void merge(int x,int y)
	{
		x=getf(x);
		y=getf(y);
		if(x!=y)
		{
			c[x]=max(c[x],c[y]);
			f[y]=x;
		}
	}	
	
	int getmin(string S)
	{
		//Because some pairs must be equal finally and we can only change one letter into another,
		//there are some groups of letters that must be equal at last
		int n=S.size(),m=26;
		for(int i=0;i<n;i++)
			c[S[i]-96]++;
		for(int i=0;i<n;i++)
			merge(S[i]-96,S[n-i-1]-96);
		//We use Disjoint-set data structure to determine the groups and in each group,
		//we can keep the letter that occurs most frequently and change any other letter into it.
		ans=n;
		for(int i=1;i<=m;i++)
			if(f[i]==0)
				ans-=c[i];
		return ans;
	}
};

