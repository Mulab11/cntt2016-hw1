// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
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

const int mo=1234567891;

#define clr(a) memset(a,0,sizeof a)
#define cpy(a,b) memcpy(a,b,sizeof a)

LL H;
int idx,node,K,C,a[55],Maps[11111],PP[555],key[555],A[555],B[555],T[555][555],sky[555][555],ID[555][55];

vector<pair<int,PII> > li[555];

inline void inc(int &x,int y){x=(1ll*x+y)%mo;}

inline void mul(){//自乘
	cpy(T,sky);clr(sky);
	For(i,1,node)For(k,1,node)if(T[i][k])
		For(j,1,node)if(T[k][j])
			inc(sky[i][j],1ll*T[i][k]*T[k][j]%mo);
}

inline void prod(){//左乘
	cpy(B,A);clr(A);
	For(i,1,node)For(k,1,node)if(sky[i][k])
		inc(A[i],1ll*sky[i][k]*B[k]%mo);
}

inline int HASH(int *a){
	int tmp=0;
	For(i,1,4)tmp=(tmp*5)+a[i];
	if(!Maps[tmp]){
		Maps[tmp]=++idx;
		key[idx]=int(a[1]==a[2])+(a[2]==a[4])+(a[1]==a[3])+(a[3]==a[4]);//hash
	}
	return Maps[tmp];
}

inline int ha(int *a){
	int b[5],C[9],_=0;
	For(i,1,8)C[i]=0;
	For(i,1,4)if(!C[a[i]])C[a[i]]=++_;
	For(i,1,4)b[i]=C[a[i]];//最小表示
	return HASH(b);
}

void dfs(int s,int cur,int con){//第s个，用了cur种颜色，方案为con
	if(s>8){
		int u=ha(a),v=ha(a+4),tmp=key[v];//hash前后两半
		For(i,1,4)tmp+=(a[i]==a[i+4]);//相同颜色的对数
		li[u].pb(mk(v,PII{tmp,con}));//连边
		return;
	}
	For(i,1,cur){
		a[s]=i;
		if(s==4)PP[ha(a)]=con;//方案数
		dfs(s+1,cur,s==4?1:con);
	}
	if(cur<C){
		a[s]=cur+1;
		if(s==4)PP[ha(a)]=1ll*con*(C-cur)%mo;//方案数
		dfs(s+1,cur+1,s==4?1:1ll*con*(C-cur)%mo);
	}
}

inline int Main(){
	dfs(1,0,1);//搜最小表示
	For(i,1,idx)For(j,0,K)ID[i][j]=++node;//状态hash
	For(u,1,idx)for(auto it:li[u]){
		int v=it.x,k=it.y.x,c=it.y.y;
		For(j,0,K-k)inc(sky[ID[v][j+k]][ID[u][j]],c);//转移
	}
	++node;
	For(i,1,node)inc(sky[node][i],1);//sum
	For(i,1,idx)if(key[i]<=K)A[ID[i][key[i]]]=PP[i];//初值
	for(;H;H>>=1,mul())if(H&1)prod();//矩乘
	return A[node];
}

struct TheBrickTowerHardDivOne{
	int find(int C, int K, long long H){
		::C=C;::K=K;::H=H;
		return Main();
	}
};