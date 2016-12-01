#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class GearsDiv1{
	static const int maxn=55;
	int fa[maxn],L,R;
	bool mp[maxn][maxn],to[maxn][maxn],vis[maxn];
	char col[maxn];
	int num[maxn];
	int n;
	
	bool dfs(int p){
		if (vis[p]) return false;
		vis[p]=true;
		for (int i=1;i<=R;++i) if (to[p][i]){
			if (fa[i]==0||dfs(fa[i])){
				fa[i]=p;
				return true;
			}
		}
		return false;
	}
	
	int get(int &a,int b){
		if (num[b]==0) num[b]=++a;
		return num[b];
	}
	
	int solve(char c){
		L=R=0;
		memset(num,0,sizeof(num));
		memset(to,0,sizeof(to));
		memset(fa,0,sizeof(fa));
		for (int i=0;i<n;++i) if (col[i]!=c)
		for (int j=0;j<n;++j) if (col[i]<col[j]) if (col[j]!=c) if (mp[i][j])
		to[get(L,i)][get(R,j)]=true;
		int ret=0;
		for (int i=1;i<=L;++i){
			memset(vis,0,sizeof(vis));
			if (dfs(i)) ++ret;
		}
//		printf("solve %c = %d\n",c,ret);
		return ret;
	}
	
	public:
		int getmin(string color, vector<string> graph){
			n=color.length();
			for (int i=0;i<n;++i) col[i]=color[i];
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (graph[i][j]=='Y') mp[i][j]=true;
			return min({solve('R'),solve('G'),solve('B')});
		}
};
