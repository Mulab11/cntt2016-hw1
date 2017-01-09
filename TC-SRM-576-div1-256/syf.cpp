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

const int N=50+3;

char s[N][N];
bool vis[N][N];
pii Q[N*N];
int n,m,tx,ty,res,f,w;

void Upd(int x,int y){
	if (x<1||x>n||y<1||y>m) return;
	if (s[x][y]!='X'||vis[x][y]) return;
	vis[x][y]=1,Q[++f]=mp(x,y);
}
bool bfs(int L){	//用BFS判断是否联通，事实上可以用MST优化
	memset(vis,0,sizeof(vis));vis[n][1]=1;
	f=1,w=0;Q[1]=mp(n,1);
	while (f>w){
		w++;
		int x=Q[w].fi,y=Q[w].se;
		Upd(x,y-1);
		Upd(x,y+1);
		for (int i=-L;i<=L;i++) Upd(x+i,y);
	}
	return vis[tx][ty];
}

class ArcadeManao{
public:
	int shortestLadder(Vs level,int tx,int ty){
		::tx=tx;::ty=ty;
		n=level.size();
		m=level[0].length();
		For(i,1,n+1){
			For(j,1,m+1) s[i][j]=level[i-1][j-1];
		}
		For(i,0,n){
			if (bfs(i)) return i;	//枚举答案
		}
	}
} T;