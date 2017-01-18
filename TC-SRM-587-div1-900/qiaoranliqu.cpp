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
int i,j,m,n,p,k,vis[N],A[N][N],Q[N];
int bfs(int x)
{
	int l=1; int i;
	Q[Q[0]=1]=x; vis[x]=1;
	for (;l<=Q[0];++l)
	{
			int p=Q[l];
			for (i=0;i<n;++i)
		{
				if (A[p][i]==1)
				{
						if (vis[i]==-1) vis[i]=vis[p],Q[++Q[0]]=i;
						else if (vis[i]!=vis[p]) return 0;
				}
				if (A[p][i]==2)
				{
						if (vis[i]==-1) vis[i]=vis[p]^1,Q[++Q[0]]=i;
						else if (vis[i]==vis[p]) return 0;
				}
		}
	}
	return 1;
}
int work(vector <string> cells)
{
		int i,j,k;
		memset(A,0,sizeof(A));
		memset(vis,-1,sizeof(vis));
		for (i=0;i<n;++i)
			for (j=0;j<n;++j)
				if (i!=j)
				{
						int flag=0;
						for (k=0;k<m;++k) if (cells[i][k]!='?'&&cells[j][k]!='?')
						{
								if (cells[i][k]==cells[j][k]) flag|=1; else flag|=2;
						}
						if (flag==3) return 0;
						A[i][j]=flag;
				}
		for (i=0;i<n;++i)
			if (vis[i]==-1)
				if (!bfs(i)) return 0;
		return 1;
}
class ThreeColorability{
	public:
		vector <string> lexSmallest(vector <string> cells)
		{
			vector<string>ans;
			n=(int)cells.size(); m=(int)cells[0].length();
			if (!work(cells)) return ans;
			for (i=0;i<n;++i)
				for (j=0;j<m;++j)
					if (cells[i][j]=='?')
					{
							cells[i][j]='N';
							if (work(cells)) continue;
							cells[i][j]='Z';
					}
			return cells;
		}
}MRT;

int main()
{
	 MRT.lexSmallest({"??", "?N"});
}

