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

#define m	25
#define n	105
#define INF	(1 << 30)

int		C, N, M, F[m][m][m][m];

struct	Nod{
		int a, b, c, d;
}A[n];

bool	OK(int i, int a, int b, int c, int d)	{	//判断合法性
		return	A[i].a <= a && A[i].b <= b && A[i].c <= c && A[i].d <= d;
}

int		Cal(int i, int a, int b, int c, int d)	{	//计算答案
		return	max(A[i].a + d, max(A[i].b + c, max(A[i].c + b, A[i].d + a)));
}

void	Min(int&a, int b)	{
		a= min(a, b);
}

class	EllysChessboard{
	public:
		int 	minCost(vector <string> s){
			For(i, 1, s.size())	For(j, 1, s[0].length())
				if	(s[i-1][j-1] == '#')	A[++ C]= (Nod){i+j, i-j, j-i, -i-j};
			
			N= s.size() + 1;
			M= N << 1;
			
			//F[a][b][c][d]表示前四个值小于等于a,b,c,d的所有物品构成的答案，枚举下一个加入的物品转移
			
			For(a, 0, M)	For(b, 0, M)	For(c, 0, M)	For(d, 0, M)	F[a][b][c][d]= INF;
			F[0][0][0][0]= 0;
			
			For(a, 0, M)	For(b, 0, M)	For(c, 0, M)	For(d, 0, M)	if	(F[a][b][c][d] < INF)	{
				For(i, 1, C)	if	(! OK(i, a, b-N, c-N, d-M))	{
					int	t= (a+b+c+d ? Cal(i, a, b-N, c-N, d-M) : 0);
					int	a1= max(a, A[i].a), b1= max(b, A[i].b+N), c1= max(c, A[i].c+N), d1= max(d, A[i].d+M);
					
					For(j, 1, C)	if	(! OK(j, a, b-N, c-N, d-M) && OK(j, a1, b1-N, c1-N, d1-M) && j != i)
						t+= Cal(j, a1, b1-N, c1-N, d1-M);
					
					Min(F[a1][b1][c1][d1], F[a][b][c][d] + t);
				}
			}
			
			int	a= 0, b= 0, c= 0, d= 0;
			For(i, 1, C)	{
				a= max(a, A[i].a);
				b= max(b, A[i].b+N);
				c= max(c, A[i].c+N);
				d= max(d, A[i].d+M);
			}
			
			return	F[a][b][c][d];
		}
}GTW;