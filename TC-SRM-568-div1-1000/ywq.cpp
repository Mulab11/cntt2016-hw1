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

int n,a[55];

namespace prog1
{
	vi e[55];
	int m,l,c[55][2],b[55],color[55];
	bool v[55];

	bool check(int k)
	{
		for (vi::iterator p=e[k].begin();p!=e[k].end();p++)
			if (color[*p]==2)
			{
				color[*p]=color[k]^1;
				if (!check(*p)) return 0;
			}
			else
				if (color[*p]==color[k]) return 0;
		return 1;
	}

	bool dfs(int k,int p)
	{
		if (k>=m)
		{
			for (int i=0;i<p;i++) e[i].clear();
			for (int i=0;i<p;i++)
				for (int j=0;j<p;j++)
					if ((c[i][0]<c[j][0]&&c[j][0]<c[i][1]&&c[i][1]<c[j][1]))
					{
						e[i].pb(j);e[j].pb(i);
					}
			for (int i=0;i<p;i++) color[i]=2;
			for (int i=0;i<p;i++)
				if (color[i]==2)
				{
					color[i]=0;
					if (!check(i)) return 0;
				}
			return 1;
		}
		if (v[k]) return dfs(k+1,p);
		for (int i=k+1;i<m;i++)
			if (!v[i])
			{
				c[p][0]=b[k];c[p][1]=b[i];
				v[k]=1;v[i]=1;
				if (dfs(k+1,p+1)) return 1;
				v[k]=0;v[i]=0;
			}
		return 0;
	}

	string main()
	{
		m=l=0;
		for (int i=0;i<n;i++) if (a[i]==-1) b[m++]=i;
		for (int i=0;i<n;i++)
		{
			int x=-1,y=-1;
			for (int j=0;j<n;j++)
				if (a[j]==i) {if (x==-1) x=j; else y=j;}
			if (x!=-1) {c[l][0]=x;c[l++][1]=y;}
		}
		memset(v,0,sizeof(v));
		if (dfs(0,l)) return "POSSIBLE"; else return "IMPOSSIBLE";
	}
}

namespace prog2
{
	int m,fa[55],c[55][2],b[55],s[55];
	bool d[55];

	int find(int x)
	{
		int y=fa[x];
		if (x!=fa[x]) fa[x]=find(fa[x]);
		d[x]^=d[y];
		return fa[x];
	}

	bool union0(int x,int y,bool z)
	{
		int fx=find(x),fy=find(y);
		if (fx!=fy)
		{
			fa[fy]=fx;d[fy]=d[y]^d[x]^z;return 1;
		}
		if ((d[x]^d[y])!=z) return 0; else return 1;
	}

	string main()
	{
		m=0;
		for (int i=0;i<n;i++)
		{
			int x=-1,y=-1;
			for (int j=0;j<n;j++)
				if (a[j]==i) {if (x==-1) x=j; else y=j;}
			if (x!=-1) {c[m][0]=x;c[m++][1]=y;}
		}
		for (int i=0;i<m;i++)
		{
			b[i]=0;
			for (int j=0;j<m;j++)
				if ((c[i][0]<c[j][0]&&c[j][0]<c[i][1]&&c[i][1]<c[j][1])) b[i]^=(1<<j);
		}
		s[0]=0;for (int i=0;i<n;i++) {s[i+1]=s[i];if (a[i]==-1) s[i+1]^=-1;}
		for (int i=0;i<(1<<m);i++)
		{
			bool ok=1;
			for (int j=0;j<m;j++)
				if (i&(1<<j))
				{
					if (i&b[j]) {ok=0;break;}
				}
				else
				{
					if ((i|b[j])!=i) {ok=0;break;}
				}
			if (!ok) continue;
			for (int j=0;j<=n;j++) 
			{
				fa[j]=j;d[j]=0;
			}
			for (int j=0;j<n;j++) 
				if (a[j]!=-1) union0(j,j+1,0);
			for (int j=0;j<m;j++)
				if (i&(1<<j))
				{
					if (!union0(c[j][0],c[j][1],0)) {ok=0;break;}
				}
				else
				{
					if (!union0(c[j][0],c[j][1],s[c[j][0]]^s[c[j][1]])) {ok=0;break;}
				}
			int x=find(0),y=find(n);
			if (x==y&&(d[0]^d[n])) ok=0;
			if (ok) return "POSSIBLE";
		}
		return "IMPOSSIBLE";
	}
}

struct DisjointSemicircles 
{
    string getPossibility(vector <int> labels)
    {
    	n=labels.size();int s=0;
    	for (int i=0;i<n;i++) a[i]=labels[i];
    	for (int i=0;i<n;i++)
    		if (a[i]==-1) s++;
    	if (s<=12) return prog1::main(); else return prog2::main();
    }
};

