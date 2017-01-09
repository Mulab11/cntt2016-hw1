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
#define INF	(1ll << 60)

int		M1, M2, M3, cnt[n];

I64		A[n], B[n], C[n];

void	Work(int M, int p, int c)	{
	//	printf("---- %d %d %d\n", M, p, c);
		
		M2= M;
		For(i, 0, M-1)	cnt[i]= 0, B[i]= INF;
		
		For(k, 0, p*c)	{	//k只需要枚举到p*c即
			int	t= 1ll*k*k%p;
			for (int i= t; i < M; i+= p)	{	//将所有有可能含有p的数都除掉p
				int	x= (i - 1ll*k*k% M + M) % M;
				if	(! x)	x= M;
				
				int y= x;
				for (; x % p == 0; )	x/= p, cnt[i]++;
				
				if	(cnt[i] >= c)	B[i]= min(B[i], 1ll*k*k + y);	//更新答案
			}
		}
		
	//	For(i, 0, M-1)	printf("%lld %d\n", Min[i], cnt[i]);
	//	puts("");
		
		M3= M1;
		For(i, 0, M3-1)	C[i]= A[i];
		
		M1= M2 * M3;
		For(i, 0, M1)	{	//中国剩余定理
			int	x= i % M2, y= i % M3;
			
			if	(B[x] == INF || C[y] == INF)	A[i]= INF;
			else	{
				A[i]= i;
				
				if	(A[i] < B[x])
					A[i]+= ((B[x] - A[i] - 1) / M1 + 1) * M1;
				
				if	(A[i] < C[y])
					A[i]+= ((C[y] - A[i] - 1) / M1 + 1) * M1;
			}
		}
}

I64		Cal(I64 N)	{
		I64	ret= 0;
		For(i, 0, M1-1)	{
			if	(N < A[i])	continue;
			ret+= (N - A[i]) / M1 + 1;
		}
		return	ret;
}

class	SparseFactorial{
	public:
		I64 	getCount(I64 L, I64 R, int M)	{
			M1= 1;
			for (int i= 2; i <= M; i++)	//对于每一个质因子分别计算答案，然后用中国剩余定理合并
				if	(M % i == 0)	{
					int	p= i, c= 0, pc= 1;
					for (; M % p == 0; )	M/= p, c++, pc*= p;		
					Work(pc, p, c);	
				}
			
			return	Cal(R) - Cal(L-1);	//前缀和相减就是答案
		}
}GTW;