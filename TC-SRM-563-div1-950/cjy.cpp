#include <bits/stdc++.h>
#define I2 pair<int,int>
#define I4 pair<I2,I2>
using namespace std;
int f[2][50][50],b[50][50],p[2500],P=1e9+9,t[2500],dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},n,m,i,j,F=1,T,x,y,s,o,e=1;
map<I4,int> S;
int C(int k){if(x=i+dx[k],y=j+dy[k],~x&&~y&&x<n&&y<m)return b[x][y]?f[o][x][y]:f[o][i][j];return 0;} 
class CoinsGame
{
	public:
		int ways(vector<string> a)
		{
			for(n=a.size(),m=a[0].size();i<n;i++)for(j=0;j<m;j++)x+=f[o][i][j]=b[i][j]=a[i][j]=='.';
			for(i=p[0]=1;i<=x;i++)p[i]=p[i-1]*2%P;
			for(s=p[x]-1;F;swap(o,e))
			{
				for(S.clear(),T=F=i=0;i<n;i++)for(j=0;j<m;j++)if(b[i][j])
				{
					I4 g=I4(I2(C(0),C(1)),I2(C(2),C(3)));
					if(!S.count(g))t[S[g]=++T]=0;
					if(t[f[e][i][j]=S[g]]++,S[g]!=f[o][i][j])F=1;
				}
			}
			for(i=1;i<=T;i++)s=(s+P+1-p[t[i]])%P;
			return s;
		}
};
