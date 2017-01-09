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

int		Ans= 4;

bool	check(int N, int M, int X)	{	//判断是否可以一次完成
		if	(M == 1 && (X == 1 || X == N))	return	1;
		if	(N <= M && (X == 1 || X == N))	return	1;
		if	(N % M == 1 && X == N)	return	1;
		if	(N < 2*M && X == M)	return	1;
		return	0;
}

void	DFS(int N, int M, int X, int s)	{
		if	(check(N, M, X))	{
			Ans= min(Ans, s);
			return;
		}
		if	(s == 3)	return;
		
		int	a= (X-1) / M + 1, b= (X-1) % M + 1;
		int	c= (N-1) / M, d= (N-1) % M + 1;
		
		if	(c >= a)	{	//枚举这一层的选法
			For(i, 1, a-1)	For(j, 1, M)	DFS(N - i*j, M, X - i*j, s+1);
		
			DFS(N - (c-a)*M - d, M, X, s+1);
			
			For(i, 1, a)	For(j, 1, b-1)	DFS(N - i*j - (c-a)*j - min(d, j), M, X - i*j, s+1);
			
			For(i, 1, a)	For(j, 1, M-b)	DFS(N - i*j - (c-a)*j - max(0, min(d-b, j)), M, X - (i-1)*j, s+1);
		}
		else	{
			For(i, 1, a-1)	For(j, 1, M)	DFS(N - i*j, M, X - i*j, s+1);
			
			For(i, 1, a)	For(j, 1, b-1)	DFS(N - i*j, M, X - i*j, s+1);
			
			For(i, 1, a)	For(j, 1, M-b)	DFS(N - (i-1)*j - max(0, min(d-b, j)), M, X - (i-1)*j, s+1);
		}
}

class	FoxAndAvatar{
	public:
		int minimalSteps(int N, int M, int X){	//答案小于等于4，只需要枚举前两层，第3层可以特判，否则输出4
			if	(N == 1)	return	0;
			DFS(N, M, X, 1);
			return	Ans;
		}
};