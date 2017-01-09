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

#define n	355
#define P	1000000007

int		N;

struct	Mat{	//矩阵乘法快速幂
		int A[n];
		
		Mat()	{
			For(i, 0, N-1)	A[i]= 0;
		}
		
		Mat	operator *	(const Mat& b)	{
			Mat	c, a= *this;
			For(i, 0, N-1)	For(j, 0, N-1)
				c.A[(i+j)%N]= (c.A[(i+j)%N] + 1ll*a.A[i]*b.A[j]) % P;
			return	c;
		}
		
		Mat	operator ^	(I64 K)	{
			Mat	ret, a= *this;
			ret.A[0]= 1;
			
			for (; K; K >>= 1, a= a*a)
				if	(K&1)	ret= ret * a;
			return	ret;
		}
}F[n];

class	PenguinEmperor{
	public:
		int		countJourneys(int N, I64 M){
			::N= N;
			F[0].A[0]= 1;
			
			For(i, 1, N)	{	//将进行1-i步操作的矩阵预处理出来
				Mat	t;
				t.A[i]= t.A[N-i]= 1;
				
				F[i]= t * F[i-1];
			}
			
			Mat	Ans= (F[N]^(M/N)) * F[M%N];	//计算答案
			
			return	Ans.A[0];
		}
};