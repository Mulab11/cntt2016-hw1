#include <vector>
#include <string>
#include <cstring>
using namespace std;
class CirclesGame{
public:
	int n,fa[60],g[60]; // g[i]为以i为根的子树的SG值
	struct edge{int to;edge*next;}E[60],*first[60];
	bool S[64];
	void dfs2(int i,int v){ // 将能转移到的SG值加入S，val为与i到子树的根的路径相邻的子树的SG值异或和
		for(edge*e=first[i];e;e=e->next)v^=g[e->to];
		S[v]=1;
		for(edge*e=first[i];e;e=e->next)dfs2(e->to,v^g[e->to]);
	}
	void dfs1(int i){ // 计算以i为根的子树中所有点的g值
		for(edge*e=first[i];e;e=e->next)dfs1(e->to);
		memset(S,0,sizeof(S));
		dfs2(i,0);
		for(g[i]=0;S[g[i]];g[i]++); // g[i]等于不属于S的最小自然数 
	}
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r){
		// 构造圆构成的森林，fa[i]为i的父节点
		n=x.size();
		for(int i=0;i<n;i++)fa[i]=-1;
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(r[j]>r[i]&&(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<(r[i]+r[j])*(r[i]+r[j])){
			if(fa[i]==-1||r[j]<r[fa[i]])fa[i]=j;
		}
		// 用邻接表存储
		for(int i=0;i<n;i++)if(fa[i]!=-1)E[i]=(edge){i,first[fa[i]]},first[fa[i]]=E+i;
		// 计算每个树的SG值的异或和
		int v=0;
		for(int i=0;i<n;i++)if(fa[i]==-1)dfs1(i),v^=g[i];
		return v?"Alice":"Bob";
	}
};
