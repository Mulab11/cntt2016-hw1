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

const int N=30;

struct Edge{
	int y,z,nxt;
} E[500000];

Vi T[N];
string res,s;
int las[N],Q[N*N],num[N],vis[N],dis[N];
int x,n,cnt;
stringstream ss;

void Add_Edge(int x,int y,int z){
	E[cnt]=(Edge){y,z,las[x]};las[x]=cnt++;
}
string Work(Vs B){	//把题目转为差分约束模型，用SPFA判断负环
	memset(las,-1,sizeof(las));
	cnt=0;
	For(i,0,B.size()){
		int x=B[i][0]-'A',a=B[i][1]-'0';
		int y=B[i][3]-'A',b=B[i][4]-'0';
		Add_Edge(x,y,(T[y][b+1]-1)-T[x][a]);
		Add_Edge(y,x,(T[x][a+1]-1)-T[y][b]);
	}
	memset(num,0,sizeof(num));
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	int f=0,w=0;
	For(i,0,n){
		Q[++f]=i;vis[i]=1;
	}
	while (f>w){
		int x=Q[++w];
		for (int i=las[x],y;~i;i=E[i].nxt)
			if (dis[x]+E[i].z<dis[y=E[i].y]){
				dis[y]=dis[x]+E[i].z;
				if (!vis[y]){
					vis[y]=1;
					Q[++f]=y;
					if (++num[y]>n) return "N";
				}
			}
		vis[x]=0;
	}
	return "Y";
}

class History{
public:
	string verifyClaims(Vs D,Vs B,Vs Q){
		n=D.size();
		For(i,0,n){
			stringstream ss;
			ss<<D[i];
			while (ss>>x) T[i].pb(x);
		}
		ss<<accumulate(B.begin(),B.end(),string());
		B.clear();
		while (ss>>s) B.pb(s);
		For(i,0,Q.size()){	//对于每一个询问，加入这条关系判断
			B.pb(Q[i]);
			res+=Work(B);
			B.pop_back();
		}
		return res;
	}
} Te;