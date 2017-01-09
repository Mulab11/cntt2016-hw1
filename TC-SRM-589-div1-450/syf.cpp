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

const int N=50+19;
const int oo=(1<<30)-1;

string s;
Vs G;
struct Edge{
	int y,f,nxt;
} E[500000];
int las[N],dis[N],Q[N];
int res=oo,cnt,n,S,T;

void Add_Edge(int x,int y,int f){
	E[cnt]=(Edge){y,f,las[x]};las[x]=cnt++;
	E[cnt]=(Edge){x,0,las[y]};las[y]=cnt++;
}
bool bfs(){
	memset(dis,-1,sizeof(dis));dis[S]=1;
	int f=1,w=0;Q[1]=S;
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
			res+=tmp,flow-=tmp,E[i].f-=tmp,E[i^1].f+=tmp;
		}
	if (!res) dis[x]=-1;
	return res;
}
void Work(char ch1,char ch2){
	memset(las,-1,sizeof(las));cnt=0;
	S=N-1,T=S-1;
	For(i,0,n){
		if (s[i]==ch1) Add_Edge(S,i,1);
		if (s[i]==ch2) Add_Edge(i,T,1);
	}
	For(i,0,n)
		if (s[i]==ch1){
			For(j,0,n)
				if (s[j]==ch2&&G[i][j]=='Y') Add_Edge(i,j,1);
		}
	int tmp=0;
	while (bfs()) tmp+=dinic(S,oo);
	res=min(res,tmp);
}

class GearsDiv1{
public:
	int getmin(string s,Vs G){	//½¨Í¼ÅÜÍøÂçÁ÷
		n=s.length();
		::s=s;::G=G;
		Work('R','G');
		Work('R','B');
		Work('G','B');
		return res;
	}
} Te;