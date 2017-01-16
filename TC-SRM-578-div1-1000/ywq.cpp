#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

int dp[55][55],a[55],b[55],dfn[55][2],st[55],g[55][55],times;
bool v[55];
vi e[55];

namespace km
{
	int lx[55],ly[55];
	int pre1[55],pre2[55],pre3[55];
	bool vx[55],vy[55];
	int slack[55];

	int main(int n1,int n2)
	{
		if (n1>n2)
		{
			for (int i=1;i<=n1;i++)
				for (int j=i+1;j<=n1;j++)
					swap(g[i][j],g[j][i]);
			swap(n1,n2);
		}
		for (int i=1;i<=n1;i++)
		{
			lx[i]=0;
			for (int j=1;j<=n2;j++) lx[i]=max(lx[i],g[i][j]);
		}
		memset(ly+1,0,n2*sizeof(int));
		memset(pre1+1,0,n2*sizeof(int));
		memset(pre3+1,0,n1*sizeof(int));
		for (int i=1;i<=n1;i++)
		{
			for (int j=1;j<=n2;j++)
			{
				slack[j]=lx[i]+ly[j]-g[i][j];pre2[j]=i;
			}
			memset(vx+1,0,n1*sizeof(bool));vx[i]=1;
			memset(vy+1,0,n2*sizeof(bool));
			while (1)
			{
				int mi=1000;
				for (int j=1;j<=n2;j++) if (!vy[j]) mi=min(mi,slack[j]);
				for (int j=1;j<=n1;j++) if (vx[j]) lx[j]-=mi;
				for (int j=1;j<=n2;j++) if (vy[j]) ly[j]+=mi; else slack[j]-=mi;
				bool ok=0;
				for (int j=1;j<=n2;j++)
					if (!(vy[j]||slack[j]))
					{
						vy[j]=1;
						if (pre1[j])
						{
							int x=pre1[j];vx[x]=1;
							for (int k=1;k<=n2;k++)
								if (lx[x]+ly[k]-g[x][k]<slack[k]) {slack[k]=lx[x]+ly[k]-g[x][k];pre2[k]=x;}
						}
						else
						{
							int k1=pre2[j],k2=j;
							while (k2)
							{
								int k3=pre3[k1];
								pre3[k1]=k2;pre1[k2]=k1;
								k2=k3;k1=pre2[k2];
							}
							ok=1;break;
						}
					}
				if (ok) break;
			}
		}
		int ans=0;
		for (int i=1;i<=n1;i++) ans+=lx[i];
		for (int i=1;i<=n2;i++) ans+=ly[i];
		return ans;
	}
}


void dfs(int k)
{
	dfn[k][0]=++times;st[times]=k;
	for (int i=0;i<e[k].size();i++)
		if (!dfn[e[k][i]][0]) dfs(e[k][i]);
	dfn[k][1]=times;
}

void dfs2(int k,int l,int r)
{
	v[k]=1;
	for (int i=0;i<e[k].size();i++)
		if (!(l<=dfn[e[k][i]][0]&&dfn[e[k][i]][0]<=r||v[e[k][i]])) dfs2(e[k][i],l,r);
	int n2=0;
	for (int i=0;i<e[k].size();i++)
		if (!(l<=dfn[e[k][i]][0]&&dfn[e[k][i]][0]<=r||v[e[k][i]])) b[++n2]=e[k][i];
	for (int i=l;i<=r;i++)
	{
		int n1=0;
		for (int j=0;j<e[st[i]].size();j++)
			if (i<=dfn[e[st[i]][j]][0]&&dfn[e[st[i]][j]][0]<=dfn[st[i]][1]) a[++n1]=e[st[i]][j];
		for (int p=1;p<=n1;p++)
			for (int q=1;q<=n2;q++)
				g[p][q]=dp[a[p]][b[q]];
		dp[st[i]][k]=km::main(n1,n2)+1;
	}
	v[k]=0;
}

struct DeerInZooDivOne 
{
    int getmax(vector <int> a, vector <int> b)
    {
    	int n=a.size()+1;
    	for (int i=0;i<n-1;i++)
    	{
    		e[a[i]].pb(b[i]);e[b[i]].pb(a[i]);
    	}
    	dfs(0);
    	int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (!(dfn[i][0]<=dfn[j][0]&&dfn[j][0]<=dfn[i][1]))
    			{
    				memset(v,0,sizeof(v));
    				dfs2(j,dfn[i][0],dfn[i][1]);
    				ans=max(ans,dp[i][j]);
    			}
    	return ans;
    }
};
