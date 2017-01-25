#include <vector>
#include <string>
#include <algorithm>
#define MOD 1000000007
using namespace std;
class SimilarNames{
public:
	int n,m,k,ex[8],ey[8],V[16],G[16],popc[1<<16];
	vector<int> ch[51],split[1<<16];
	int f[51][1<<16],g[51][1<<16];
	int calc_sum(int i,int j,int S,int k,int T){
		if(k==split[S].size())return 1ll*dfs_g(i,j-1,T)*dfs_f(ch[i][j-1],S-T)%MOD;
		return(calc_sum(i,j,S,k+1,T)+calc_sum(i,j,S,k+1,T|split[S][k]))%MOD;
	}
	int dfs_g(int i,int j,int S){ // 将点集S加入i的前j个子树（除i外）的方案数
		if(!j)return!S;
		int&s=g[ch[i][j-1]][S];
		if(s)return s-1;
		s=j==1?dfs_f(ch[i][0],S):calc_sum(i,j,S,0,0);
		return s++;
	}
	int dfs_f(int i,int S){ // 将点集S加入i子树的方案数
		int&s=f[i][S];
		if(s)return s-1;
		s=dfs_g(i,ch[i].size(),S);
		for(int j=0;j<m;j++)if((S>>j&1)&&!(G[j]&S))s=(s+dfs_g(i,ch[i].size(),S-(1<<j)))%MOD;
		return s++;
	}
	bool vis[1<<16];
	int fa[16];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	void init(int S){ // 预处理连通块划分split[S]
		vis[S]=1;
		for(int i=0;i<m;i++)if(S>>i&1)fa[i]=i;
		for(int i=0;i<k;i++)if((S>>ex[i]&1)&&(S>>ey[i]&1))fa[find(ex[i])]=find(ey[i]);
		int RS[m]; // R为连通块根集合
		for(int i=0;i<m;i++)if(S>>i&1)RS[i]=0;
		for(int i=0;i<m;i++)if(S>>i&1)RS[find(i)]|=1<<i;
		for(int i=0;i<m;i++)if((S>>i&1)&&find(i)==i)split[S].push_back(RS[i]);
		for(int i=0;i<m;i++)if((S>>i&1)&&!(G[i]&S)&&!vis[S-(1<<i)])init(S-(1<<i));
	}
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		n=names.size();m=0;k=info1.size();
		// 离散化图中的点集
		for(int i=0;i<k;i++)V[m++]=info1[i],V[m++]=info2[i];
		sort(V,V+m);m=unique(V,V+m)-V;
		for(int i=0;i<m;i++)G[i]=0;
		for(int i=0;i<k;i++)G[ey[i]=lower_bound(V,V+m,info2[i])-V]|=1<<(ex[i]=lower_bound(V,V+m,info1[i])-V);
		// 字符串前缀关系构树
		for(int i=0;i<n;i++){
			int f=n;
			for(int j=0;j<n;j++)if(j!=i&&names[j].length()<names[i].length()&&(f==n||names[j].length()>names[f].length())){
				bool s=1;for(int k=0;k<names[j].length()&&s;k++)if(names[j][k]!=names[i][k])s=0;
				if(s)f=j;
			}
			ch[f].push_back(i);
		}
		// DP
		for(int S=0;S<(1<<m);S++)popc[S]=S?popc[S&(S-1)]+1:0;
		init((1<<m)-1);
		int ans=dfs_g(n,ch[n].size(),(1<<m)-1);
		for(int i=n-m;i;i--)ans=1ll*ans*i%MOD;
		return ans;
	}
};
