#include<bits/stdc++.h>
using namespace std;
long long f[55][110],i,j,n;
class MonstersValley
{
	public:
		int minimumPrice(vector<long long> a,vector<int> c)
		{
			for(memset(f,-1,sizeof(f)),n=a.size(),f[0][0]=0;i<n;i++)for(j=0;j<=2*n;j++)if(~f[i][j])if(f[i+1][j+c[i]]=max(f[i+1][j+c[i]],f[i][j]+a[i]),f[i][j]>=a[i])f[i+1][j]=max(f[i+1][j],f[i][j]);
			for(i=0;i<=n+n;i++)if(~f[n][i])return i;
		}
};
