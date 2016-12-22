#include<bits/stdc++.h>
#define A(x,y) x=(x+y)%P
using namespace std;
int P=1e9+9,n,s[333],f[333][333],g[333][333],h[333][333],i,j,k;//f:有顶 g:无顶 h:空
class TheExperiment
{
	public:
		int countPlacements(vector<string> S,int m,int l,int a,int b)
		{
			for(auto x : S)for(auto y : x)s[++n]=s[n-1]+y-48;
			for(;i<=n;i++)for(g[i][0]=h[i][0]=j=1;j<=m;j++)
			{
				for(k=max(0,i-l);k<i;k++)if(a<=s[i]-s[k]&&s[i]-s[k]<=b)if(A(g[i][j],g[k][j-1]),k==i-l)A(f[i][j],g[k][j-1]);else A(f[i][j],f[k][j-1]);
				if(i)A(g[i][j],h[i-1][j]),h[i][j]=(f[i][j]+h[i-1][j])%P;
			}
			return h[n][m];
		}
};
