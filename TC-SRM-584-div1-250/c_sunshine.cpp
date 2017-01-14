#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class Egalitarianism
{
	public:
	int n;
	int g[55][55];
	int maxDifference(vector<string> isFriend,int d)
	{
		//It is apparent that the answer is max{distance(i,j)*d} 
		n=isFriend.size();
		memset(g,31,sizeof(g));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(isFriend[i][j]=='Y')g[i][j]=1;
		//Use Floyd to solve the All Pairs Shortest Path 
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
		int ans=0;
		//Get the maximum distance
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
			{
				if(g[i][j]>100)return -1;
				else
				{
					ans=max(ans,g[i][j]*d);
				}
			}
		return ans;
	}
};

