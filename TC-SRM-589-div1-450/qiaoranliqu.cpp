#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans,A[N][N],B[N][N],color[N],vis[N],match[N];
int dfs(int x)
{
		int i;
		for (i=0;i<n;++i)
			if (!vis[i]&&B[x][i])
			{
					vis[i]=1;
					if (!match[i]||dfs(match[i]-1))
					{
							match[i]=x+1;
							return 1;
					}
			}
	   return 0;
}
int work(int x,int y)
{
		memset(B,0,sizeof(B));
		for (i=0;i<n;++i)
			if (color[i]==x)
			 for (j=0;j<n;++j)
			 	if (color[j]==y&&A[i][j])
			 		B[i][j]=1;
		int ans=0;
		memset(match,0,sizeof(match));
		for (i=0;i<n;++i) 
		{
			memset(vis,0,sizeof(vis));
			if (dfs(i)) ++ans;
		}
		return n-ans; 
}
class GearsDiv1{ 
	public:
	int getmin(string color, vector <string> graph)
	{
			n=color.size();
			for (i=0;i<n;++i) if (color[i]=='R') ::color[i]=0;
			else if (color[i]=='G') ::color[i]=1;
			else if (color[i]=='B') ::color[i]=2;
			for (i=0;i<n;++i)
				for (j=0;j<n;++j) A[i][j]=(graph[i][j]=='Y'?1:0);
			return n-max(work(0,1),max(work(0,2),work(1,2))); 
	}
}MRT;

int main()
{
	 MRT.getmin("RGB",
{"NYY","YNY","YYN"});
}
