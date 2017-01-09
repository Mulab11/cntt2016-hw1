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

#define n	15
#define INF	(1 << 30)

int		N, M, V[n], A[n][n], B[n][n];

void	T1(int x, int y)	{	//操作一
		B[x-1][y]^= 1;
		B[x][y-1]^= 1;
		B[x][y]^= 1;
		B[x][y+1]^= 1;
		B[x+1][y]^= 1;
}

void	T2(int x, int y)	{	//操作二
		B[x-1][y]^= 1;
		B[x][y-1]^= 1;
		B[x][y+1]^= 1;
		B[x+1][y]^= 1;
}

class	YetAnotherBoardGame{
	public:
		int 	minimumMoves(vector <string> board){
			N= board.size();
			M= board[0].length();
			For(i, 1, N)	For(j, 1, M)	A[i][j]= board[i-1][j-1] == 'W';
			
			int U= (1 << M) - 1, Ans= INF;
			For(s, 0, U)	{	//枚举每一列进行的操作是种类1还是2
				For(i, 1, M)	V[i]= ((1 << (i-1)) & s) > 0;
				
				{
					for (int t= s; ; t= (t-1) & s){	//枚举第一列的状态
						For(i, 1, N)	For(j, 1, M)	B[i][j]= A[i][j];
						
						int	ret= 0;
						For(i, 1, M)	if	((1 << (i-1)) & t)	T1(1, i), ret++;
						
						For(i, 1, N-1)	{	//NM推一遍
							int v1= 0, v2= 0;
							
							For(j, 1, M)	if	(B[i][j])	{
								if	(V[j])	T1(i+1, j), v1= 1;
									else	T2(i+1, j), v2= 1;
								ret++;
							}
							
							if	(v1 && v2)	{ret= INF;	break;}	//验证
						}
						
						For(i, 1, M)	if	(B[N][i])	ret= INF;
						Ans= min(Ans, ret);
						
						if	(! t)	break;
					}
				}
				
				{
					for (int t= s; ; t= (t-1) & s){
						For(i, 1, N)	For(j, 1, M)	B[i][j]= A[i][j];
						
						int	ret= 0;
						For(i, 1, M)	if	((1 << (i-1)) & t)	T2(1, i), ret++;
						
						For(i, 1, N-1)	{
							int v1= 0, v2= 0;
							
							For(j, 1, M)	if	(B[i][j])	{
								if	(V[j])	T2(i+1, j), v1= 1;
									else	T1(i+1, j), v2= 1;
								ret++;
							}
							
							if	(v1 && v2)	{ret= INF;	break;}
						}
						
						For(i, 1, M)	if	(B[N][i])	ret= INF;
						Ans= min(Ans, ret);
						
						if	(! t)	break;
					}
				}
			}
			
			return	Ans == INF ? -1 : Ans;
		}
}GTW;