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

#define n	3005
#define P	1000000007

int		N, S, A[n], F[n], C[n][n];

class	LISNumber{
	public:
		int count(vector <int> card, int K){
			N= card.size();
			For(i, 1, N)	A[i]= card[i-1], S+= A[i];
			
			For(i, 0, 3000)	{
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= (C[i-1][j-1] + C[i-1][j]) % P;
			}
			
			For(i, 1, K)	{
				F[i]= 1;
				For(j, 1, N)	F[i]= 1ll*F[i]*C[i][A[j]]%P;	//计算出至多有i段的方案数
				
				For(j, 1, i-1)	F[i]= (F[i] - 1ll*F[j]*C[S+i-j][i-j]) % P;	//容斥减去不合法的，系数为*C[S+i-j][i-j]
			}
			
			return	(F[K] + P) % P;
		}
};