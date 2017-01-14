#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TPS
{
	public:
	int n;
	vector<int> g[55];
	int f[55][2];
	
	void dp(int x,int fa)
	{
		f[x][0]=f[x][1]=0;
		int b=0;
		for(int i=0,y;i<g[x].size();i++)
			if((y=g[x][i])!=fa)
			{
				dp(y,x);
				f[x][0]+=f[y][1];
				f[x][1]+=f[y][1];
				b=max(b,f[y][1]-f[y][0]);
			}
		//If vertex x has k sons, at least k-1 of them should containa beacon in their subtree.
		f[x][0]-=b;f[x][1]-=b;//We find the best son whose subtree can be empty.
		if(f[x][1]==0)f[x][1]++;
	}
	
	int minimalBeacons(vector<string> linked)
	{
		n=linked.size();
		if(n==1)return 0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(linked[i][j]=='Y')g[i].push_back(j);
		int res=n;
		//f[i][j]: the minimum number of the beacons in subtree i.
		//If j=1 there must be at least one beacon in the subtree.
		for(int i=0;i<n;i++)
		{
			dp(i,-1);
			res=min(res,1+f[i][0]);
		}
		return res;
	}
};

