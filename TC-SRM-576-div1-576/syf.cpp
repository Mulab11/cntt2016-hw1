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

#define n	305
#define P	1000000009

int		N, A[n], F[n][n][3];

void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
}

class	TheExperiment{
	public:
		int countPlacements(vector <string> s, int M, int L, int X, int Y){
			For(i, 1, s.size())	For(j, 1, s[i-1].length())	A[++ N]= s[i-1][j-1] - '0';
			For(i, 1, N)	A[i]+= A[i-1];
			
			F[0][0][0]= 1;	//F[i][j][k]表示前i格，有j段，是否出现过最大值的答案
			For(i, 1, N)	For(j, 0, M)	{
				Plu(F[i][j][0], F[i-1][j][0]);
				Plu(F[i][j][0], F[i-1][j][2]);
				
				if	(j)	{
					For(k, 1, min(i, L))	//枚举上一段，转移
					if	(X <= A[i] - A[i-k] && A[i] - A[i-k] <= Y){
						if	(k < L)	{
							Plu(F[i][j][1], F[i-k][j-1][0]);
							Plu(F[i][j][1], F[i-k][j-1][1]);
						}
						
						Plu(F[i][j][2], F[i-k][j-1][2]);
						if	(k == L)	{
							Plu(F[i][j][2], F[i-k][j-1][0]);
							Plu(F[i][j][2], F[i-k][j-1][1]);
						}
					}
				}
			}
			
			int	Ans= (F[N][M][0] + F[N][M][2]) % P;
			return	Ans;
		}
}GT;