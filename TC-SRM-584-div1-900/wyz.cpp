// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxTheLinguist.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 105
#define M 2333

struct edge{
	int from,adj,next;int len;
	edge(){}
	edge(int _from,int _adj,int _next,int _len):from(_from),adj(_adj),next(_next),len(_len){}
} e[M];
int n,g[N],m;int n0;
void AddEdge(int u,int v,int w){
//	printf("%d %d %d\n",u,v,w);
	e[++m]=edge(u,v,g[u],w);g[u]=m;
}

int in[N];
int prep[N];
int vis[N],stamp;
int bl[N],cnt;
int directed_MST(){
	n=n0;
	int ret=0;
	e[0].adj=0;
	for (;;){
		memset(in,127,sizeof(in));
		memset(prep,0,sizeof(prep));
		for (int u=1;u<=n;++u)
			for (int i=g[u];i;i=e[i].next)
				if (e[i].len<in[e[i].adj])
					in[e[i].adj]=e[i].len,prep[e[i].adj]=u;
		for (int i=1;i<=n;++i) if (prep[i]) ret+=in[i];
		memset(vis,0,sizeof(vis));vis[0]=stamp=1;
		memset(bl,0,sizeof(bl));cnt=0;
		for (int i=1;i<=n;++i)if (!vis[i]){
			int u=i;
			++stamp;
			for (;!vis[u];u=prep[u]) vis[u]=stamp;
			if (vis[u]==stamp){
				++cnt;
				for (;!bl[u];u=prep[u]) bl[u]=cnt;
			}
		}
		if (!cnt) return ret;
		for (int i=1;i<=n;++i) if (!bl[i]) bl[i]=++cnt;
		int m0=m;
		memset(g,0,sizeof(g));m=1;
		for (int i=2;i<=m0;++i)
			if (bl[e[i].from]!=bl[e[i].adj])
				AddEdge(bl[e[i].from],bl[e[i].adj],e[i].len-in[e[i].adj]);
		n=cnt;
	}
}

void dfs(int u,int &stamp){
	++stamp;
	vis[u]=1;
	for (int i=g[u];i;i=e[i].next)
		if (!vis[e[i].adj]) dfs(e[i].adj,stamp);
}

class FoxTheLinguist{
	public:
	int minimalHours(int n, vector <string> courseInfo){
		n0=n*10+1;
		string st="";
		for (int i=0;i<courseInfo.size();++i) st+=courseInfo[i];
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<st.size();i+=12)
			AddEdge((st[i]-65)*10+st[i+1]-46,(st[i+4]-65)*10+st[i+5]-46,(((st[i+7]-48)*10+st[i+8]-48)*10+st[i+9]-48)*10+st[i+10]-48);
		for (int i=0;i<n;AddEdge(1,(i++)*10+2,0))
			for (int j=2;j<=10;++j) AddEdge(i*10+j+1,i*10+j,0);
		memset(vis,0,sizeof(vis));
		int stamp=0;
		dfs(1,stamp);
		if (stamp<n0) return -1;
		return directed_MST();
	}
};
