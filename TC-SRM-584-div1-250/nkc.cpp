#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct Egalitarianism
{
	int f[N][N];
	int maxDifference(vector <string> isFriend, int d)
	{
		int n=isFriend.size();
		memset(f,0x3f,sizeof(f));
		int i,j,k;
		for(i=0;i<n;i++)
		{
			f[i][i]=0;
			for(j=0;j<n;j++)
			if(isFriend[i][j]=='Y')
			f[i][j]=1;
		}
		for(k=0;k<n;k++)
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
		int ans=0;
		for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
		ans=max(ans,f[i][j]);
		if(ans==0x3f3f3f3f) return -1;
		return ans*d;
	}
};