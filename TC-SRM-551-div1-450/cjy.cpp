#include<bits/stdc++.h>
using namespace std;
int d[50][50],n,i,j,k;
class ColorfulWolves//最短路
{
	public:
		int getmin(vector<string> s)
		{
			for(n=s.size(),memset(d,9,sizeof(d));i<n;i++)for(j=k=0;j<n;j++)if(s[i][j]=='Y')d[i][j]=k++;
			for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			return d[0][n-1]<9999?d[0][n-1]:-1;
		}
};
