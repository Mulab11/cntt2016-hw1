// BEGIN CUT HERE

// END CUT HERE
#line 5 "CurvyonRails.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

namespace CostFlow{
	#define N 2333
	#define M 233333
	#define INF (1e9)
	struct edge{
		int adj,next,cap,len;
		edge(){}
		edge(int a,int n,int c,int l):adj(a),next(n),cap(c),len(l){}
	} e[M];
	int n,g[N],m;
	void AddEdge(int u,int v,int c,int w){
		e[++m]=edge(v,g[u],c,w);g[u]=m;
		e[++m]=edge(u,g[v],0,-w);g[v]=m;
	}
	int q[N],qh,qt;
	int from[N],mind[N];
	bool exist[N];
	bool spfa(){
		memset(mind,127,sizeof(mind));
		qh=qt=0;
		q[(++qt)%=n]=1;
		from[1]=mind[1]=0;exist[1]=1;
		bool flag=0;
		while (qh!=qt){
			int u=q[(++qh)%=n];
			flag|=u==n;
			for (int i=g[u];i;i=e[i].next)if (e[i].cap){
				int v=e[i].adj;
				if (mind[v]<=mind[u]+e[i].len) continue;
				mind[v]=mind[u]+e[i].len;
				from[v]=i;
				if (exist[v]) continue;
				exist[v]=1;
				q[(++qt)%=n]=v;
			}
			exist[u]=0;
		}
		return flag;
	}
	int maxflow,mincost;
	void mcf(){
		int flow=INF,cost=0;
		for (int i=from[n];i;i=from[e[i^1].adj])
			flow=min(flow,e[i].cap);
		for (int i=from[n];i;i=from[e[i^1].adj]){
			cost+=flow*e[i].len;
			e[i].cap-=flow;
			e[i^1].cap+=flow;
		}
		maxflow+=flow;mincost+=cost;
	}
	int doit(){
		mincost=0;maxflow=0;
		while (spfa()) mcf();
		return mincost;
	}
};


class CurvyonRails{
	int idr[66][66];
	int idc[66][66];
	int r,c;
	public:
	int getmin(vector <string> field){
		using namespace CostFlow;
		memset(g,0,sizeof(g));m=1;
		r=field.size();
		c=field[0].size();
		int cnt[2]={0,0};
		n=2;
		memset(idr,0,sizeof(idr));
		memset(idc,0,sizeof(idc));
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)if (field[i-1][j-1]!='w'){
			++cnt[(i+j)&1];
			idr[i][j]=n++;
			idc[i][j]=n++;
			AddEdge(idr[i][j],idc[i][j],1,field[i-1][j-1]=='C');
			AddEdge(idc[i][j],idr[i][j],1,field[i-1][j-1]=='C');
		}
		if (cnt[0]!=cnt[1]) return -1;
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)if (idr[i][j]){
			if ((i+j)&1){
				AddEdge(1,idr[i][j],1,0);
				AddEdge(1,idc[i][j],1,0);
				if (idr[i-1][j]) AddEdge(idr[i][j],idr[i-1][j],1,0);
				if (idr[i+1][j]) AddEdge(idr[i][j],idr[i+1][j],1,0);
				if (idc[i][j-1]) AddEdge(idc[i][j],idc[i][j-1],1,0);
				if (idc[i][j+1]) AddEdge(idc[i][j],idc[i][j+1],1,0);
			}
			else AddEdge(idr[i][j],n,1,0),AddEdge(idc[i][j],n,1,0);
		}
		int ret=doit();
		if (maxflow!=cnt[0]+cnt[1]) return -1;
		return ret;
	}
};
