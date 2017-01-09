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

#define n	2005
#define P	1000000007

int		Ans, A[n], F[n][n], G[n][n];

void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
}

class	WolfInZooDivOne{
	public:
		int 	count(int N, vector <string> LL, vector <string> RR){
			string	L= "", R= "";
			For(i, 1, LL.size())	L+= LL[i-1];
			For(i, 1, RR.size())	R+= RR[i-1];
			
			for (int i= 0, j= 0, l1= L.length(), l2= R.length(); i < l1 && j < l2; i++, j++)	{
				int x= 0, y= 0;
				
				for (; i < l1 && L[i] != ' '; i++)	x= x*10 + L[i] - '0';
				for (; j < l2 && R[j] != ' '; j++)	y= y*10 + R[j] - '0';
				
				x++;
				y++;
				A[x]= max(A[x], y);
			}
			
			For(i, 1, N)	A[i]= max(A[i], A[i-1]);	//预处理
			
			For(i, 1, N)	F[0][i]= 1;
			
			For(i, 0, N)	{	//F[i][j]表示倒数第一个1是i，倒数第二个1是j的方案。
				For(j, i, N)	Plu(G[i][j], G[i][j-1]);	//前缀和优化
				For(j, i, N)	Plu(F[i][j], G[i][j]);
				
				For(j, i, N)	{
					int k= max(A[i], j) + 1;
					Plu(G[j][k], F[i][j]);	//计数
				}
			}
			
			For(i, 0, N)	For(j, i, N)	Plu(Ans, F[i][j]);
			Plu(Ans, 1);
			
			return	Ans;
		}
};