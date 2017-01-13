#include<bits/stdc++.h>
using namespace std;
int f[50],i,j,n,g[50],w[50],a[99],s;
vector<int> E[50];
void dfs(int x,int k){a[k]=1;for(auto y : E[x])dfs(y,k^w[y]^g[y]);}
void dp(int x)
{
	for(auto y : E[x])dp(y);
	for(memset(a,0,sizeof(a)),dfs(x,w[x]);a[g[x]];g[x]++);w[f[x]]^=g[x];
}
class CirclesGame
{
	public:
		string whoCanWin(vector<int> x,vector<int> y,vector<int> r)
		{
			for(n=x.size();i<n;i++)for(f[i]=-1,j=0;j<n;j++)if(j!=i&&r[i]+sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))<r[j]&&(f[i]<0||r[j]<r[f[i]]))f[i]=j;
			for(i=0;i<n;i++)if(~f[i])E[f[i]].push_back(i);
			for(i=0;i<n;i++)if(f[i]<0)dp(i),s^=g[i];
			return s?"Alice":"Bob";
		}
};
