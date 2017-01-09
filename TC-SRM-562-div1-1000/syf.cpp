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
#define P	1000000009

int		N, K, D, st[n], ID[n][n];

int		L[n], R[n], C[n][n];

int		fa[n], V[n], siz[n], F[n][n][n], G[n][n], H[n];

struct	Lin{
		int v, next;
}E[n];

void	Link(int u, int v){
		E[++ D]= (Lin){v, st[u]};	st[u]= D;	ID[u][v]= D;
		E[++ D]= (Lin){u, st[v]};	st[v]= D;	ID[v][u]= D;
}

int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

void	DFS(int u, int f)	{
		int s= ID[f][u];
		
		if	(V[s])	return;
		V[s]= 1;
		
		siz[s]= 1;
		F[s][0][0]= 1;
		
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	{
				int t= ID[u][v];
				DFS(v, u);
				
				For(a, 0, siz[s])	For(b, 0, siz[s])
					G[a][b]= F[s][a][b], F[s][a][b]= 0;
				
				For(a, 0, siz[s])	For(b, 0, siz[s])
					For(c, 0, siz[t])	For(d, 0, siz[t])	//树形背包合并
						F[s][a+c][b+d]= (F[s][a+c][b+d] + 1ll*G[a][b]*F[t][c][d]%P*C[a+c][a]%P*C[b+d][b]) % P;
				
				siz[s]+= siz[t];
			}
		
		H[s]= L[siz[s]-1];
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	{
				int t= ID[u][v];
				H[s]= 1ll*H[s]*R[siz[t]]%P*H[t]%P;
			}
			
		F[s][0][siz[s]]= (F[s][0][siz[s]] + H[s]) % P;
		F[s][siz[s]][0]= (F[s][siz[s]][0] + H[s]) % P;
}

int		Ans, Seq[n];

void	DFS2(int u, int f)	{	//DFS所有路径
		Seq[++ *Seq]= u;
		
		if	(*Seq == N-2*K+2)	{
			int s= ID[Seq[2]][Seq[1]],
				t= ID[Seq[*Seq - 1]][Seq[*Seq]];
			
			if	(siz[s] == K && siz[t] == K)
				Ans= (Ans + 1ll*F[s][K][0]*F[t][0][K]) % P;
		}
		
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	DFS2(v, u);
				
		
		-- *Seq;
}

int		Work1(){
		if	(K == 1)	return	L[N];
		For(i, 1, N)	DFS2(i, 0);
		return	Ans;
}

int		Work2()	{
		int M= N-K;
		For(i, 1, N)	Ans= (Ans + F[ID[0][i]][M][M]) % P;
		For(i, 1, 2*K-N-1)	Ans= 1ll*Ans*i%P;
		return	Ans;
}

class	InducedSubgraphs{
	public:
		int 	getCount(vector <int> edge1, vector <int> edge2, int k){
			N= edge1.size() + 1;
			For(i, 2, N)	Link(edge1[i-2]+1, edge2[i-2]+1);
			
			L[0]= 1;
			For(i, 1, N)	L[i]= 1ll*L[i-1]*i%P;
			For(i, 0, N)	R[i]= Pow(L[i], P-2);
			
			For(i, 0, N)	{
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= (C[i-1][j-1] + C[i-1][j]) % P;
			}
			
			//预处理
			
			For(i, 1, N)	ID[0][i]= ++ D, DFS(i, 0);	//预处理Dp数组，为i这个子树，包含a个白点，b个黑点的方案。
			
			K= k;
			if	(2*K <= N)	return	Work1();	//分情况计数
			return	Work2();
		}
};