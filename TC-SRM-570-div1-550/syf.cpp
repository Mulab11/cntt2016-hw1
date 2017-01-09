//============================================================================
// Author       : sunyaofeng
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

#define	min(a,b)	((a)<(b)?(a):(b))
#define	max(a,b)	((a)<(b)?(b):(a))

#define For(i,a,b)	for(int i=a;i<=b;i++)

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define	M	50
#define	n	55

int		N, D, st[n], L[n], R[n];

I64		Ans, F[n][n << 1][2], G[n << 1][2];

struct	Lin{
		int v, next;
}E[n << 1];

void	Link(int u, int v){
		E[++D]= (Lin){v, st[u]};	st[u]= D;
		E[++D]= (Lin){u, st[v]};	st[v]= D;
}

void	Work(int u, int f){	//F[i][j]表示第i个点子树，所求的东西权值为j的方案数，用树形背包转移。
		F[u][M][0]= 1;
		F[u][M+1][1]= 1;
		L[u]= M;
		R[u]= M+1;
		
		for	(int i= st[u], v; i; i = E[i].next )	
			if  ((v= E[i].v) != f)	{
				Work(v, u);
				
				int l= n<<1, r= 0;
				for	(int x= L[u]; x <= R[u]; x ++ )		//枚举两个子树的信息
					for	(int y= L[v]; y <= R[v]; y ++ )	{
						if  (F[u][x][0] > 0 && F[v][y][0]+F[v][y][1] > 0){
							G[x+y-M][0]= 1ll*F[u][x][0]*(F[v][y][0]+F[v][y][1]) + G[x+y-M][0];
							l= min(l, x+y-M);
							r= max(r, x+y-M);
						}
						
						if  (F[u][x][1] > 0 && F[v][y][0] > 0){
							G[x+y-M][1]= 1ll*F[u][x][1]*F[v][y][0] + G[x+y-M][1];
							l= min(l, x+y-M);
							r= max(r, x+y-M);
						}
						
						if  (F[u][x][1] > 0 && F[v][y][1] > 0){
							G[x+y-2-M][1]=  1ll*F[u][x][1]*F[v][y][1] + G[x+y-2-M][1];
							l= min(l, x+y-2-M);
							r= max(r, x+y-2-M);
						}
					}
				
				L[u]= l;
				R[u]= r;
				for	(int i= L[u]; i <= R[u]; i ++ )	{
					F[u][i][0]= G[i][0];
					F[u][i][1]= G[i][1];
					G[i][0]= G[i][1]= 0;
				}
			}
}

class	CentaurCompany{
	public:
		double getvalue(vector <int> a, vector <int> b){
			N= a.size() + 1;
			For(i, 2, N)	Link(a[i-2], b[i-2]);
			
			Work(1, 0);	//树形Dp
			for	(int i= L[1]; i <= R[1]; i ++ )	
				Ans= 1ll*(F[1][i][0]+F[1][i][1])*max(i-M-2, 0) + Ans;	//累加答案
			
			DB	ret= Ans * 2;
			For(i, 1, N)	ret*= .5;
			
			return	ret;
		}
};