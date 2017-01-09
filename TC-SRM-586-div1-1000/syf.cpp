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
#define m	105
#define INF	(1 << 30)

int		N, A[n], B[n], F[n][27][27];

inline	void	Min(int&a, int b)	{
		a= min(a, b);
}

class	StringWeight{
	public:
		int getMinimum(vector <int> ss){
			N= ss.size();
			For(i, 1, N)	A[i]= ss[i-1], B[i]= B[i-1] + A[i];
			
			For(i, 0, N)	For(a, 0, 26)	For(b, 0, 26)	F[i][a][b]= INF;
			F[0][0][0]= 0;	//F[i][a][b] 表示前i个串，用a个字母完结，用b个字母还没有被匹配
			
			For(i, 1, N)	{
				int tot= min(A[i], 26);
				
				For(a, 0, 26)	For(b, 0, 26)	{
					int	val= F[i-1][a][b];
					if	(val == INF)	continue;
					
					For(x, 0, min(b, tot))	For(y, 0, min(tot-x, 26-a-b)){	//枚举这个串的性质，贪心摆放
						int	t= val + (B[i-1] * x + (1+x)*x/2) - (B[i] * y - (y-1)*y/2);
						int	c= min(tot-x-y, b-x), d= tot-x-y-c;	//延续的, 自给自足的
						
						if	(a+b+y+d > 26)	continue;
						
						if	(c)	Min(F[i][a+x+d][b-x+y], t);
						else	{
							int	len= A[i]-x-y;
							Min(F[i][a+x+d][b-x+y], t + len - d);
						}
					}
				}
			}
			
			int	Ans= INF;
			For(a, 0, 26)	Min(Ans, F[N][a][0]);
			
			return	Ans;
		}
}GT;