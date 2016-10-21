// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
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

int odd,even,D,n,m,sz,bo[55][55],a[55][55],up[55][55],dn[55][55];

void gao(int i,int j){
	if(bo[i][j])return;
	++sz;
	bo[i][j]=1;
	For(p,1,m){
		int k=i;
		if(abs(i-k)+abs(j-p)<=D && a[k][p])gao(k,p);
		k=up[i-1][p];
		if(abs(i-k)+abs(j-p)<=D)gao(k,p);
		k=dn[i+1][p];
		if(abs(i-k)+abs(j-p)<=D)gao(k,p);
	}
	//找到每列离它最近的三个点，深搜
}

int Main(){
	For(j,1,m){
		up[0][j]=-10000;
		For(i,1,n)up[i][j]=a[i][j]?i:up[i-1][j];
		dn[n+1][j]=10000;
		dto(i,n,1)dn[i][j]=a[i][j]?i:dn[i+1][j];
	}
	For(i,1,n)For(j,1,m)if(a[i][j] && !bo[i][j]){
		//依次处理每个没有处理过的连通块
		sz=0;
		gao(i,j);
		if(sz&1)++odd;else ++even;
		//算出这个连通块的大小是奇数还是偶数
	}
	int A=0;
	if(odd)A=odd+even-1;else A=even;
	int re=1;
	for(;A--;)re=re*2%1000000007;
	return re-1;//因为是2的幂次，因此不会出现模P为0的情况
	//答案计算方式是2^(max(odd,1)+even-1)-1
}

struct GooseInZooDivOne{
	int count(vector <string> field, int dist){
		n=field.size();m=field[0].size();
		rep(i,0,n)rep(j,0,m)a[i+1][j+1]=field[i][j]=='v';
		D=dist;
		//读取数据
		return Main();
	}
};