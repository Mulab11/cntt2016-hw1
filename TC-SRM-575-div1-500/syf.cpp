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

int		N, A[n];

DB		sum, F[n][2];

class	TheSwapsDivOne{
	public:
		double find(vector <string> S, int M)	{
			For(i, 1, S.size())	For(j, 1, S[i-1].length())	A[++ N]= S[i-1][j-1] - '0', sum+= A[N];
			
			F[0][1]= 1;
			For(i, 1, M)	{	//F[i][j]表示i轮后，是否在本位的概率，随便转移一下。
				F[i][1]+= F[i-1][1] * (N-2) / N;
				F[i][1]+= F[i-1][0] * 2 / N;
				F[i][0]= (1 - F[i][1]) / (N-1);
			}
			
		//	For(i, 0, M)	printf("%.6lf %.6lf %.6lf\n", F[i][0], F[i][1], F[i][0] * (N-1) + F[i][1]);
			
			DB	Ans= 0;
			For(i, 1, N)	Ans+= ( F[M][1] * A[i] + F[M][0] * (sum - A[i]) ) * i * (N-i+1);	//计算答案
			return	Ans * 2 / N / (N+1);
		}
}GTW;