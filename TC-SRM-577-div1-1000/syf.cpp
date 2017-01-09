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
#define m	100005

#define INF	(1 << 30)

const	int	cx[]= {-1, 0, 0, 1}, cy[]= {0, -1, 1, 0};

int		N, M, C, A[n][n], ID[n][n];

namespace	MaxFlow{	//最大流
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

class	BoardPainting{
	public:
		int 	minimalSteps(vector <string> s)		{	//构图跑网络流
			N= s.size();
			M= s[0].length();
			For(i, 1, N)	For(j, 1, M)
				if	(s[i-1][j-1] == '#')	A[i][j]= 1, ID[i][j]= ++C;;
			
			using	namespace	MaxFlow;
			
			S= ++C;
			T= ++C;
			
			For(i, 1, N)	For(j, 1, M)
			if	(A[i][j])	{
				int	u= 0, v= 0;
				
				For(k, 0, 3)	{
					int x= i + cx[k], y= j + cy[k];
					
					if	(1 <= x && x <= N && 1 <= y && y <= M && A[x][y])	Link(ID[i][j], ID[x][y], 1);
						else	u+= (k == 1 || k == 2), v+= (k == 0 || k == 3);
				}
				
				Link(S, ID[i][j], u);
				Link(ID[i][j], T, v);
			}	//构图
			
			return	Flow() >> 1;
		}
};