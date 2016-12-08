#include<bits/stdc++.h>
using namespace std;
vector<string> a,empty;
int b[55][55],c[55];
class ThreeColorability
{
	public:
		int dfs(int x,int g)
		{
			if(~c[x])return c[x]==g;
			c[x]=g;
			for(int i=0;i<a.size();i++)if(~b[x][i]&&!dfs(i,g^b[x][i]))return 0;
			return 1;
		}
		int check()
		{
			int i,j,k;
			memset(b,-1,sizeof(b));
			memset(c,-1,sizeof(c));
			for(j=0;j<a[0].size();j++)for(i=0;i<a.size();i++)for(k=i+1;k<a.size();k++)if(a[i][j]!='?'&&a[k][j]!='?')//连边			
			{
				if(~b[i][k]&&b[i][k]!=(a[i][j]!=a[k][j]))return 0;
				b[i][k]=b[k][i]=(a[i][j]!=a[k][j]);
			}
			for(i=0;i<a.size();i++)if(c[i]<0&&!dfs(i,0))return 0;//二分图染色			
			return 1;
		}
		vector<string> lexSmallest(vector<string> A)
		{
			a=A;
			int i,j;
			for(i=0;i<a.size();i++)for(j=0;j<a[i].size();j++)if(a[i][j]=='?')if(a[i][j]='N',!check())a[i][j]='Z';
			if(check())return a;
			return empty;
		}
};
