// by ¦Î

#include <bits/stdc++.h>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define sqr(x) (x)*(x)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> PDD;
typedef vector<int> VI;
typedef vector<PII> VII;

struct RockPaperScissors{
	int N;
	db F[55][55][55],g[55][55][55];
	db bestScore(VI A,VI B,VI C){
		N=A.size();
		// package
		***F=1;
		rep(i,0,N)
		for(int a=N;~a;--a)
		for(int b=N-a;~b;--b)
		for(int c=N-a-b;~c;--c){
			if(a)F[a][b][c]+=F[a-1][b][c]*A[i];
			if(b)F[a][b][c]+=F[a][b-1][c]*B[i];
			if(c)F[a][b][c]+=F[a][b][c-1]*C[i];
		}
		for(int a=N;~a;--a)
		for(int b=N-a;~b;--b)
		for(int c=N-a-b;~c;--c)
		if(a+b+c<N && F[a][b][c]>1e-12){
			// select one and place it at end
			db	p1=F[a+1][b][c]*(a+1),p2=F[a][b+1][c]*(b+1),p3=F[a][b][c+1]*(c+1),
				val=max(max(p1*3+p2,p2*3+p3),p3*3+p1);
			g[a][b][c]=(val+p1*g[a+1][b][c]+p2*g[a][b+1][c]+p3*g[a][b][c+1])/(p1+p2+p3);
		}return ***g;
	}
}MAIN;