// BEGIN CUT HERE

// END CUT HERE
#line 5 "DisjointSemicircles.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

struct edge{
	int adj,next,type;
	edge(){}
	edge(int _adj,int _next,int _type):adj(_adj),next(_next),type(_type){}
};

namespace judge{
	edge e[maxn*maxn];
	int n,g[maxn],m;
	void AddEdge(int u,int v,int t){
//		printf("%d %d %d\n",u,v,t);
		e[++m]=edge(v,g[u],t);g[u]=m;
		e[++m]=edge(u,g[v],t);g[v]=m;
	}
	void clear(){memset(g,0,sizeof(g));m=1;}
	int col[maxn];
	int q[maxn],qh,qt;
	bool doit(){
		memset(col,-1,sizeof(col));
		qh=qt=0;
		for (int _s=0;_s<n;++_s)if (col[_s]<0){
			q[++qt]=_s;
			col[_s]=0;
			while (qh<qt){
				int u=q[++qh];
				for (int i=g[u];i;i=e[i].next){
					int v=e[i].adj;
					if (col[v]>=0&&col[v]!=(col[u]^e[i].type)) return 0;
					if (col[v]>=0) continue;
					col[v]=col[u]^e[i].type;
					q[++qt]=v;
				}
			}
		}
		return 1;
	}
};

int a[maxn],n;
pair<int,int> p[maxn];
int t;
bool found;


namespace subtask1{
	void dfs(int u,int _l,int _r){
		if (_l>_r) return;
		if (u==n){
			judge::clear();
			judge::n=t;
			for (int i=0;i<t;++i)for (int j=0;j<t;++j)
				if (p[i].first<p[j].first&&p[j].first<p[i].second&&p[i].second<p[j].second)
					judge::AddEdge(i,j,1);
			if (judge::doit()) found=1;
//			if (found) for (int i=0;i<t;++i) printf("%d %d\n",p[i].first,p[i].second);
			return;
		}
		if (a[u]>=0) dfs(u+1,_l,_r);
		else{
			a[u]=0;
			for (int i=0;i<u;++i)if (a[i]<0){
				a[i]=0;
				p[t++]=make_pair(i,u);
				dfs(u+1,_l-1,_r-1);
				if (found) return;
				--t;
				a[i]=-1;
			}
			a[u]=-1;
			dfs(u+1,_l+1,_r-1);
		}
	}
};

namespace subtask2{
	int b[maxn];
	void dfs(int u){
		if (u==t){
//			puts("qwq");
			judge::clear();
			judge::n=n+1;
			for (int i=0;i<t;++i){
				int tmp=(p[i].second-p[i].first+1)&(b[i]^1);
				judge::AddEdge(p[i].first+1,p[i].second,tmp);
				judge::AddEdge(p[i].first,p[i].first+1,b[i]);
				judge::AddEdge(p[i].second,p[i].second+1,b[i]);
			}
			judge::AddEdge(0,n,0);
			if (judge::doit()) found=1;
//			if (found) for (int i=0;i<t;++i) printf("%d\n",b[i]);
			return;
		}
		b[u]=0;
		bool valid=1;
		for (int i=0;valid&&i<u;++i)if (b[u]==b[i]){
			if (p[i].first<p[u].first&&p[u].first<p[i].second&&p[i].second<p[u].second) valid=0;
			if (p[u].first<p[i].first&&p[i].first<p[u].second&&p[u].second<p[i].second) valid=0;
		}
		if (valid) dfs(u+1);
		if (found) return;
		b[u]=1;
		valid=1;
		for (int i=0;valid&&i<u;++i)if (b[u]==b[i]){
			if (p[i].first<p[u].first&&p[u].first<p[i].second&&p[i].second<p[u].second) valid=0;
			if (p[u].first<p[i].first&&p[i].first<p[u].second&&p[u].second<p[i].second) valid=0;
		}
		if (valid) dfs(u+1);
	}
};


class DisjointSemicircles {
	public:
	string getPossibility(vector <int> labels){
		n=labels.size();
		int last[maxn];
		memset(last,-1,sizeof(last));
		t=0;
		for (int i=0;i<n;++i){
			a[i]=labels[i];
			if (a[i]>=0){
				if (last[a[i]]>=0) p[t++]=make_pair(last[a[i]],i);
				last[a[i]]=i;
			}
		}
//		for (int i=0;i<t;++i) printf("%d %d\n",p[i].first,p[i].second);
		found=0;
		if (t>19) subtask1::dfs(0,0,n-2*t);
		else subtask2::dfs(0);
		return found?"POSSIBLE":"IMPOSSIBLE";
	}
};
