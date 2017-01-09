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

int		N;

I64		A[n], F[n][n << 1];

void	Max(I64&a, I64 b){
		a= max(a, b);
}

class	MonstersValley{
	public:
		int minimumPrice(vector<long long> dread, vector <int> price){
			N= dread.size();
			For(i, 1, N)	A[i]= dread[i-1];
			
			For(i, 0, N)	For(j, 0, N*2)	F[i][j]= -INF;	//F[i][j]表示前i个位置，收到j点伤害的最高智商，直接转移
			F[0][0]= 0;
			
			For(i, 1, N)	For(j, 0, N*2)	if	(F[i-1][j] != -INF){
				Max(F[i][j+price[i-1]], F[i-1][j] + A[i]);
				
				if	(A[i] <= F[i-1][j])	Max(F[i][j], F[i-1][j]);
			}
			
			For(j, 0, N*2)	if	(F[N][j] != -INF)	return j;
			return	233;
		}
};