#include<bits/stdc++.h>
using namespace std;
int f[55],n,r,i;
vector<string> g;
void dp(int x,int F)
{
	int i=0,j=0;
	for(f[x]=0;i<n;i++)if(i!=F&&g[x][i]=='Y')dp(i,x),f[x]+=max(1,f[i]),j|=!f[i];
	f[x]-=j;
}
class TPS
{
	public:
		int minimalBeacons(vector<string> G)
		{
			g=G;r=n=G.size();
			if(n<2)return 0;
			for(;i<n;i++)dp(i,n),r=min(r,f[i]+1);
			return r;
		}
};
