#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i,x,y)  for(int i=(int)x;i<=(int)y;i++)
#define For(i,x,y)  for(int i=(int)x;i< (int)y;i++)
#define PER(i,x,y)  for(int i=(int)x;i>=(int)y;i--)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define md ((L+R)/2)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
const	int P=1e9+7;
const	int inf=1e9;
const	ll Inf=1e16;
const	int N=1005;

inline int IN(){
	char ch=getchar();int x=0,f=0;
	for(;ch<48||ch>57;ch=getchar()) f=ch=='-';
	for(;ch>=48&&ch<=57;ch=getchar()) x=(x<<1)+(x<<3)+ch-48;
	return f?(-x):x;
}

int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int n,f[N],g[N];
bool G[N][N];

void DFS(int x,int y){
	int sn=0,sm=0,las=0;
	REP(v, 1, n) if(G[x][v]){
		if(v == y)continue;
		DFS(v, x);
		sm += f[v];
		sn ++;
		las = v;
	}
	if(!sn){
		f[x] = 1;
		g[x] = 0;
	}else
	if(sn==1){
		f[x] = sm;
		g[x] = g[las];
	}else{
		f[x] = sm;
		g[x] = inf;
		REP(v, 1, n) if(G[x][v]){
			if(v == y) continue;
			f[x] = min(f[x], sm - f[v] + g[v]);	
		}
	}
}

struct TPS{
	int minimalBeacons(vector<string> linked){
		n=linked.size();
		if(n == 1) return 0;
		REP(i,1,n) REP(j,1,n) if(linked[i-1][j-1]=='Y') G[i][j]=1;
		int ans=inf;
		REP(rt,1,n){
			memset(f,0x3f,sizeof f);
			memset(g,0x3f,sizeof g);
			DFS(rt,0);
			ans=min(ans,min(f[rt],g[rt])+1);
		}
		return ans;
	}
}str;