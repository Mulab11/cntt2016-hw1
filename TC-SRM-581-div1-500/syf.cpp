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

const int N=300+19;

stringstream ss1,ss2;
Vi V1[N],V2[N];
int d1[N][N],d2[N][N],f1[N],f2[N],n;
db res;

void dfs1(int x,int fa,int s,int d){
	d1[s][x]=d;
	For(i,0,V1[x].size()) if (V1[x][i]!=fa) dfs1(V1[x][i],x,s,d+1);
}
void dfs2(int x,int fa,int s,int d){
	d2[s][x]=d;
	For(i,0,V2[x].size()) if (V2[x][i]!=fa) dfs2(V2[x][i],x,s,d+1);
}

class TreeUnion{
public:
	db expectedCycles(Vs tree1,Vs tree2,int K){
		ss1<<accumulate(tree1.begin(),tree1.end(),string());
		ss2<<accumulate(tree2.begin(),tree2.end(),string());
		for (int i=0,x;ss1>>x;i++){
			V1[x].pb(i+1);
			V1[i+1].pb(x);
		}
		for (int i=0,x;ss2>>x;i++){
			V2[x].pb(i+1);
			V2[i+1].pb(x);
			n=i+2;
		}
		For(i,0,n){
			dfs1(i,-1,i,0);
			dfs2(i,-1,i,0);	//DP预处理出树上所有长度为0-K的链ed个数
		}
		For(a,0,n) For(b,a+1,n) f1[d1[a][b]]++;
		For(c,0,n) For(d,0,n) if (c!=d) f2[d2[c][d]]++;
		for (int i=1;K-2-i>=1;i++){	//枚举两棵树的长度，计算方案数
			res+=1.0/n/(n-1)*f1[i]*f2[K-2-i];
		}
		return res;
	}
} T;