// BEGIN CUT HERE

// END CUT HERE
#line 5 "GooseInZooDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007

using namespace std;
const int maxn=2505;

class GooseInZooDivOne{
	int x[maxn],y[maxn],n;
	int limit;
	bool vis[maxn];
	void dfs(int u,int &sz){
		sz^=1;
		vis[u]=1;
		for (int v=1;v<=n;++v)if (abs(x[u]-x[v])+abs(y[u]-y[v])<=limit){
			if (vis[v])continue;
			dfs(v,sz);
		}
	}
	public:
	int count(vector <string> field, int dist){
		limit=dist;
		n=0;
		for (int i=0;i<field.size();++i)
			for (int j=0;j<field[i].size();++j)
				if (field[i][j]=='v'){x[++n]=i;y[n]=j;}
		memset(vis,0,sizeof(vis));
		int cnt[2]={0,0},sz;
		for (int i=1;i<=n;++i)if (!vis[i]){
			dfs(i,sz=0);
			++cnt[sz];
		}
		int ret=1;
		for (int i=1;i<cnt[1];++i) (ret*=2)%=P;
		for (int i=1;i<=cnt[0];++i) (ret*=2)%=P;
		--ret;
		if (ret<0) ret+=P;
		return ret;
	}
};
