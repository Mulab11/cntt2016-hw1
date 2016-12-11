#include<bits/stdc++.h>
using namespace std;
string a="RGB";
int t,p[55][55],f[55],v[55],i,j,n,S=99,r;
int dfs(int x)
{
	if(v[x])return 0;
	v[x]=1;
	for(int i=0;i<n;i++)if(p[x][i]&&(f[i]<0||dfs(f[i])))
	{
		f[i]=x;
		return 1;
	}
	return 0;
}
class GearsDiv1
{
	public:
		int getmin(string c,vector<string>s)
		{
			n=c.size();
			for(t=0;t<3;t++)
			{
				memset(p,0,sizeof(p));
				memset(f,-1,sizeof(f));
				for(i=0;i<n;i++)for(j=0;j<n;j++)if(c[i]<c[j]&&c[i]!=a[t]&&c[j]!=a[t]&&s[i][j]=='Y')p[i][j]=1;
				for(i=r=0;i<n;i++)if(memset(v,0,sizeof(v)),dfs(i))r++;//考虑最大匹配数				
				S=min(S,r);
			}
			return S;
		}
};
