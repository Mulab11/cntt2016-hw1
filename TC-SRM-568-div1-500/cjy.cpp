#include<bits/stdc++.h>
using namespace std;
int P=1e9+7,n,v[123],b[123],i,j,s,T,l,r;
vector<pair<int,int> > E[123];
void dfs(int x){for(auto y : E[x])if(!v[y.first])v[y.first]=T,b[y.first]=y.second-b[x],dfs(y.first);else if(b[y.first]!=y.second-b[x])s=0;}
int solve(int x)
{
	for(memset(v,0,sizeof(v)),s=1,i=0;i<n+n;i++)if(!v[i])
	{
		for(v[i]=++T,l=j=b[i]=0,dfs(i),r=999;j<n;j++)if(v[j]==T)l=max(l,x-b[j]);
		for(;j<n+n;j++)if(v[j]==T)r=min(r,b[j]+1);s=1ll*s*max(r-l,0)%P;
	}
	return s;
}
class EqualSums
{
	public:
		int count(vector<string> s)
		{
			for(n=s.size();i<n;i++)for(j=0;j<n;j++)if(s[i][j]^'-')E[i].push_back(make_pair(j+n,s[i][j]-48)),E[j+n].push_back(make_pair(i,s[i][j]-48)); 
			return(solve(0)-solve(1)+P)%P;
		}
};
