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

#define n	205
#define INF	(1 << 30)

int		N, Ans, MinW, MaxW, Num[n];

int		M, X[n], Y[n], w[n][n];

int		Dep[n];

namespace	Flow{		//网络流判断合法性。
	int		S, T, D, st[n], Dis[n], Q[n];
	
	struct	Lin{
		int	v, f, next;
	}E[n];
	
	void	Link(int u, int v, int f){
		E[++ D]= (Lin){v, f, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, 0, st[v]};	st[v]= D;
		
	//	printf("** %d %d %d\n", u, v, f);
	}
	
	bool	BFS(){
		For(i, 1, T)	Dis[i]= -1;
		Dis[Q[1]= S]= 0;
		
		for (int l= 0, r= 1; l < r; ){
			int u= Q[++ l];
			
			for (int i= st[u], v; i; i= E[i].next)
				if	(E[i].f && Dis[v= E[i].v] == -1)	{
					Dis[Q[++ r]= v]= Dis[u] + 1;
					if	(v == T)	return 1;
				}
		}
		
		return	0;
	}
	
	int		DFS(int u, int Lim){
		if	(u == T)	return	Lim;
		int ret= 0;
		
		for (int i= st[u], v; i; i= E[i].next)
			if	(E[i].f && Dis[v= E[i].v] == Dis[u] + 1)	{
				int t= DFS(v, min(E[i].f, Lim-ret));
				
				if	(t)	{
					E[i].f-= t;
					E[i^1].f+= t;
					ret+= t;
					
					if	(ret == Lim)	break;
				}	else	Dis[v]= -1;
			}
		
		return	ret;
	}
	
	int		Dinic(){	//Dinic
		int ret= 0;
		for (; BFS(); )	ret+= DFS(S, INF);
		return	ret;
	}
	
	bool	Main(){	//构图
		S= N+1;
		T= N+2;
		
		For(d, 1, N)	{
		//	puts("  #");
			For(i, 1, T)	st[i]= 0;
			D= 1;
			
			For(i, 1, N)	if	(Dep[i] == d-1)
				For(j, 1, N)	if	(Dep[j] == d)
					if	(w[i][j])	Num[i]--, Num[j]--;
			
			int	tot= 0;
			For(i, 1, N)	if	(Dep[i] == d-1)	Link(S, i, Num[i]);
			For(i, 1, N)	if	(Dep[i] == d)	Link(i, T, Num[i]), tot+= Num[i];
			
			For(i, 1, N)	if	(Dep[i] == d-1)
				For(j, 1, N)	if	(Dep[j] == d)
					if	(w[i][j])	Link(i, j, INF);
			
			int	flag= 1;
			if	(Dinic() != tot)	flag= 0;
				
			For(i, 1, N)	if	(Dep[i] == d-1)
				For(j, 1, N)	if	(Dep[j] == d)
					if	(w[i][j])	Num[i]++, Num[j]++;
				
			if	(! flag)	return	0;
		}
		
		return	1;
	}
};

bool	check(){	//搜索过程中粗判
		static	int	Path[n][n];
		
		For(i, 1, N)	For(j, 1, N)	Path[i][j]= w[i][j];
		For(k, 1, N)	For(i, 1, N)	For(j, 1, N)
			if	(Path[i][k] && Path[k][j])	Path[i][j]= 1;
	
		For(i, 1, N)	if	(Path[i][i])	return	0;
	
		For(i, 1, N)	For(j, 1, N)	For(k, 1, N)
			if	(Path[i][j] && Path[j][k] && w[i][k])	return	0;
		
		return	1;
}

bool	Right(){	//验证是否合法
		static	int	Q[n], Deg[n];
		
		For(i, 1, N)	Dep[i]= Deg[i]= 0;
		For(i, 1, N)	For(j, 1, N)	Deg[i]+= w[j][i];
		
		*Q= 0;
		For(i, 1, N)	if	(! Deg[i])	Q[++ *Q]= i;
		
		for (int i= 1; i <= *Q; i++)	{
			int u= Q[i];	
			For(v, 1, N)	if	(w[u][v])
				if	(! (--Deg[v]))	Q[++ *Q]= v, Dep[v]= Dep[u] + 1;
		}
		
		For(i, 1, N)	For(j, 1, N)
			if	(w[i][j] && Dep[j] != Dep[i] + 1)	return	0;
	
		//用拓扑排序粗判
	
		For(d, 1, N)	{
			For(i, 1, N)	if	(Dep[i] == d-1)
				For(j, 1, N)	if	(Dep[j] == d)
					if	(w[i][j])	Num[i]--, Num[j]--;
			
			int	flag= 1;
			For(i, 1, N)	if	(Num[i] < 0)	flag= 0;	
			
			For(i, 1, N)	if	(Dep[i] == d-1)
				For(j, 1, N)	if	(Dep[j] == d)
					if	(w[i][j])	Num[i]++, Num[j]++;
			
			if	(! flag)	return	0;
		}
		
		//给拓扑图分层
		
		return	1;
}

int		Cal(){	//用状态Dp计算可行的拓扑序
		static	int	U= (1<<N)-1, F[n];
		
		For(i, 0, U)	F[i]= 0;
		F[0]= 1;
		
		For(s, 1, U)	{
			For(i, 1, N)	if	((1<<(i-1)) & s)	{
				int	flag= 1;
				For(j, 1, N)	if	(! ((1<<(j-1)) & s) && w[j][i])	flag= 0;
				if	(! flag)	continue;
				
				F[s]+= F[s ^ (1<<(i-1))];
			}
		}
		
		return	F[U];
}

void	DFS(int d)	{	//搜索出所有的拓扑图
		if	(! check())	return;
		if	(d > M)	{
			if	(! Right())	return;
			if	(! Flow::Main())	return;
			
			int t= Cal();
			Ans+= (MinW <= t && t <= MaxW);
			return;
		}
		
		w[X[d]][Y[d]]= 1;	//这条边是X-Y
		DFS(d+1);
		w[X[d]][Y[d]]= 0;
		
		w[Y[d]][X[d]]= 1;	//这条边是Y-X
		DFS(d+1);
		w[Y[d]][X[d]]= 0;
		
		DFS(d+1);	//不放
}

class	CosmicBlocks{
	public:
		int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)	{
			N= blockTypes.size();
			For(i, 1, N)	Num[i]= blockTypes[i-1];
			
			MinW= minWays;
			MaxW= maxWays;
			
			For(i, 1, N)	For(j, i+1, N)
				M++, X[M]= i, Y[M]= j;
			
			DFS(1);
			
			return	Ans;
		}
};