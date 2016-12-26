// by ξ
// program sky  :)

#include <vector>
#include <complex>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef complex<db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+7;

int root,m,n,fa[55],pw[11],F[55][6666],go[6666][55],a[11],b[11];
bool bo[55],ok[88][88],can[6666];
string s[55];

VI li,g,tr[6666],Ed[55];

inline int bit(int x,int k){return x/pw[k]%3;}
inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

void dfs(int u){
	// 拿处理好的转移进行转移
	F[u][0]=1;
	for(int v:Ed[u]){
		dfs(v);
		for(int x:li)
			for(int y:tr[x])
				F[u][x]=(F[u][x]+1ll*F[u][y]*F[v][x-y])%mo;
	}
	// 枚举当前串选不选
	if(u^root)
	dto(i,pw[m]-1,0)if(F[u][i])
		for(int j:g)if(go[i][j]!=-1)inc(F[u][go[i][j]],F[u][i]);
}

int Main(){
	*pw=1;For(i,1,8)pw[i]=pw[i-1]*3;
	// 建树
	root=0;
	For(i,1,n){
		int ma=0,u=root;
		For(j,1,n)if(i^j && s[j].length()<s[i].length()){
			int L=0;
			for(;L<s[j].length() && s[i][L]==s[j][L];++L);
			if(L==s[j].length() && L>ma)ma=L,u=j;
		}
		Ed[fa[i]=u].pb(i);
	}
	rep(i,0,m)bo[a[i]]=bo[b[i]]=1;
	For(i,1,n)if(bo[i])g.pb(i);
	// 预处理O(3^m)合法状态及O(5^m)合法转移
	rep(i,0,pw[m]){
		bool flag=1;
		for(int j:g){
			bool f1=0,f2=0;
			rep(k,0,m){
				if(a[k]==j){
					if(bit(i,k)==2)f1=1;else f2=1;
				}
				if(b[k]==j){
					if(bit(i,k)==0)f2=1;else f1=1;
				}
				if(f1 && f2){
					flag=0;
					break;
				}
			}
			if(!flag)break;
		}
		if(flag)li.pb(i),can[i]=1;
	}
	for(int x:li){
		for(int i:g){
			int y=x;bool flag=1;
			rep(j,0,m){
				if(b[j]==i)
					if(bit(x,j)==0)y+=pw[j];else{flag=0;break;}
				else if(a[j]==i)
					if(bit(x,j)==1)y+=pw[j];else{flag=0;break;}
			}
			if(flag)go[x][i]=y,assert(can[y]);else go[x][i]=-1;
		}
	}
	rep(i,0,pw[4])rep(j,0,pw[4]){
		ok[i][j]=1;
		rep(k,0,4)
			ok[i][j]=ok[i][j] && (bit(i,k)==0 || bit(j,k)==0);
	}
	for(int x:li)for(int y:li)if(y)
		if(ok[x%pw[4]][y%pw[4]] && ok[x/pw[4]][y/pw[4]])
			tr[x+y].pb(x);
	reverse(ALL(li));
	// 树DP
	dfs(root);
	int res=F[root][pw[m]-1],tot=0;
	// 其他位置乱选
	For(i,1,n)if(!bo[i])res=1ll*res*(++tot)%mo;
	return res;
}

struct SimilarNames{
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		n=names.size();
		For(i,1,n)s[i]=names[i-1];
		rep(i,0,info1.size())if(info1[i]^info2[i])a[m]=info1[i]+1,b[m]=info2[i]+1,++m;
		return Main();
	}
};