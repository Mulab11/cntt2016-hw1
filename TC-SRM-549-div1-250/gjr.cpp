#line 7 "PointyWizardHats.cpp"

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

//inline inc(int &a,int/ {return a-b<0? a-b+mod:a-b;}

typedef vector<int> vi;
typedef pair<int,int> pii;


namespace f {
	#define maxn 110
	#define maxm 3000
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
		return maxflow;
	}
}



class PointyWizardHats
{
        public:
        int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius)
        {
        	int n=topHeight.size();
        	int m=bottomHeight.size();
        	f::cnt_li=1;f::start=0;f::final=n+m+1;
        	fill(f::head,0);
        	
        	for (int i=1;i<=n;++i) f::add(f::start,i,1);
        	for (int i=1;i<=m;++i) f::add(i+n,f::final,1);
        	
        	//consider any tow cone
            for (int i=0;i<n;++i) {
            	for (int j=0;j<m;++j) {
            		// if i can match with j
            		if (topRadius[i]<bottomRadius[j]&&(ll)topHeight[i]*bottomRadius[j]>(ll)bottomHeight[j]*topRadius[i]) f::add(i+1,j+n+1,1);
				}
            }
            return f::dinic();
        }

};

