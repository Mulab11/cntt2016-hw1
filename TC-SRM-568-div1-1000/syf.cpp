//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define n	55

int		N, M, C, ND, A[n], L[n], R[n];

namespace	Case1{	//暴搜
	int		V[n], F[n], D[n];
	
	int		Get(int u){
		if	(F[u] == u)	return	u;
		int t= Get(F[u]);
		
		D[u]^= D[F[u]];
		return	F[u]= t;
	}
	
	bool	check(){	//用并查集判断
		For(i, 1, N)	F[i]= i, D[i]= 0;
		
		For(i, 1, N)	For(j, i+1, N)
			if	(! (L[i] >= R[j] || L[j] >= R[i] || (L[i] <= L[j] && R[j] <= R[i]) || (L[j] <= L[i] && R[i] <= R[j])))	{
				int fx= Get(i), fy= Get(j);
				
				if	(fx == fy)	{
					if	(D[i]^D[j]^1)	return	0;
				}	else	{
					F[fx]= fy;
					D[fx]= D[i]^D[j]^1;
				}
			}
		
		return	1;		
	}
	
	bool	DFS(int i)	{
		if	(i > C)	return	check();
		
		if	(V[i])	return	DFS(i+1);
		
		For(j, i+1, C)	if	(! V[j]){
			V[j]= 1;
			
			ND++;
			L[ND]= A[i];
			R[ND]= A[j];
			
			if	(DFS(i+1))	return	1;
			
			ND--;
			V[j]= 0;
		}
		return	0;
	}
	
	bool	Main(){
		return	DFS(1);
	}
};

namespace	Case2{
	int		U[n], D[n], F[n], S[n];
	
	int		Get(int u){
		if	(F[u] == u)	return	u;
		int t= Get(F[u]);
		
		S[u]^= S[F[u]];
		return	F[u]= t;
	}
	
	bool	Merge(int l, int r, int c)	{	//用并查集判断
		int fx= Get(l-1), fy= Get(r);
		
		if	(fx == fy)	{
			if	(S[l-1] ^ S[r] ^ c)	return	0;
		}	else	{
			F[fx]= fy;
			S[fx]= S[l-1] ^ S[r] ^ c;
		}
		
		return	1;
	}
	
	bool	check()	{
		For(i, 1, *U)	For(j, i+1, *U){
			int l1= L[U[i]], r1= R[U[i]], l2= L[U[j]], r2= R[U[j]];	
			if	(l1 < l2 && l2 < r1 && r2 > r1)	return	0;
		}
		
		For(i, 1, *D)	For(j, i+1, *D){
			int l1= L[D[i]], r1= R[D[i]], l2= L[D[j]], r2= R[D[j]];	
			if	(l1 < l2 && l2 < r1 && r2 > r1)	return	0;
		}
		
		For(i, 0, M)	F[i]= i, S[i]= 0;
		
		For(i, 1, *U)	{
			int l= L[U[i]], r= R[U[i]];
			if	(! Merge(l, r, 0))	return	0;
			if	(! Merge(l, l, 1))	return	0;
			if	(! Merge(r, r, 1))	return	0;
		}
		
		For(i, 1, *D)	{
			int l= L[D[i]], r= R[D[i]];
			if	(! Merge(l, r, (r-l+1)&1))	return	0;
			if	(! Merge(l, l, 0))	return	0;
			if	(! Merge(r, r, 0))	return	0;
		}
		
		if	(Merge(1, M, 0))	return	1;
		return	0;
	}
	
	bool	DFS(int d)	{
		if	(d > ND)	return	check();
		
		U[++ *U]= d;
		if	(DFS(d+1))	return	1;
		-- *U;
		
		D[++ *D]= d;
		if	(DFS(d+1))	return	1;
		-- *D;
		
		return	0;
	}
	
	bool	Main(){
		return	DFS(1);
	}
};

class	DisjointSemicircles{
	public:
		string getPossibility(vector <int> lab)	{
			M= lab.size();
			N= M >> 1;
			
			For(i, 1, M)	if	(lab[i-1] != -1)
				For(j, i+1, M)	if	(lab[j-1] == lab[i-1])	{
					ND++;
					L[ND]= i;
					R[ND]= j;
				}
			
			For(i, 1, M)	if	(lab[i-1] == -1)	A[++ C]= i;
			
			if	(C <= 12)	return	Case1::Main() ? "POSSIBLE" : "IMPOSSIBLE";	//分情况选择过程求解答案
			return	Case2::Main() ? "POSSIBLE" : "IMPOSSIBLE";
		}
}GTW;