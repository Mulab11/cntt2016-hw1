#include<bits/stdc++.h>
using namespace std;
int n,e[55][55],c[55],v[55],i,j,k,t;
int dfs(int x){v[x]=1;for(int y=1;y<=n;y++)if(e[x][y])if(!c[y]||!v[c[y]]&&dfs(c[y]))return c[y]=x,1;return 0;}
class Incubator
{
	public:
		int maxMagicalGirls(vector<string> s)
		{
			for(n=s.size();i<n;i++)for(j=0;j<n;j++)e[i+1][j+1]=s[i][j]=='Y';
			for(k=1;k<=n;k++)for(i=1;i<=n;i++)for(j=1;j<=n;j++)e[i][j]|=e[i][k]&e[k][j];
			for(i=1;i<=n;i++)memset(v,0,sizeof(v)),t+=dfs(i);
			return n-t;
		}
};
