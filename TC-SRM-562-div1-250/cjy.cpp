#include<bits/stdc++.h>
using namespace std;
long long s[128],f[128],n,m,i,j,k,c[55][55];
class PastingPaintingDivOne
{
	public:  
		vector<long long> countColors(vector<string> a,int t)
		{
			for(n=a.size(),m=a[0].size();k++<=n&&t;t--)
			{
				for(memset(f,0,sizeof(f)),i=0;i<n;i++)for(j=0;j<m;j++)if(a[i][j]!='.')f[c[i][j]]--,f[c[i][j]=a[i][j]]++;
				for(i=0;i<n;i++)for(j=0;j<m;j++)c[i][j]=c[i+1][j+1];
				for(i='A';i<'Z';i++)s[i]+=f[i];
			}
			for(i='A';i<'Z';i++)s[i]+=f[i]*t;
			return vector<long long>{s['R'],s['G'],s['B']};
		}
};
