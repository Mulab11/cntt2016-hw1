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
#define For(i,a,b)	for(int i=a;i<=b;i++)
#define Rep(i,a,b)	for(int i=a;i>=b;i--)

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define n	255
#define P	100007

const	DB	eps= 1e-10, Pi= acos(-1);

I64		H[n][n];
int		col[n], OK[n][n], Num[n][n];
int		F[n][n][2], G[n][n];

struct	Pot{
		DB	x, y;
		
		Pot	operator -	(const Pot&b)	{
			return	(Pot){x - b.x, y - b.y};
		}
		DB	operator *	(const Pot&b)	{
			return	x*b.y - y*b.x;
		}
}A[n], B[n];

void	Plu(int&a,int b){
		a+= b;
		if  (a >= P)	a-= P;
}

struct	FencingPenguins{
		int countWays(int N, int R, vector <int> x, vector <int> y, string s){
			int M= x.size();
			For(i, 1, M)	{
				A[i].x= x[i-1];
				A[i].y= y[i-1];
				col[i]= (s[i-1]>='a' && s[i-1] <= 'z')?s[i-1]-'a':s[i-1]-'A'+26;
			}
			
			For(i, 1, N)	B[i]= (Pot){R * cos(2*Pi/N*i), R * sin(2*Pi/N*i)};	//将圆上的点建出来
			
			For(i, 1, N)	For(j, i+1, N)	{	//预处理每一条连边是否合法
				I64	l= 0, r= 0;
				For(k, 1, M)	if	((A[k]-B[i])*(B[j]-B[i]) > 0)	l|= 1ll<<col[k], H[j][i]|= 1ll<<k, Num[i][j]++;
					else	r|= 1ll<<col[k], H[i][j]|= 1ll<<k, Num[j][i]++;
				OK[i][j]= OK[j][i]= (l & r) == 0;
			}
			
			For(len, 3, N)	For(i, 1, N-len+1)	{	//区间Dp，F[i][j]表示i-j这些点构成凸包的方案数
				int j= i+len-1;
				
				For(k, i+1, j-1)	if	(OK[i][k]){	//枚举新加入的三角形，要求在边界上
					int t= (H[i][k]&H[k][j]&H[j][i])>0;
					For(b, 0, 1)	{	//分情况转移
						int x= 0, y= 0;
						
						if	(! Num[i][k])	x= 1;
						lf	(i+1 < k-1 && Num[i][k] == Num[i+1][k-1]&& OK[i][k])	x= G[i+1][k-1];
						
						if	(! b)	{
							if	(! Num[k][j])	y= 1 + F[k][j][b];
							else	{
								y= F[k][j][b];
								if	(k+1 < j-1 && Num[k][j] == Num[k+1][j-1] && OK[k][j])	y+= G[k+1][j-1];
							}
						}	else	y= F[k][j][b];
						
						Plu(F[i][j][t|b], 1ll*x*y%P);
					}
				}
				
				if	(Num[i][j] == Num[i+1][j])	Plu(G[i][j], G[i+1][j]);	//G[i][j]表示将i-j构成若干封闭的凸包的方案数
				
				For(k, i+1, j-1)	if	(OK[k][i])	{
					if	(Num[i][k] + Num[k+1][j]  == Num[i][j])	Plu(G[i][j], 1ll*F[i][k][1]*G[k+1][j]%P);
					if	(Num[i][k] == Num[i][j])	Plu(G[i][j], F[i][k][1]);
				}
				if	(OK[j][i])	Plu(G[i][j], F[i][j][1]);
			}
			
			if	(Num[N][1])	return	0;
			return	G[1][N];
		}
};