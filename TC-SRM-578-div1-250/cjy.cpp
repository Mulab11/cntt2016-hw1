#include<bits/stdc++.h>
using namespace std;
int P=1e9+7,v[50][50],S[2],s,n,m,i=0,j,d,r=1;
vector<string> a;
void dfs(int x,int y)
{
	int i=0,j;
	for(v[x][y]=1,s^=1;i<n;i++)for(j=0;j<m;j++)if(a[i][j]=='v'&&!v[i][j]&&abs(i-x)+abs(j-y)<=d)dfs(i,j);
}
class GooseInZooDivOne
{
	public:
		int count(vector<string> A,int D)
		{
			for(a=A,d=D,n=a.size(),m=a[0].size();i<n;i++)for(j=0;j<m;j++)if(a[i][j]=='v'&&!v[i][j])s=0,dfs(i,j),S[s]++;
			for(i=0;i<2;i++)for(j=i;j<S[i];j++)r=r*2%P;
			return(r+P-1)%P;
		}
};
