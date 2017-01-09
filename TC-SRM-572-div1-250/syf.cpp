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

#define n	5005

int		N, Ans, F[n], cnt[n];

int		Get(int u)	{
		return	F[u] == u ? u : F[u]= Get(F[u]);
}

void	Merge(int x, int y)	{	//并查集
		int fx= Get(x), fy= Get(y);
		
		if	(fx != fy)	F[fx]= fy;
}

class	NewArenaPassword{
	public:
		int minChange(string S, int K){
			N=	S.length();
			For(i, 1, N)	F[i]= i;
			
			For(i, 1, K)	Merge(i, N-K+i);	//将应该相同的格子连在一起
			
			For(i, 1, N)	if	(Get(i) == i)	{	//同一个并查集里取出现次数最多的即可
				For(c, 'a', 'z')	cnt[c]= 0;
				
				int	tot= 0;
				For(j, 1, N)	if	((j <= K || j > N-K) && Get(j) == Get(i))	cnt[S[j-1]]++, tot++;
				
				int	Max= 0;
				For(c, 'a', 'z')	Max= max(Max, cnt[c]);
				
				Ans+= tot - Max;
			}
			
			return	Ans;
		}
};