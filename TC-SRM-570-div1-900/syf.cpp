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

#define n	35
#define m	10005
#define INF	(1 << 30)

int		N, M, C, S, T, tot;

int		A[n][n], Col[n][n], ID[n][n], IDr[n][n], IDc[n][n];

namespace	CostFlow{
	int		D= 1, st[m], Dis[m], V[m], pre[m], Q[m*10];
	
	struct	Lin{
		int v, c, f, next;
	}E[m];
	
	void	Link(int u, int v, int c, int f)	{
		E[++ D]= (Lin){v, c, f, st[u]};		st[u]= D;
		E[++ D]= (Lin){u, -c, 0, st[v]};	st[v]= D;
	}
	
	bool	SPFA()	{
		For(i, 1, C)	Dis[i]= INF;
		Dis[Q[1]= S]= 0;
		
		for (int l= 0, r= 1; l < r;)	{
			int u= Q[++ l];
			V[u]= 0;
			
			for (int i= st[u], v; i; i= E[i].next)
				if	(E[i].f && Dis[u] + E[i].c < Dis[v= E[i].v])	{
					Dis[v]= Dis[u] + E[i].c;
					pre[v]= i;
					
					if	(! V[v])	V[Q[++ r]= v]= 1;
				}
		}
		
		return	Dis[T] != INF;
	}
	
	PA		mincost()	{
		PA	ret= MK(0, 0);
		for (; SPFA(); )	{
			int	Min= INF;
			for (int x= T; x != S; x= E[pre[x]^1].v)	Min= min(Min, E[pre[x]].f);
			for (int x= T; x != S; x= E[pre[x]^1].v)
				E[pre[x]].f-= Min, E[pre[x]^1].f+= Min;
			
			ret.fi+= Min;
			ret.se+= Min * Dis[T];
		}
		return	ret;
	}
};

class	CurvyonRails{
	public:
		int 	getmin(vector <string> field){	//构图跑费用流即可
			N= field.size();
			M= field[0].length();
			
			For(i, 1, N)	For(j, 1, M)	{
				if	(field[i-1][j-1] == 'w')	Col[i][j]= -1;
				else	{	//奇偶染色
					tot++;
					Col[i][j]= (i+j) & 1;
					A[i][j]= field[i-1][j-1] == 'C';
					
					ID[i][j]= ++C;
					IDr[i][j]= ++C;
					IDc[i][j]= ++C;
				}
			}
			
			S= ++C;
			T= ++C;
			
			using namespace	CostFlow;
			
			For(i, 1, N)	For(j, 1, M){	//拆点连边
				if	(Col[i][j] == 0)	{
					Link(S, ID[i][j], 0, 2);
					
					if	(A[i][j])	{
						Link(ID[i][j], IDr[i][j], 0, 1);
						Link(ID[i][j], IDr[i][j], 1, 1);
						Link(ID[i][j], IDc[i][j], 0, 1);
						Link(ID[i][j], IDc[i][j], 1, 1);
					}	else	{
						Link(ID[i][j], IDr[i][j], 0, 2);
						Link(ID[i][j], IDc[i][j], 0, 2);
					}
				}
				lf	(Col[i][j] == 1)	{
					Link(ID[i][j], T, 0, 2);
					
					if	(A[i][j])	{
						Link(IDr[i][j], ID[i][j], 0, 1);
						Link(IDr[i][j], ID[i][j], 1, 1);
						Link(IDc[i][j], ID[i][j], 0, 1);
						Link(IDc[i][j], ID[i][j], 1, 1);
					}	else	{
						Link(IDr[i][j], ID[i][j], 0, 2);
						Link(IDc[i][j], ID[i][j], 0, 2);
					}
				}
			}
			
			For(i, 1, N)	For(j, 1, M-1)	{
				if	(Col[i][j] == -1 || Col[i][j+1] == -1)	continue;
				
				if	(Col[i][j] == 0)	Link(IDr[i][j], IDr[i][j+1], 0, 1);
					else	Link(IDr[i][j+1], IDr[i][j], 0, 1);
			}
			
			For(i, 1, N-1)	For(j, 1, M)	{
				if	(Col[i][j] == -1 || Col[i+1][j] == -1)	continue;
				
				if	(Col[i][j] == 0)	Link(IDc[i][j], IDc[i+1][j], 0, 1);
					else	Link(IDc[i+1][j], IDc[i][j], 0, 1);
			}
			
			PA	ret= mincost();
			
			if	(ret.fi != tot)	return	-1;
			return	ret.se;
		}
};