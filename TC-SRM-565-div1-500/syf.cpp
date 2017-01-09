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

#define n	1000005

int		N, V[n], num[n], rev[n], F[n];

class	TheDivisionGame{
	public:
		I64		countWinningIntervals(int L, int R){
			N= R-L+1;
			For(i, 1, N)	rev[i]= L+i-1;
			
			int S= 100000;
			For(i, 2, S)	if	(! V[i])	{	//将L-R的所有数分解质因数，可以枚举小于\sqrT{R}的质数
				For(j, 2, S/i)	V[i*j]= 1;
				
				int x= ((L-1) / i + 1) * i;
				for (; x <= R; x+= i)	{
					int j= x-L+1;
					for (; rev[j] % i == 0; )	rev[j]/= i, num[j]++;
				}
			}
			
			For(i, 1, N)	if	(rev[i] > 1)	num[i]++;
			For(i, 1, N)	num[i]^= num[i-1];
			
			//计算出SG值，xor起来就是答案。
			
			I64	Ans= 0;
			For(i, 1, N)	{
				F[num[i-1]]++;
				Ans+= i - F[num[i]];
			}
			
			return	Ans;
		}
};