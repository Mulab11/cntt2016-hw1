#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class Stamp
{
	public:
	int n;
	vector<int> s;
	int f[55][3];
	
	int can(int l,int r,int c)//If we can paint [l,r] with only color c.
	{
		for(int i=l;i<r;i++)
			if(s[i]!=3&&s[i]!=c)
				return 0;
		return 1;
	}
	
	int dp(int L)
	{
		//f[i][j] : cells in [1,i] have been colored, and the last color is j.
		memset(f,31,sizeof(f));
		for(int k=0;k<3;k++)
			if(can(0,L,k))f[L][k]=1;
		for(int i=L+1;i<=n;i++)
			for(int j=0;j<3;j++)
				if(can(i-L,i,j))
				{
					//The last colored cell is before position i-L+1.
					f[i][j]=min(min(f[i-L][0],f[i-L][1]),f[i-L][2])+1;
					for(int p=i-L+1;p<i;p++)//Otherwise we should use the same color.
						f[i][j]=min(f[i][j],f[p][j]+1);
				}
		return min(min(f[n][0],f[n][1]),min(f[n][2],1000));
	}
	
	int getMinimumCost(string desiredColor, int stampCost, int pushCost)
	{
		n=desiredColor.size();
		for(int i=0;i<n;i++)
		{
			char t=desiredColor[i];
			if(t=='R')s.push_back(0);
			if(t=='G')s.push_back(1);
			if(t=='B')s.push_back(2);
			if(t=='*')s.push_back(3);
		}
		int ans=1<<30;
		//Pick L.
		for(int i=1;i<=n;i++)
			ans=min(ans,dp(i)*pushCost+i*stampCost);
		return ans; 
	}
};

