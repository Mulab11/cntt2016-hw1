// BEGIN CUT HERE

// END CUT HERE
#line 5 "OldBridges.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define N 55
#define M 5555
#define INF 1e9
struct edge{
	int adj,next,cap;
	edge(){}
	edge(int a,int n,int c):adj(a),next(n),cap(c){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v,int c){
	e[++m]=edge(v,g[u],c);g[u]=m;
	e[++m]=edge(u,g[v],0);g[v]=m;
}

int h[N],gap[N],di[N],maxflow,flow;
bool found;
void aug(int u){
	if (u==n){
		maxflow+=flow;
		found=1;
		return;
	}
	int i,tmp=flow;
	for (i=di[u];i;i=e[i].next)if (e[i].cap){
		int v=e[i].adj;
		if (h[u]==h[v]+1){
			di[u]=i;
			flow=min(flow,e[i].cap);
			aug(v);
			if (h[1]==n) return;
			if (found) break;
			flow=tmp;
		}
	}
	if (found){
		e[i].cap-=flow;
		e[i^1].cap+=flow;
	}
	else{
		if (!--gap[h[u]]) h[1]=n;
		int minh=n;
		for (int i=g[u];i;i=e[i].next)if (e[i].cap)
			minh=min(minh,h[e[i].adj]+1);
		++gap[h[u]=minh];
		di[u]=g[u];
	}
}



void work_maxflow(){
	memset(h,0,sizeof(h));
	memset(gap,0,sizeof(gap));
	gap[0]=n;
	for (int i=1;i<=n;++i) di[i]=g[i];
	maxflow=0;
	while (h[1]<n){
		flow=INF;
		found=0;
		aug(1);
	}
}


int s1,t1,cnt1,s2,t2,cnt2,num;
int a[N][N];

void build(){
	swap(s1,t1);
	memset(g,0,sizeof(g));m=1;
	for (int i=1;i<=num;++i)
		for (int j=1;j<=num;++j)
			if (a[i][j]) AddEdge(i+1,j+1,a[i][j]);
	AddEdge(1,s1,cnt1);AddEdge(t1,n,cnt1);
	AddEdge(1,s2,cnt2);AddEdge(t2,n,cnt2);
}


class OldBridges {
	public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
		s1=a1+2;t1=a2+2;cnt1=an;
		s2=b1+2;t2=b2+2;cnt2=bn;
		num=bridges.size();
		n=num+2;
		for (int i=1;i<=num;++i)for (int j=1;j<=num;++j)
			a[i][j]=bridges[i-1][j-1]!='N'?bridges[i-1][j-1]=='O':INF;
		build();
		work_maxflow();
		if (maxflow<cnt1+cnt2) return "No";
		build();
		work_maxflow();
		return maxflow<cnt1+cnt2?"No":"Yes";
	}
};
