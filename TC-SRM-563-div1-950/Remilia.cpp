// by ξ
// program sky  :)

#include <vector>
#include <bitset>
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
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+9,dx[]={0,0,1,-1},dy[]={1,-1,0,0};

int n,m,dd,node,ans,fa[1666],sz[1666],pw[1666],ID[44][44],B[44][44],g[1280000];
bool ok[1280000];
int li[1280000][9];

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}
inline void dec(int &x,int y){if((x-=y)<0)x+=mo;}

int get(int x){return x^fa[x]?fa[x]=get(fa[x]):x;}//冰茶几

inline void uni(int u,int v){
	u=get(u);v=get(v);
	if(u^v)fa[u]=v,sz[v]+=sz[u];//合并冰茶几
}

inline void pret(){
	int tot=0;For(i,1,n)For(j,1,m)tot+=B[i][j];
	*pw=1;For(i,1,n*m)pw[i]=pw[i-1]*2%mo;
	ans=pw[tot];
}

inline int tr(int i,int j,int d){
	int ii=i+dx[d],jj=j+dy[d];
	if(!ii || ii>n || !jj || jj>m)return 0;
	if(!B[ii][jj])return ID[i][j];
	return ID[ii][jj];//移动一步
}

inline int dian(int i,int j){
	return (i-1)*(2*node-i)/2+j-i;//hash
}

inline int Main(){
	pret();
	For(i,1,n)For(j,1,m)if(B[i][j])ID[i][j]=++node;
	dd=node*(node-1)/2;
	For(i,1,n)For(j,1,m)if(B[i][j])
		For(k,1,n)For(l,1,m)if(B[k][l] && ID[i][j]<ID[k][l]){
			rep(d,0,4){
				int u=tr(i,j,d),v=tr(k,l,d);
				if(u==v)continue;
				if(u>v)swap(u,v);
				if(!u || !v){
					ok[dian(ID[i][j],ID[k][l])]=1;
					break;
				}else li[dian(u,v)][++*li[dian(u,v)]]=dian(ID[i][j],ID[k][l]);//如果状态可达，就连个反边搞点事情
			}
		}
	For(i,1,dd)if(ok[i])g[++*g]=i;
	for(int i=1;i<=*g;++i)
		For(j,1,*li[g[i]])if(!ok[li[g[i]][j]])ok[g[++*g]=li[g[i]][j]]=1;//renew状态是否合法
	For(i,1,node)fa[i]=i,sz[i]=1;
	For(i,1,node)For(j,i+1,node)if(!ok[dian(i,j)])uni(i,j);//等价类搞出来
	For(i,1,node)if(get(i)==i)dec(ans,pw[sz[i]]-1);//减掉不合法的
	return ans-1;
}

struct CoinsGame{
	int ways(vector<string> bb){
		n=SZ(bb);m=SZ(bb[0]);
		For(i,1,n)For(j,1,m)B[i][j]=bb[i-1][j-1]=='.';
		return Main();
	}
};