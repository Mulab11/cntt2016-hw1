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

int		N, D, st[n], F[n], G[n];

struct	Lin{
		int v, next;
}E[n << 1];

void	Link(int u, int v)	{
		E[++ D]= (Lin){v, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, st[v]};	st[v]= D;
}

void	DFS(int u, int f)	{
		int	d= 0;
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	DFS(v, u), d++;
		
		if	(! d)	{	//特判叶子
			F[u]= 1;
			G[u]= 0;
		}
		lf	(d == 1)	{	//链或者分叉
			for (int i= st[u], v; i; i= E[i].next)
				if	((v= E[i].v) != f)	{
					if	(G[v] == 0)	G[u]= 0, F[u]= 1;
						else	G[u]= 1, F[u]= F[v];
				}
		}
		else	{	//随便转移一下
			int sum= 0;
			G[u]= 1;
			
			for (int i= st[u], v; i; i= E[i].next)
				if	((v= E[i].v) != f)	sum+= F[v];
			F[u]= sum;
			
			for (int i= st[u], v; i; i= E[i].next)
				if	((v= E[i].v) != f && G[v] == 0)	F[u]= min(F[u], sum-1);
		}
}

class	TPS{
	public:
		int 	minimalBeacons(vector <string> linked){
			N= linked.size();
			For(i, 1, N)	For(j, i+1, N)
				if	(linked[i-1][j-1] == 'Y')	Link(i, j);
			
			if	(N == 1)	return	0;
			
			int	Ans= N;
			For(i, 1, N)	{	//枚举根，进行树形DP
				DFS(i, 0);
				if	(G[i] == 0)	Ans= 1;
					else	Ans= min(Ans, F[i] + 1);
			}
			
			return	Ans;
		}
};