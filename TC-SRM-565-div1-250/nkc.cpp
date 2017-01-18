#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct MonstersValley
{
	long long f[N][N<<1];
	int minimumPrice(vector<long long> dread, vector <int> price)
	{
		int n=dread.size();
		int i,j;
		memset(f,0xef,sizeof(f));
		f[0][price[0]]=dread[0];
		for(i=0;i<n-1;i++)
		for(j=0;j<=2*n;j++)
		{
			f[i+1][j+price[i+1]]=max(f[i+1][j+price[i+1]],f[i][j]+dread[i+1]);
			if(f[i][j]>=dread[i+1]) f[i+1][j]=max(f[i+1][j],f[i][j]); 
		}
		for(i=0;i<=2*n;i++)
		if(f[n-1][i]>0) return i;
	}
};