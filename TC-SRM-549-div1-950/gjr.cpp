#line 7 "CosmicBlocks.cpp"

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define inf 0x3f3f3f3f
#define fill(a,b) memset(a,b,sizeof(a))
#define cpy(a,b) memcpy(a,b,sizeof(b))
#define mp make_pair
#define fi first
#define se second
#define N 
#define mod 1000000007
template<typename T> inline bool MIN(T &a,const T &b) {return a>b? a=b,1:0;}
template<typename T> inline bool MAX(T &a,const T &b) {return a<b? a=b,1:0;}
inline int inc(int &a,int b) {a+=b;if (a>=mod) a-=mod;}
inline int dec(int &a,int b) {a-=b;if (a<0) a+=mod;}
inline int mul(int a,int b) {return (ll)a*b%mod;}
inline int plu(int a,int b) {return a+b>=mod? a+b-mod:a+b;}
inline int sub(int a,int b) {return a-b<0? a-b+mod:a-b;}
typedef vector<int> vi;
typedef pair<int,int> pii;
int n;

vi bT,vec[10];
int cnt[10],hi[10];

int ans;

namespace f {
	#define maxn 10
	#define maxm 100
	int maxflow,start,final,stop,cnt_li;
	int way[maxn],dis[maxn],head[maxn],qe[maxn],head2[maxn];
	struct LI {
		int la,v,f;
	}li[maxm*2];
	void add(int a,int b,int c) {
		li[++cnt_li]=(LI){head[a],b,c};head[a]=cnt_li;
		li[++cnt_li]=(LI){head[b],a,0};head[b]=cnt_li;
	} 
	int bfs() {
		int op=0;
		qe[++op]=final;
		memset(dis,0,sizeof(dis));
		dis[final]=inf;
		for (int cl=1;cl<=op;cl++) {
			int u=qe[cl];
			for (int i=head[u];i;i=li[i].la) {
				int v=li[i].v,f=li[i^1].f;
				if (f&&!dis[v]) {
					dis[v]=dis[u]-1;
					qe[++op]=v;
				}
			}
		}
		return dis[start];
	}
	int find(int u,int top) {
		if (u==final) {
			int flow=inf;
			for (int i=1;i<top;i++) if (li[way[i]].f<flow) {
				flow=li[way[i]].f;
				stop=i;
			}
			for (int i=1;i<top;i++) {
				li[way[i]].f-=flow;
				li[way[i]^1].f+=flow;
			}
			maxflow+=flow;
			return 1;
		}
		for (int &i=head2[u];i;i=li[i].la) {
			int v=li[i].v,f=li[i].f;
			if (f&&dis[v]==dis[u]+1) {
				way[top]=i;
				if (find(v,top+1)&&top!=stop) return 1;
			}
		}
		return 0;
	}
	int dinic() {
		maxflow=0;
		while (bfs()) {
			memcpy(head2,head,sizeof(head));
		    find(start,1);
		}
		for (int e=head[0];e;e=li[e].la) if (li[e].f) return 0;
		return 1;
	}
	int clear() {
		cnt_li=1; fill(head,0); start=0;final=7;
	}
}


int G[10][10];
int check(int c) {
	//it is ok only if the flow is full 
	f::clear();
	vi deg=bT;
	for (int i=0;i<vec[c+1].size();++i) {
		for (int j=0;j<vec[c].size();++j) {
			int a=vec[c+1][i],b=vec[c][j];
			if (G[a][b]) --deg[a],--deg[b],f::add(a+1,b+1,inf);
		}
	}
	
	for (int i=0;i<n;++i) if (deg[i]<0) return 0;
	
	for (int i=0;i<vec[c+1].size();++i) f::add(0,vec[c+1][i]+1,deg[vec[c+1][i]]);
	for (int i=0;i<vec[c].size();++i) f::add(vec[c][i]+1,7,deg[vec[c][i]]);
	return f::dinic();
}

int tot,minW,maxW,used[10],pos[10];
int dfs(int s) {
	if (s==n) {
		for (int i=0;i<n;++i) for (int j=0;j<n;++j) if (G[i][j]&&pos[i]>pos[j]) return 0;
		++tot;
		return 0;
	}
	for (int i=0;i<n;++i) if (!used[i]) {
		used[i]=1;
		pos[s]=i;
		dfs(s+1);
		used[i]=0;
	}
}

int run(int a,int b) {

	if (a==n) {
		for (int i=0;cnt[i+1];++i) {
			if (!check(i)) return 0;
		}
		
		tot=0;
		fill(used,0);
		dfs(0);//get the number of permutation which satisfy the graph
		if (minW<=tot&&tot<=maxW) ++ans;
		return 0;
	}
	if (b==n) return run(a+1,0);
	G[a][b]=0,run(a,b+1);
	if (hi[a]==hi[b]+1) G[a][b]=1,run(a,b+1);
}

int force(int s) {
	if (s==n) {

		for (int i=0;i<10;++i) vec[i].clear(),cnt[i]=0;
		for (int i=0;i<n;++i) cnt[hi[i]]+=bT[i],vec[hi[i]].pb(i);
		for (int i=0;i<n-1;++i) if (cnt[i]<cnt[i+1]) return 0;
		
		//search the pair of adjacent color
		run(0,0);

		return 0;
	}
	for (int i=0;i<n;++i) hi[s]=i,force(s+1);
}

class CosmicBlocks
{
        public:
        int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
        {
        	minW=minWays,maxW=maxWays;
        	bT=blockTypes;
        	n=bT.size();
        	ans=0;
        	force(0);//search height of every color
        	return ans;
        }


};
