// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorTravelingSalesman.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;
bool vis[maxn];
bool g[maxn][maxn];
int n;
void dfs(int u){
	if (vis[u]) return;
	vis[u]=1;
	for (int v=0;v<n;++v)
		if (g[u][v])
			dfs(v);
}

const int maxm=10;

class XorTravelingSalesman {
	int bin[maxm+2];
	int a[maxm+2];
	public:
	int maxProfit(vector <int> cityValues, vector <string> roads){
		for (int i=0;i<=maxm;++i) bin[i]=1<<i;
		n=cityValues.size();
		memset(g,0,sizeof(g));
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)if (roads[i][j]=='Y') g[i][j]=1;
		memset(vis,0,sizeof(vis));
		dfs(0);
		memset(a,0,sizeof(a));
		for (int i=0;i<n;++i)if (vis[i]){
			int tmp=cityValues[i];
			for (int j=maxm;j>=0;--j){
				if ((tmp&bin[j])==0) continue;
				if (!a[j]){a[j]=tmp;break;}
				tmp^=a[j];
			}
		}
		int ret=0;
		for (int j=maxm;j>=0;--j){
			if ((ret&bin[j])||!a[j]) continue;
			ret^=a[j];
		}
		return ret;
	}
};
