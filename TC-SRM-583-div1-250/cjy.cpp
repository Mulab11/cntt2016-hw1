#include<bits/stdc++.h>
using namespace std;
int f[55][55],i,j,k,n;
class TravelOnMars
{
	public:
		int minTimes(vector<int> a,int s,int t)
		{
			memset(f,9,sizeof(f));
			for(n=a.size();i<n;i++)for(int j=1;j<=a[i];j++)f[i][(i+j)%n]=f[i][(i+n-j)%n]=1;
			for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			return f[s][t];
		}
};
