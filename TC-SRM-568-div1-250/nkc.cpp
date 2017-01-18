#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct BallsSeparating
{
	int f[N][8],tot[N];
	int minOperations(vector <int> red, vector <int> green, vector <int> blue)
	{
		int n=red.size();
		int i,j;
		memset(f,0x3f,sizeof(f));
		for(i=0;i<n;i++)
		tot[i]=red[i]+green[i]+blue[i];//计算总数 
		f[0][1]=tot[0]-red[0];
		f[0][2]=tot[0]-green[0];
		f[0][4]=tot[0]-blue[0];//初始化DP边界 
		for(i=1;i<n;i++)
		for(j=1;j<8;j++)//开始状压DP 
		{
			if(j&1) f[i][j]=min(f[i][j],min(f[i-1][j],f[i-1][j-1])+tot[i]-red[i]);
			if(j&2) f[i][j]=min(f[i][j],min(f[i-1][j],f[i-1][j-2])+tot[i]-green[i]);
			if(j&4) f[i][j]=min(f[i][j],min(f[i-1][j],f[i-1][j-4])+tot[i]-blue[i]);
		}
		if(f[n-1][7]==0x3f3f3f3f) return -1;//特判无解 
		return f[n-1][7];
	}
};