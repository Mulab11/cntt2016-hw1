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
#define INF	(1 << 30)

int		N, F[n][8];

void	Min(int&a, int b)	{
		a= min(a, b);
}

class	BallsSeparating{
	public:
		int minOperations(vector <int> red, vector <int> green, vector <int> blue){
			N= red.size();
			
			if	(N < 3)	return	-1;
			
			For(i, 0, N)	For(j, 0, 7)	F[i][j]= INF;	//F[i][j] 表示处理了前i个物品后，8种三种颜色出现的情况的最少操作次数。
			F[0][0]= 0;
			
			For(i, 1, N)	{
				int r= red[i-1], g= green[i-1], b= blue[i-1];
				
				For(j, 0, 7)	{	//枚举放哪一个
					Min(F[i][j|1], F[i-1][j] + g + b);	
					Min(F[i][j|2], F[i-1][j] + r + b);
					Min(F[i][j|4], F[i-1][j] + r + g);
				}
			}
			
			return	F[N][7];
		}
};