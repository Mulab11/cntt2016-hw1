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
#define INF	(1ll << 60)

int		N, A[n], E[n][n];

I64		F[n][n];

class	SkiResorts{
	public:
		long long minCost(vector <string> road, vector <int> altitude){	
			N= road.size();
			For(i, 1, N)	For(j, 1, N)	E[i][j]= (road[i-1][j-1] == 'Y');
			For(i, 1, N)	A[i]= altitude[i-1];
			
			For(i, 1, N)	For(j, 1, N)	F[i][j]= INF;
			For(i, 1, N)	F[1][i]= abs(A[i]-A[1]);
			
			//F[i][j]表示第i个点，特征值为j的最短路，随便转移一下即可
			
			For(Tim, 1, N)	{
				For(i, 1, N)	For(j, 1, N)	if	(F[i][j] != INF)
					For(k, 1, N)	if	(E[i][k])
						For(l, 1, N)	if	(A[l] <= A[j])	F[k][l]= min(F[k][l], F[i][j] + abs(A[k]-A[l]));
			}
			
			I64	Ans= INF;
			For(i, 1, N)	Ans= min(Ans, F[N][i]);
			
			if	(Ans == INF)	return	-1;
			return	Ans;
		}
};