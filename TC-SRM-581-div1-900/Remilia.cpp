// by ξ
// program sky  :)

#include <vector>
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

const int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int n,m,col[15][2],A[15][15],B[15][15];

void upd(int &x,int y){
	if(x==-1 || y<x)x=y;
}

void compo(int i,int j,bool c){
	// 两种操作
	if(c)B[i][j]^=1;
	rep(d,0,4){
		int x=i+dir[d][0],y=j+dir[d][1];
		if(x && x<=n && y && y<=m)B[x][y]^=1;
	}
}

int gao(int r){
	if(r==n+1){
		For(j,1,m)if(B[n][j])return -1;
		return 0;
	}
	// 取出一定要变的位置，并且决定其类型
	int flag=-1,res=-1,tmp=0;
	For(j,1,m)if(B[r-1][j]){
		++tmp;
		if(col[j][0]){
			if(flag==-1)flag=0;
			else if(flag==1)return -1;
		}
		if(col[j][1]){
			if(flag==-1)flag=1;
			else if(flag==0)return -1;
		}
	}
	// 搜索
	VI li;
	if(flag==0 || flag==-1){
		li.resize(0);
		For(j,1,m)if(B[r-1][j])compo(r,j,0),++col[j][0],li.pb(j);
		int x=gao(r+1);
		if(x>=0)upd(res,tmp+x);
		for(int j:li)compo(r,j,0),--col[j][0];
	}
	if(flag==1 || flag==-1){
		li.resize(0);
		For(j,1,m)if(B[r-1][j])compo(r,j,1),++col[j][1],li.pb(j);
		int x=gao(r+1);
		if(x>=0)upd(res,tmp+x);
		for(int j:li)compo(r,j,1),--col[j][1];
	}
	return res;
}

int Main(){
	int Ans=-1;
	// 枚举第一行的情况
	rep(mask,0,1<<m){
		int tmp=0,x;
		For(i,1,n)For(j,1,m)B[i][j]=A[i][j];
		For(i,1,m)if(mask>>i-1&1)compo(1,i,0),++col[i][0],++tmp;
		x=gao(2);
		if(~x)upd(Ans,tmp+x);
		For(i,1,m)if(mask>>i-1&1)--col[i][0];

		For(i,1,n)For(j,1,m)B[i][j]=A[i][j];
		For(i,1,m)if(mask>>i-1&1)compo(1,i,1),++col[i][1];
		x=gao(2);
		if(~x)upd(Ans,tmp+x);
		For(i,1,m)if(mask>>i-1&1)--col[i][1];
	}
	return Ans;
}

struct YetAnotherBoardGame{
	int minimumMoves(vector<string> bd){
		n=SZ(bd);m=SZ(bd[0]);
		For(i,1,n)For(j,1,m)A[i][j]=bd[i-1][j-1]=='W';
		return Main();
	}
};