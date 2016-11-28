#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class PointyWizardHats{
	static const int maxn=55;
	int fa[maxn],n,m;
	bool vis[maxn],mp[maxn][maxn];
	
	bool check(int a,int b,int c,int d){
		if (b>=d) return false;
//		printf("check(%d,%d,%d,%d)\n",a,b,c,d);
		double tmp=(double)c/d*b;
		if (tmp<a) return true;
		else return false;
	}
	
	bool dfs(int p){
		if (vis[p]) return false;
		vis[p]=true;
		for (int i=1;i<=m;++i) if (mp[p][i]){
			if (fa[i]==0||dfs(fa[i])){
				fa[i]=p;
				return true;
			}
		}
		return false;
	}
	
	public:
		int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight,
		vector<int> bottomRadius){
			n=topHeight.size();
			m=bottomHeight.size();
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
			if (check(topHeight[i],topRadius[i],bottomHeight[j],bottomRadius[j])) mp[i+1][j+1]=true;
			else mp[i+1][j+1]=false;
			int ans=0;
			memset(fa,0,sizeof(fa));
//			for (int i=1;i<=n;++i)
//			for (int j=1;j<=m;++j) if (mp[i][j]) printf("%d,%d\n",i,j);
			for (int i=1;i<=n;++i){
				memset(vis,0,sizeof(vis));
				if (dfs(i)) ++ans;
			}
			return ans;
		}
};
