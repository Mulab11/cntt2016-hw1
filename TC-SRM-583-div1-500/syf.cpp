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

struct Edge{
	int y,z,nxt;
} E[N*2];
int las[N],f[N][2],g[2];
int cnt,n;

void Upd(int &x,int y){
	x=min(x,y);
}
void Link(int x,int y,int z){
	E[cnt]=(Edge){y,z,las[x]};las[x]=cnt++;
	E[cnt]=(Edge){x,z,las[y]};las[y]=cnt++;
}
void dfs(int x,int fa){	//树形dp，F[i][j]表示i这个子树，j这个点有没有向上的树边
	f[x][0]=0;
	f[x][1]=oo;
	for (int i=las[x],y;~i;i=E[i].nxt)
		if ((y=E[i].y)!=fa){
			dfs(y,x);
		}
	for (int i=las[x],y,z;~i;i=E[i].nxt)	//枚举子树，随便转移
		if ((y=E[i].y)!=fa){
			g[0]=g[1]=oo;
			z=E[i].z;
			if (z==2){
				For(a,0,2) For(b,0,2) Upd(g[(a+b)&1],f[x][a]+f[y][b]);
			} else{
				For(a,0,2) For(b,0,2) Upd(g[(a+b+(b&1^z))&1],f[x][a]+f[y][b]+(b&1^z));
			}
			For(a,0,2) f[x][a]=g[a];
		}
}

class TurnOnLamps{
public:
	int minimize(Vi V,string s,string t){
		memset(las,-1,sizeof(las));
		n=V.size()+1;
		For(i,0,n-1){
			Link(V[i],i+1,t[i]=='0'?2:(s[i]==t[i]?0:1));
		}
		dfs(0,-1);
		return min(f[0][0]/2,(f[0][1]+1)/2);
	}
} T;