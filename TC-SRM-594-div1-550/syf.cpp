//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50*50+19;
const int M=500000;
const int oo=(1<<30)-1;

struct Edge{
	int y,f,nxt;
} E[M];
int las[N],Q[N],dis[N],id[59][59];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int S,T,s,t,cnt,num,n,m,res;

void Add_Edge(int x,int y,int f){
	E[cnt]=(Edge){y,f,las[x]};las[x]=cnt++;
	E[cnt]=(Edge){x,0,las[y]};las[y]=cnt++;
}
bool bfs(){
	For(i,1,num+1) dis[i]=-1;
	int f=1,w=0;
	Q[1]=S;dis[S]=1;
	while (f>w){
		int x=Q[++w];
		for (int i=las[x],y;~i;i=E[i].nxt)
			if (E[i].f&&dis[y=E[i].y]==-1){
				dis[y]=dis[x]+1;
				Q[++f]=y;
				if (y==T) return 1;
			}
	}
	return 0;
}
int dinic(int x,int flow){
	if (x==T||!flow) return flow;
	int res=0;
	for (int i=las[x],y;~i&&flow;i=E[i].nxt)
		if (E[i].f&&dis[y=E[i].y]==dis[x]+1){
			int tmp=dinic(y,min(flow,E[i].f));
			E[i].f-=tmp,E[i^1].f+=tmp,flow-=tmp,res+=tmp;
		}
	if (!res) dis[x]=-1;
	return res;
}

class FoxAndGo3{
public:
	int maxEmptyCells(Vs s){	//¹¹Í¼ÅÜÍøÂçÁ÷
		n=s.size();
		memset(las,-1,sizeof(las));
		S=++num,T=++num;
		For(i,0,n) For(j,0,n) id[i][j]=++num;
		For(i,0,n) For(j,0,n){
			if (s[i][j]=='o'){
				Add_Edge(S,id[i][j],1);
				For(k,0,4){
					int x=i+dx[k],y=j+dy[k];
					if (x>=0&&x<n&&y>=0&&y<n&&s[x][y]=='.') Add_Edge(id[i][j],id[x][y],oo);
				}
				res++;
			}
			if (s[i][j]=='.'){
				Add_Edge(id[i][j],T,1);
				res++;
			}
		}
		while (bfs()) res-=dinic(S,oo);
		return res;
	}
} Te;