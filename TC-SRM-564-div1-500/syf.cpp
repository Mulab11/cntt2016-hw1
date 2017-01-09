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

class	AlternateColors2{
	public:
		I64	countWays(int N, int K)	{
			I64	Ans= 0;
			
			For(i, 0, N/3)	{
				if	(3*i >= K)	{
					if	(K % 3 == 1)	{
						int rev= N - 3*i;
						Ans+= 1ll*(rev+2)*(rev+1)/2;
					}
					break;
				}	else	{
					int	rev= N - 3*i, t= K - 3*i;
					
					Ans++;	//全放在R上

					if	(t % 2 == 1)	{
						if	(t/2)	Ans+= 2 * (rev - t + 1);
							else	Ans+= 2 * (rev - t);
					}
					
					Ans+= 2 * max(0, t / 2 - 1);
				}
			}
			
			return	Ans;
		}
};