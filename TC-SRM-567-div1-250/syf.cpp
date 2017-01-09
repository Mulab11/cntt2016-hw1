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

map<int, int>	F;

int		Cal(int x)	{	//分解质因数，将奇数次幂的质数相乘
		int ret= 1;
		for (int i= 2; i*i <= x; i++)
			if	(x % i == 0)	{
				int t= 0;
				for (; x % i ==0; x/= i, t^=1);
				
				if	(t)	ret*= i;
			}
		
		ret*= x;
		return	ret;
}

int		Ans;

class	TheSquareRootDilemma{
	public:
		int countPairs(int N, int M){
			For(i, 1, N)	F[Cal(i)]++;
			For(i, 1, M)	Ans+= F[Cal(i)];	//计算答案
			return	Ans;
		}
};