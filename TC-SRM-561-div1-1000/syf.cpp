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

#define m	305
#define n	2505

int		N, M, K, ID[m][m];

int		D, A[n], V[n], st[n], Dfn[n], Dis[n][n];

int		T, X[n], Y[n], siz[n], Count[n], gtw[n];

char	s[m][m];

DB		C[m][m], Ans[n];

struct	Lin{
		int v, next;
}E[n << 1];

void	Link(int u, int v)	{
		X[++ T]= u;
		Y[T]= v;
	
		E[++ D]= (Lin){v, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, st[v]};	st[v]= D;
}

void	DFS(int u, int f, int d, int g)	{	//预处理距离
		Dis[g][u]= d;
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	DFS(v, u, d+1, g);
}

void	DFS2(int u, int f)	{	//预处理DFS序
		Dfn[u]= ++*Dfn;
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	DFS2(v, u);
}

bool	Cmp(int a, int b)	{
		return	Dfn[a] < Dfn[b];
}

DB		Work1(){	//计算虚树的直径期望
		DB	ret= 0;
		For(i, 1, *A)	For(j, i+1, *A){
			int u= A[i], v= A[j], a= j-i-1, b= *A - a - 2;
			
			if	(a >= K-2)	ret+= Dis[u][v]*C[a][K-2];
			if	(b >= K-2)	ret+= Dis[u][v]*C[b][K-2];
		}
		
		return	ret / C[*A][K];
}


DB		Work3(){	//计算直径的期望
		DB	ret= 0;
		For(i, 1, *A)	For(j, i+1, *A)	{
			int u= A[i], v= A[j], d= Dis[u][v], cnt= 0;
			
			For(k, 1, *A)	{
				int w= A[k], a= Dis[w][u], b= Dis[w][v];
				
				if	(a < d && b < d)	cnt++;
				lf	(a == d && b < d && k > j)	cnt++;
				lf	(a < d && b == d && k > i)	cnt++;
				lf	(a == d && b == d && k > j)	cnt++;
			}
			
			if	(cnt >= K-2)	ret+= d * C[cnt][K-2];
		}
		
		return	ret / C[*A][K];
}

void	DFS3(int u, int f, int d){
		if	(V[u])	Count[d]++;
		siz[u]= 1;
		
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	{
				DFS3(v, u, d+1);
				siz[u]+= siz[v];
			}
}

DB		Work2(){	//另一种计算直径期望的方法
		N= **ID;
		M= *A;
		
		DB	ret= 0;
		For(u, 1, N)	{	//直径的中点在点上的情况
			For(j, 0, N)	Count[j]= 0, Ans[j]= 0;
			DFS3(u, 0, 0);
			
			For(j, 0, N)	gtw[j]= Count[j];
			For(j, 1, N)	gtw[j]+= gtw[j-1];
			
			For(j, 1, N)	{
				For(k, 2, min(Count[j], K))
					if	(gtw[j-1] >= K-k)	Ans[j]+= C[Count[j]][k] * C[gtw[j-1]][K-k];
				Count[j]= 0;
			}
			
			for (int i= st[u], v; i; i= E[i].next){
				DFS3(v= E[i].v, u, 1);
				
				For(j, 1, siz[v])	{
					For(k, 2, min(Count[j], K))
						if	(gtw[j-1] >= K-k)	Ans[j]-= C[Count[j]][k] * C[gtw[j-1]][K-k];
					Count[j]= 0;
				}
			}
			
			For(j, 1, N)	ret+= j*2 * Ans[j];
		}
		
		For(s, 1, T)	{	//直径的中点在边中的情况
			int u= X[s], v= Y[s];
			
			For(j, 0, N)	Count[j]= 0, Ans[j]= 0;
			DFS3(u, v, 1);
			DFS3(v, u, 1);
			
			For(j, 0, N)	gtw[j]= Count[j];
			For(j, 1, N)	gtw[j]+= gtw[j-1];
			
			For(j, 1, N)	{
				For(k, 2, min(Count[j], K))
					if	(gtw[j-1] >= K-k)	Ans[j]+= C[Count[j]][k] * C[gtw[j-1]][K-k];
				Count[j]= 0;
			}
			
			DFS3(u, v, 1);
			For(j, 1, siz[u])	{
				For(k, 2, min(Count[j], K))
					if	(gtw[j-1] >= K-k)	Ans[j]-= C[Count[j]][k] * C[gtw[j-1]][K-k];
				Count[j]= 0;
			}
			
			DFS3(v, u, 1);
			For(j, 1, siz[v])	{
				For(k, 2, min(Count[j], K))
					if	(gtw[j-1] >= K-k)	Ans[j]-= C[Count[j]][k] * C[gtw[j-1]][K-k];
				Count[j]= 0;
			}
			
			For(j, 1, N)	ret+= (j*2-1) * Ans[j];
		}
	
		return	ret / C[M][K];
}

class	Orienteering{
	public:
		double expectedLength(vector <string> field, int K)	{
			N= field.size();
			M= field[0].length();
			::K= K;
			
			For(i, 1, N)	For(j, 1, M)	{
				s[i][j]= field[i-1][j-1];
				if	(s[i][j] != '#')	ID[i][j]= ++ **ID;
				if	(s[i][j] == '*')	A[++ *A]= **ID, V[A[*A]]= 1;
			}
			
			For(i, 1, N)	For(j, 1, M)	if	(ID[i][j])	{
				if	(i-1 > 0 && ID[i-1][j])	Link(ID[i-1][j], ID[i][j]);
				if	(j-1 > 0 && ID[i][j-1])	Link(ID[i][j-1], ID[i][j]);
			}
			
			//建树
			
			For(i, 1, *A)	DFS(A[i], 0, 0, A[i]);
			
			DFS2(1, 0);
			sort(A+1, A+*A+1, Cmp);
			
			For(i, 0, *A)	{
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= C[i-1][j-1] + C[i-1][j];
			}

			return	Work1() - Work2();
		}
};