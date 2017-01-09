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

int		F[n][n][m];

void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
}

class	LittleElephantAndPermutationDiv1{
	public:
		int getNumber(int N, int M){
			F[N+1][0][0]= 1;
			M--;
			
			//F[i][j][k]表示处理了i-N这些数，权值为j，还有k个空的方案数
			
			Rep(i, N, 1)	For(j, 0, i)	For(k, 0, M){
				int val= F[i+1][j][k];
				if	(! val)	continue;
				
				Plu(F[i][j][k+i], val);	//枚举这一位的放法
				Plu(F[i][j][k+i], 1ll*val*j%P);
				
				if	(j)	Plu(F[i][j-1][k], 1ll*val*j*j%P);
				
				Plu(F[i][j][k+i], 1ll*val*j%P);
				Plu(F[i][j+1][k+2*i], val);
			}
			
			int	tot= 1;
			For(i, 1, N)	tot= 1ll*tot*i%P;
			
			int	Ans= tot;
			For(k, 0, M)	Ans= (Ans - F[1][0][k] + P) % P;
			
			return	1ll*Ans*tot%P;
		}
};