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
#define m	2505
#define P	1000000007

int		E[n], F[n][n], C[m][m];

class	KingdomAndCities{
	public:
		int		howMany(int N, int M, int K){
			For(i, 1, N)	E[i]= E[i-1] + i-1;
			
			For(i, 0, E[N])	{	//预处理组合数
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= (C[i-1][j-1] + C[i-1][j]) % P;
			}
			
			For(i, 1, N)	For(j, 0, min(K, E[i]))	{	//预处理F[i][j]，表示i个点j条边的连通图个数
				F[i][j]= C[E[i]][j];
				
				For(a, 1, i-1)	For(b, 0, j){
					int x= i-a, y= j-b;
					
					F[i][j]= (F[i][j] - 1ll*F[a][b]*C[i-1][a-1]%P*C[E[x]][y] + P)%P;
				}
			}
			
			//分情况讨论
			
			if	(M == 0)	return	F[N][K];
			
			if	(M == 1)	{	//M=1只有连通块个数可能是1或者2
				int	Ans= 0;
				if	(K >= 2)	Ans= 1ll*F[N-1][K-2]*C[N-1][2]%P;
				
				For(i, 1, N-2)	For(j, 0, K-2){
					int x= N-1-i, y= K-2-j;
					
					Ans= (Ans + 1ll*C[N-2][i-1]*F[i][j]%P*F[x][y]%P*i*x) % P;
				}
				
				return	Ans;
			}
			
			int	Ans= 0;
			if	(K >= 3)	Ans= (Ans + 1ll*F[N-2][K-3]*(N-2)*(N-2)) % P;
			if	(K >= 4)	Ans= (Ans + 1ll*F[N-2][K-4]*C[N-2][2]%P*C[N-2][2]) % P;
			
			//计算连通块为3的
			
			if	(K >= 3)	{	//为1的
				For(i, 1, N-3)	For(j, 0, K-3){
					int x= N-2-i, y= K-3-j;
					
					Ans= (Ans + 1ll*C[N-3][i-1]*F[i][j]%P*F[x][y]%P*i*x*2)%P;
				}
			}
			
			if	(K >= 4)	{	//为1的
				For(i, 1, N-3)	For(j, 0, K-4){
					int x= N-2-i, y= K-4-j;
					
					Ans= (Ans + 1ll*C[N-3][i-1]*F[i][j]%P*F[x][y]%P*i*x%P*i*x) % P;
					Ans= (Ans + 1ll*C[N-3][i-1]*F[i][j]%P*F[x][y]%P*i*x*2%P*(C[i][2] + C[x][2])) % P;
				}
			}
			
			if	(K >= 4)	{	//为2的
				For(i, 1, N-4)	For(j, 0, K-4)
					For(x, 1, N-3-i)	For(y, 0, K-4-j)	{
						int a= N-2-i-x, b= K-4-j-y;
						int	t= (i*x*i*a + i*x*x*a + i*a*i*x + i*a*x*a + x*a*i*x + x*a*i*a) % P;
						
						Ans= (Ans + 1ll*C[N-3][i-1]*C[N-2-i-1][x-1]%P*F[i][j]%P*F[x][y]%P*F[a][b]%P*t) % P;
					}
			}
			
			return	Ans;
		}
};