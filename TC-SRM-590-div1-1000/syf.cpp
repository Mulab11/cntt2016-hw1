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

#define n	45
#define m	500005
#define INF	(1 << 29)

int		N, C, ID[n][n];

int		A[n], F[n][n];

namespace	MaxFlow{	//网络流
	int		D= 1, S, T, st[m], Q[m], Dis[m];
	
	struct	Lin{
		int v, next, f;
	}E[m];
		
	void	Link(int u, int v, int f){
		E[++D]= (Lin){v, st[u], f};	st[u]= D;
		E[++D]= (Lin){u, st[v], 0};	st[v]= D;
	}
	
	bool	BFS(){
		For(i, 1, C)	Dis[i]= -1;
		Dis[Q[1]= S]= 0;
		
		for (int l= 0, r= 1; l < r;)	{
			int u= Q[++l];
			for	(int i=st[u], v; i; i= E[i].next)
			if	(E[i].f && Dis[v= E[i].v] == -1){
				Dis[Q[++r]= v]= Dis[u] + 1;
				if	(v == T)	return	1;
			}
		}
		
		return	0;
	}
	
	int		DFS(int u, int Lim){
		if	(u == T)	return	Lim;
		
		int	ret= 0;
		for (int i= st[u], v; i; i= E[i].next)
		if	(E[i].f && Dis[u] + 1 == Dis[v= E[i].v]){
			int	t= DFS(v, min(Lim-ret, E[i].f));
			
			if	(t)	{
				E[i].f-= t;
				E[i^1].f+= t;
				ret+= t;
				if	(ret == Lim)	break;
			}	else	Dis[v]= -1;
		}
		
		return	ret;
	}
	
	int		Flow(){
		int	ret= 0;
		for (; BFS(); )	ret+= DFS(S, INF);
		return	ret;
	}
};

class	FoxAndCity{
	public:
		int 	minimalCost(vector <string> linked, vector <int> want){	//构图跑最小割
			using namespace	MaxFlow;
			
			N= linked.size();
			For(i, 1, N)	For(j, 1, N)	if	(i != j)
				F[i][j]= linked[i-1][j-1] == 'Y' ? 1 : INF;
			
			For(k, 1, N)	For(i, 1, N)	For(j, 1, N)
				F[i][j]= min(F[i][j], F[i][k] + F[k][j]);
			
			For(i, 1, N)	A[i]= want[i-1];
			
			For(i, 1, N)	For(j, 0, N)	ID[i][j]= ++C;
			S= ++C;
			T= ++C;
			
			For(i, 1, N)	{	//对于每一个物品，拆成N个点，连边；用连INF边来限制顺序
				Link(S, ID[i][0], INF);
				Link(ID[i][N], T, INF);
				
				if	(i == 1)	Link(ID[i][0], ID[i][1], A[i]*A[i]);
					else	Link(ID[i][0], ID[i][1], INF);
				
				For(j, 1, N-1)	{
					if	(j <= F[1][i])	Link(ID[i][j], ID[i][j+1], (j-A[i])*(j-A[i]));
						else	Link(ID[i][j], ID[i][j+1], INF);
				}
			}
			
			For(i, 1, N)	For(j, i+1, N)	if	(F[i][j] == 1){
				For(k, 1, N-1)	Link(ID[i][k], ID[j][k-1], INF);
				For(k, 1, N-1)	Link(ID[j][k], ID[i][k-1], INF);
			}
			
			return	Flow();
		}
};