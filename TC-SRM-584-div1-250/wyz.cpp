// BEGIN CUT HERE

// END CUT HERE
#line 5 "Egalitarianism.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class Egalitarianism{
	int n;
	bool g[maxn][maxn];
	int deep[maxn];
	void dfs(int u){
		for (int v=0;v<n;++v)if (g[u][v]&&(deep[v]<0||deep[v]>deep[u]+1)){
			deep[v]=deep[u]+1;
			dfs(v);
		}
	}
	public:
	int maxDifference(vector <string> isFriend, int d){
		memset(g,0,sizeof(g));
		n=isFriend.size();
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			g[i][j]=isFriend[i][j]=='Y';
		int ret=0;
		for (int i=0;i<n;++i){
			memset(deep,-1,sizeof(deep));
			deep[i]=0;
			dfs(i);
			int res=0;
			for (int j=0;j<n;++j)
				if (deep[j]<0) return -1;
				else res=max(res,deep[j]);
			ret=max(ret,res*d);
		}
		return ret;
	}
};
