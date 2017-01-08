#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
double s;
long long f[80][80][2],g[2][80];//f[i][j][k]:点i，答案j，父亲是否选
int i,j,a,b,o,e=1,n;
vector<int> E[40];
void dfs(int x,int F)
{
	for(auto y : E[x])if(y!=F)dfs(y,x);
	for(a=0;a<2;a++)for(b=0;b<2;b++)
	{
		if(memset(g,0,sizeof(g)),b)g[e][n]=1;else g[e][n-1+2*a]=1;
		for(auto y : E[x])if(y!=F)for(swap(o,e),memset(g[e],0,sizeof(g[e])),i=0;i<=n+n;i++)if(f[y][i][b])for(j=0;j<=n+n;j++)if(g[o][j])g[e][i+j-n]+=f[y][i][b]*g[o][j];
		for(i=0;i<=n+n;i++)f[x][i][a]+=g[e][i];
	}
}
class CentaurCompany
{
	public:
		double getvalue(vector<int> u,vector<int> v)
		{
			for(n=u.size();i<n;i++)E[u[i]].push_back(v[i]),E[v[i]].push_back(u[i]);
			for(dfs(1,0),i=0;i<=n-2;i++)s+=f[1][i+n+2][1]*i;
			return s/(1ll<<n);
		}
};
