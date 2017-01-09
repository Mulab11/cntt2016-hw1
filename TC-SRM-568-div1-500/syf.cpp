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

#define n	105
#define m	5005
#define INF	(1 << 30)
#define P	1000000007

int		N, M, C, D, A[n], B[n], F[n], st[n];

struct	Lin{
		int v, c, next;
}E[m];

void	Link(int u, int v, int c)	{
		E[++ D]= (Lin){v, c, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, c, st[v]};	st[v]= D;
}

int		Get(int u)	{
		return	F[u] == u ? u : F[u]= Get(F[u]);
}

bool	DFS(int u, int s)	{	//DFS暴搜更新其他变量的值
		if	(B[u] != INF)	{
			if	(B[u] != s)	return	0;
			return	1;
		}
		B[u]= s;
		
		for (int i= st[u]; i; i= E[i].next)	
			if	(! DFS(E[i].v, E[i].c - s))	return	0;
		
		return	1;
}

class	EqualSums{
	public:
		int		count(vector <string> board){
			N= board.size();
			M= N << 1;
			
			For(i, 1, M)	F[i]= i;	//并查集
			
			For(i, 1, N)	For(j, 1, N)	//将有关的边全部连上
				if	(board[i-1][j-1] != '-')	{
					Link(i, N+j, board[i-1][j-1] - '0');
					
					int fx= Get(i), fy= Get(N+j);
					if	(fx != fy)	F[fx]= fy;
				}
			
			int	Ans1= 1, Ans2= 1;
			For(i, 1, M)	if	(Get(i) == i){	//对于每一个连通块计算答案
				C= 0;
				For(j, 1, M)	if	(Get(j) == i)	A[++ C]= j;
				
				int	ret1= 0, ret2= 0;
				For(s, 0, 9)	{	//枚举其中一个变量的值
					For(j, 1, C)	B[A[j]]= INF;
					if	(! DFS(i, s))	continue;
					
					int	flag= 1;
					For(j, 1, C)	if	(B[A[j]] < 0)	flag= 0;
					if	(! flag)	continue;
					
					int	zero= 1;
					For(j, 1, C)	if	(A[j] <= N && B[A[j]] == 0)	zero= 0;
					
					ret1++;
					ret2+= zero;
				}
				
				Ans1= 1ll*Ans1*ret1%P;
				Ans2= 1ll*Ans2*ret2%P;
			}
			
			return	(Ans1 - Ans2 + P) % P;
		}
};