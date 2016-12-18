#include<bits/stdc++.h>
using namespace std;
int a[15],c[8192],i,j,s=1e9,n,m;
int dfs(int k,int now,int old,int has,int type)//搜索
{
	if(k==n)return now?1e9:0;
	int tmp=has&now,s=1e9;
	if(!(type&tmp))s=min(s,dfs(k+1,a[k]^old^(now/2)^(now*2%(1<<m)),now,has|now,type)+c[now]);
	if(!(~type&tmp))s=min(s,dfs(k+1,a[k]^old^(now/2)^(now*2%(1<<m))^now,now,has|now,type|now)+c[now]);
	return s;
}
class YetAnotherBoardGame
{
	public:
		int minimumMoves(vector<string> b)
		{
			for(n=b.size(),m=b[0].size();i<n;i++)for(j=0;j<m;j++)a[i]|=(b[i][j]=='W')<<j;
			for(i=0;i<(1<<m);i++)c[i]=c[i/2]+i%2;
			for(i=0;i<(1<<m);i++)for(j=0;j<2;j++)s=min(s,dfs(1,a[0]^(i/2)^(i*2%(1<<m))^(j*i),i,i,j*i)+c[i]);
			return s==1e9?-1:s;
		}
};
