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
#define INF	(1 << 29)

int		N, F[n][n];

class	Egalitarianism{
	public:
		int maxDifference(vector <string> s, int d){	//差分约束，构图后用floyed跑最短路
			N= s.size();
			For(i, 1, N)	For(j, 1, N)	F[i][j]= INF;
			For(i, 1, N)	F[i][i]= 0;
			
			For(i, 1, N)	For(j, 1, N)
				if	(s[i-1][j-1] == 'Y')	F[i][j]= min(F[i][j], d);
			
			For(k, 1, N)	For(i, 1, N)	For(j, 1, N)
				F[i][j]= min(F[i][j], F[i][k] + F[k][j]);
			
			int	Ans= 0;
			For(i, 1, N)	For(j, 1, N)	Ans= max(Ans, F[i][j]);
			
			return	Ans == INF ? -1 : Ans;
		}
};