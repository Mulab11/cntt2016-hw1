#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxn=305;
string s;
int to[maxn<<1],nx[maxn<<1],hd[maxn],cnt;
int n,dep[maxn];
void addedge(int u,int v){
	to[cnt]=v;nx[cnt]=hd[u];hd[u]=cnt++;
}
int size[maxn],son[maxn],top[maxn];
void dfs(int u){
	size[u]=1;
	cross(i,u){
		int v=to[i];
		dep[v]=dep[u]+1;
		dfs(v);
		if (!son[u]||size[v]>size[son[u]]) son[u]=v;
		size[u]+=size[v];
	}
}
void dfs(int u,int tp){
	top[u]=tp;
	if (!son[u]) return;
	dfs(son[u],tp);
	cross(i,u){
		int v=to[i];
		if (v!=son[u]) dfs(v,v);
	}
}
int num[maxn],fa[maxn];
int lca(int u,int v){
	while (top[u]!=top[v]){
		if (dep[top[u]]>dep[top[v]]) u=fa[top[u]];
			else v=fa[top[v]];
	}
	return dep[u]>dep[v]?v:u;
}
int dist(int u,int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}

/*
因为K<=7而且每个点只连一条边，所以环一定是A->B->A的形式
预处理每棵树中长度为1、2、3、4的链条数，然后期望线性性搞搞即可。
*/

class TreeUnion{
public:
	double expectedCycles(vector<string>t1,vector<string>t2,int K){
		rep(i,0,t1.size()-1) s+=t1[i];
		int nw=0;
		memset(hd,-1,sizeof hd);
		while (nw<s.size()){
			n++;fa[n]=0;
			while (nw<s.size()&&isdigit(s[nw])) fa[n]=fa[n]*10+s[nw]-'0',nw++;nw++;
			addedge(fa[n],n);
		}
		dfs(0),dfs(0,0);
		rep(i,0,n) rep(j,i+1,n) num[dist(i,j)]++;
		s.clear();
		rep(i,0,t2.size()-1) s+=t2[i];
		nw=0;n=0;
		memset(hd,-1,sizeof hd);cnt=0;
		while (nw<s.size()){
			n++;fa[n]=0;
			while (nw<s.size()&&isdigit(s[nw])) fa[n]=fa[n]*10+s[nw]-'0',nw++;nw++;
			addedge(fa[n],n);
		}
		memset(son,0,sizeof son);
		dfs(0),dfs(0,0);
		double ret=0;
		rep(i,0,n) rep(j,i+1,n){
			int d=dist(i,j),rem=K-d-2;
			if (rem<=0) continue;
			ret+=1.0*num[rem]/(n*(n+1)/2);
		}
		return ret;
	}
};
