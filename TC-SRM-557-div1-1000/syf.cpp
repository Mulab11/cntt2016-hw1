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

#define n	55

int		N, M;
I64		Ans, Max, A[n], B[n];

class	XorAndSum{
	public:
		I64	maxSum(vector<I64> number){
			N= number.size();
			For(i, 1, N)	A[i]= number[i-1];
			
			For(i, 1, N)	Rep(j, 50, 0)	//求出线性基
				if	((1ll<<j) & A[i])	{
					if	(! B[j])	{
						B[j]= A[i];	M ++; break;
					}
					A[i]^= B[j];
				}
			
			Rep(j, 50, 0)	For(k, j+1, 50)	//消成最简线性基
				if	((1ll<<j) & B[k])	B[k]^= B[j];
			
			Rep(j, 50, 0)	if	(! ((1ll<<j) & Max) )	Max^= B[j];	//求出最大能xor得到的值
			
			Ans= (N-M+1)*Max;
			For(j, 0, 50)	if	(B[j] && (--M))	Ans+= B[j]^Max;	//计算答案。
			
			return	Ans;
		}
};