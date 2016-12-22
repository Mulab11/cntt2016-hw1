#include<bits/stdc++.h>
using namespace std;
int f[3000],l,i,j,n,m,d;
int F(int x){return f[x]==x?x:f[x]=F(f[x]);}
class ArcadeManao
{
	public:
		int shortestLadder(vector<string> a,int x,int y)//暴力
		{
			for(n=a.size(),m=a[0].size();i<n*m;i++)f[i]=i;
			for(i=0;i<n;i++)for(j=1;j<m;j++)if(a[i][j]=='X'&&a[i][j-1]=='X')f[F(i*m+j)]=F(i*m+j-1);
			for(d=1;d<=n;d++)
			{
				if(F(x*m-m+y-1)==F(n*m-m))return d-1;
				for(i=0;i+d<n;i++)for(j=0;j<m;j++)if(a[i][j]=='X'&&a[i+d][j]=='X')f[F(i*m+j)]=F(i*m+d*m+j);
			}
			return -1;
		}
};
