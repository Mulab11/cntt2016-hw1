#include<bits/stdc++.h>
using namespace std;
int d[55],f[55][55],i,j,k,m;
long long s=1;
class PenguinSledding
{
	public:
		long long countDesigns(int n,vector<int> x,vector<int> y)
		{
			for(m=x.size();i<m;i++)d[x[i]]++,d[y[i]]++,f[x[i]][y[i]]=f[y[i]][x[i]]=1;
			for(i=1;i<=n;s+=1ll<<d[i],i++)for(j=i;j<=n;j++)for(k=j;k<=n;k++)if(f[i][j]&&f[i][k]&&f[j][k])s++;
			return s-n-m;
		}
};
