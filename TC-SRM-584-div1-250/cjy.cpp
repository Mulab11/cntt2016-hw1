#include<bits/stdc++.h>
using namespace std;
int i,j,k,f[55][55],s,n;
class Egalitarianism
{
	public:
		int maxDifference(vector<string> a,int x)
		{
			n=a.size();
			for(;i<n;i++)for(j=i+1;j<n;j++)f[i][j]=f[j][i]=(a[i][j]=='Y'?1:99);
			for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//Floyd
			for(i=0;i<n;i++)for(j=0;j<n;j++)s=max(s,f[i][j]);
			return s==99?-1:s*x;
		}
};
