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

#define n	505

int		N, C, D, X[n], Y[n], st[n], ID[n][n];

int		L[n], R[n], F[n][n];

int		w[n][n];

namespace	KM{	//KM的板子
	int		N, Tim, LA[n], LB[n], VA[n], VB[n], QA[n], QB[n], Match[n];
	
	bool	Find(int u)	{
		VA[u]= Tim;
		For(v, 1, N)	if	(VB[v] != Tim && LA[u] + LB[v] == w[u][v]){
			VB[v]= Tim;		
			if	(! Match[v] || Find(Match[v])){
				Match[v]= u;
				return	1;
			}
		}
		return	0;
	}
	
	void	Change()	{
		*QA= *QB= 0;
		For(i, 1, N)	if	(VA[i] == Tim)	QA[++ *QA]= i;
		For(i, 1, N)	if	(VB[i] != Tim)	QB[++ *QB]= i;
		
		int	Min= 1 << 30;
		For(i, 1, *QA)	For(j, 1, *QB)
			Min= min(Min, LA[QA[i]] + LB[QB[j]] - w[QA[i]][QB[j]]);
		
		For(i, 1, N)	if	(VA[i] == Tim)	LA[i]-= Min;
		For(i, 1, N)	if	(VB[i] == Tim)	LB[i]+= Min;
	}
	
	int		Main(int NN){
		N= NN;
		For(i, 1, N)	{
			LA[i]= LB[i]= Match[i]= 0;
			For(j, 1, N)	LA[i]= max(LA[i], w[i][j]);
		}
		
		For(i, 1, N)	{
			for (; ;)	{
				Tim++;
				if	(Find(i))	break;
				Change();
			}
		}
		
		int	ret= 0;
		For(i, 1, N)	ret+= w[Match[i]][i];
		return	ret;
	}
};

struct	Lin{
		int v, next;
}E[n];

void	Link(int u, int v)	{
		E[++ D]= (Lin){v, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, st[v]};	st[v]= D;
}

void	DFS1(int u, int f, int*L)	{
		L[++ *L]= u;
		
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	DFS1(v, u, L);
}

int		Work(int f1, int u1, int f2, int u2)	{	//表示两个子树的最大同构连通块大小
		int a= ID[f1][u1], b= ID[f2][u2];
		if	(F[a][b] != -1)	return	F[a][b];
		
		int	NA= 0, NB= 0;
		for (int i= st[u1]; i; i= E[i].next)
			if	(E[i].v != f1)	NA++;
		for (int j= st[u2]; j; j= E[j].next)
			if	(E[j].v != f2)	NB++;
		int	NC= max(NA, NB);
		
		for (int i= st[u1]; i; i= E[i].next)
		for (int j= st[u2]; j; j= E[j].next){
			int v1= E[i].v, v2= E[j].v;
			if	(v1 == f1 || v2 == f2)	continue;
			Work(u1, v1, u2, v2);
		}
		
	//	printf("# %d %d %d %d, %d %d:\n", f1, u1, f2, u2, a, b);
		
		For(i, 1, NC)	For(j, 1, NC)	w[i][j]= 0;
		
		for (int i= st[u1], ID1= 0; i; i= E[i].next){	//确定边权
			int v1= E[i].v;
			if	(v1 == f1)	continue;
			ID1++;
			
			for (int j= st[u2], ID2= 0; j; j= E[j].next)	{
				int	v2= E[j].v;
				if	(v2 == f2)	continue;
				ID2++;
				
				w[ID1][ID2]= Work(u1, v1, u2, v2);
			}
		}
		
		F[a][b]= KM::Main(NC) + 1;	//用KM跑最大权匹配
		return	F[a][b];
}

class	DeerInZooDivOne{
	public:
		int 	getmax(vector <int> a, vector <int> b){
			N= a.size() + 1;
			For(i, 2, N)	X[i]= a[i-2] + 1, Y[i]= b[i-2] + 1;
			
			For(i, 2, N)	ID[X[i]][Y[i]]= ++C, ID[Y[i]][X[i]]= ++C;	//给每一条边标号
			For(i, 1, N)	ID[0][i]= ++C;
			
			int	Ans= 0;
			For(i, 2, N)	{	//枚举把树上某一条边切断
				D= 0;
				For(j, 1, N)	st[j]= 0;
				For(j, 2, N)	if	(j != i)	Link(X[j], Y[j]);
				
				*L= *R= 0;
				DFS1(X[i], 0, L);	//DFS将一个联通块里面所有点拿出来
				DFS1(Y[i], 0, R);
				/* 
				puts("");
				For(j, 1, *L)	printf("%d ", L[j]);
				puts("");
				
				For(j, 1, *R)	printf("%d ", R[j]);
				puts(""); */
				
				For(j, 1, C)	For(k, 1, C)	F[j][k]= -1;
				For(j, 1, *L)	For(k, 1, *R)	Ans= max(Ans, Work(0, L[j], 0, R[k]));	
			}
			
			return	Ans;
		}
}GTW;