// by ξ

#include <bits/stdc++.h>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define sqr(x) (x)*(x)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> PDD;
typedef vector<int> VI;
typedef vector<PII> VII;
typedef int Arr[5005];

struct GameInDarknessDiv1{
	int n,m,rt,ta,INDEX,ID[55][55];
	Arr fa,d;
	bool ___[5005];
	VI Ed[5005];
	vector<string>Maps;
	void Link(int u,int x,int y){
		// 连边
		if(x>=n || y>=m)return;
		if(Maps[x][y]!='#'){
			int v=ID[x][y];
			Ed[u].pb(v);
			Ed[v].pb(u);
		}
	}
	void dfs(int u){
		// 算深度
		d[u]=d[fa[u]]+1;
		for(int v:Ed[u])if(fa[u]^v)fa[v]=u,dfs(v);
	}
	void gao(int u){
		for(int v:Ed[u])if(v^fa[u])gao(v);
		___[u]=1;
	}
	int chang(int u,int ff){
		// 算长度
		int re=0;
		for(int v:Ed[u])if(v^ff)re=max(re,chang(v,u));
		return re+1;
	}
	bool hehe(int u){
		// u有3个长度>2的分支
		int an=0;
		for(int v:Ed[u])if(chang(v,u)>2)++an;
		return an>2;
	}
	bool ck(){
		gao(ta);
		For(i,1,INDEX)if(___[i])
		if(hehe(i))return 0;
		return 1;
	}
	string check(vector<string>field){
		Maps=field;
		n=Maps.size();m=Maps[0].length();
		rep(i,0,n)rep(j,0,m)ID[i][j]=++INDEX;
		rep(i,0,n)rep(j,0,m)if(Maps[i][j]!='#'){
			if(Maps[i][j]=='A')rt=ID[i][j];
			if(Maps[i][j]=='B')ta=ID[i][j];
			Link(ID[i][j],i+1,j);
			Link(ID[i][j],i,j+1);
		}
		*d=-1;dfs(rt);
		if(d[ta]==1)return "Alice wins";
		// B能跑到的范围
		int aim=d[ta]/2+1+(d[ta]&1);
		while(d[ta]>aim)ta=fa[ta];
		return ck()?"Alice wins":"Bob wins";
	}
};