// BEGIN CUT HERE

// END CUT HERE
#line 5 "TreeUnion.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
string st;int stamp;
inline int get_char(){
	if (stamp==st.size()) return -1;
	return st[stamp++];
}
inline int read(){
	int ret=0;char ch=get_char();
	while (ch<'0'||ch>'9') ch=get_char();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=get_char();
	}
	return ret;
}

const int maxn=605;
const int maxk=7;

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[maxn*2];
int n,g[maxn],m;
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

class TreeUnion{
	int cnt[maxn][10],n1;
	int last[maxn];
	void dfs(int u,int rt,int dep){
		last[u]=rt;
		++cnt[rt][dep];
		if (dep==maxk) return;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (last[v]==rt) continue;
			dfs(v,rt,dep+1);
		}
	}
	public:
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K){
		if (K==3) return 0;
		memset(g,0,sizeof(g));m=1;
		st="";stamp=0;
		for (int i=0;i<tree1.size();++i) st+=tree1[i];
		for (n=1;stamp<st.size();++n) AddEdge(n+1,read()+1);
		st="";stamp=0;
		for (int i=0;i<tree2.size();++i) st+=tree2[i];
		for (n1=(n++);stamp<st.size();++n) AddEdge(n+1,read()+n1+1);

		memset(cnt,0,sizeof(cnt));
		memset(last,0,sizeof(last));
		for (int i=1;i<=n;++i) dfs(i,i,1);

		double res=0;
		for (int i=1;i<=n1;++i)for (int j=n1+1;j<=n;++j)
			for (int l=2;l<K-1;++l)
				res+=cnt[i][l]*cnt[j][K-l];
		return res/n1/(n1-1)/2;
	}
};
