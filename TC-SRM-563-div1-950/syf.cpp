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

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define n	43
#define m	n*n
#define P	1000000009

const	int	cx[]= {-1, 0, 0, 1, 0}, cy[]= {0, -1, 1, 0, 0};

int		N, M, A[n][n];

int		tot;

short	Q[n*n*n*n][4];

bool	Vis[n][n][n][n];

int		C, ID[n][n], F[m], S[m], B[m];

void	Push(int x1, int y1, int x2, int y2)	{	//入队
		if	(Vis[x1][y1][x2][y2])	return;
	
	//	printf("# %d %d %d %d\n", x1, y1, x2, y2);
	
		tot++;
		Vis[x1][y1][x2][y2]= 1;
		
		Q[tot][0]= x1;
		Q[tot][1]= y1;
		Q[tot][2]= x2;
		Q[tot][3]= y2;
}

bool	Inside(int x, int y)	{
		if	(1 <= x && x <= N && 1 <= y && y <= M)	return	1;
		return	0;
}

int		Get(int u)	{
		if	(F[u] == u)	return	u;
		return	F[u]= Get(F[u]);
}

void	Merge(int x, int y)	{	//并查集
		int fx= Get(x), fy= Get(y);
		if	(fx != fy)	{
			F[fx]= fy;
			S[fy]+= S[fx];
		}
}

class	CoinsGame{
	public:
		int 	ways(vector <string> board){
			N= board.size();
			M= board[0].length();
			
			For(i, 1, N)	For(j, 1, M)
				A[i][j]= board[i-1][j-1] == '.';
			
			For(i, 1, N)	For(j, 1, M)	if	(A[i][j])	{
				For(k, 1, M)	Push(i, j, 0, k), Push(i, j, N+1, k);
				For(k, 1, N)	Push(i, j, k, 0), Push(i, j, k, M+1);
			}	//把所有终止态扔进队列
		
			for (int i= 1; i <= tot; i++)	{	//BFS把所有合法的状态都求出来
				int x1= Q[i][0], y1= Q[i][1], x2= Q[i][2], y2= Q[i][3];
			//	if	(i == 12)	printf("## %d %d %d %d\n", x1, y1, x2, y2);
				
				For(a, 0, 4)	For(b, 0, 4)	{	//枚举上一个状态两个点的位置
					int x1_= x1 + cx[a], y1_= y1 + cy[a],
						x2_= x2 + cx[b], y2_= y2 + cy[b];
					
				//	if	(i == 12)	printf("### %d %d : %d %d %d %d\n", a, b, x1_, y1_, x2_, y2_);
					
					if	(! Inside(x1_, y1_) || ! Inside(x2_, y2_) || ! A[x1_][y1_] || ! A[x2_][y2_])	continue;
					
					
					int	flag= 0;
					For(k, 0, 3)	{	//枚举下一次操作
						int x1__= x1_ + cx[k], y1__= y1_ + cy[k],
							x2__= x2_ + cx[k], y2__= y2_ + cy[k];
						
						if	(! Inside(x1__, y1__))	{
							if	(! (x1__ == x1 && y1__ == y1))	continue;
						}
						lf	(A[x1__][y1__])	{
							if	(! (x1__ == x1 && y1__ == y1))	continue;
						}	else	{
							if	(! (x1_ == x1 && y1_ == y1))	continue;
						}
						
						if	(! Inside(x2__, y2__))	{
							if	(! (x2__ == x2 && y2__ == y2))	continue;
						}
						lf	(A[x2__][y2__])	{
							if	(! (x2__ == x2 && y2__ == y2))	continue;
						}	else	{
							if	(! (x2_ == x2 && y2_ == y2))	continue;
						}
						
						flag= 1;
						break;
					}
					
					if	(flag)	Push(x1_, y1_, x2_, y2_);
				}
			}
			
			For(i, 1, N)	For(j, 1, M)
				if	(A[i][j])	ID[i][j]= ++C;
			For(i, 1, C)	F[i]= i, S[i]= 1;
			
			For(i, 1, N)	For(j, 1, M)	if	(ID[i][j])
				For(x, 1, N)	For(y, 1, M)	if	(ID[x][y])
					if	(! Vis[i][j][x][y] && ! Vis[x][y][i][j])	Merge(ID[i][j], ID[x][y]);	//得到所有连通块
			
			B[0]= 1;
			For(i, 1, C)	 B[i]= B[i-1]*2%P;
			
			int	All= (B[C] - 1 - C)%P, wei= 0;
			For(i, 1, C)	if	(Get(i) == i)	wei= (wei + (B[S[i]] - S[i] - 1)) % P;	//将所有独立集方案减去
			
			return	(0ll + All - wei + P*2) % P;
		}
};