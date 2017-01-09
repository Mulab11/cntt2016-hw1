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

int		Cal(int x)	{
		int t= 1, ret= 0;
		for (; (t << 1) <= x; )	t<<= 1, ret++;
		
		if	(t != x)	ret++;
		return	ret;
}

class	BigFatInteger{
	public:
		int 	minOperations(int A, int B){
			int	sum= 0, ans= 0;
			for (int i= 2; i <= A; i++)	//每一个质因子分别计算
				if	(A % i == 0)	{
					sum++;
					
					int	t= 0;
					for (; A%i == 0; )	A/= i, t++;
					t*= B;
					
					ans= max(ans, Cal(t));
				}
			
			return	sum + ans;
		}
};