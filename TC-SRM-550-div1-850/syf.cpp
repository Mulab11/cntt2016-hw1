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
#define MK	make_pair1
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

#define n	15
#define m	155
#define P	1000000007

int		N, M, C, ID[n][n];

struct	Mat{	//矩阵乘法的板子
		int 	A[m][m];
		
		Mat()	{
			for	(int i= 1; i <= C; i ++)
				for	(int j= 1; j <= C; j ++)	A[i][j]= 0;
		}
		
		Mat	operator *	(const Mat&b)	const{
			Mat	c, a= *this;
			
			for	(int i= 1; i <= C; i ++)
				for	(int k= 1; k <= C; k ++)	if  (a.A[i][k])
					for	(int j= 1; j <= C; j ++)if  (b.A[k][j])
						c.A[i][j]= (1ll* a.A[i][k]* b.A[k][j] + c.A[i][j])%P;
			return	c;
		}
		Mat	operator ^	(int K)	const{
			Mat	ret, a=*this;
			for	(int i= 1; i <= C; i ++)	ret.A[i][i]= 1;
			
			for (;;)	{
				if  (K&1)	ret= ret*a;
				
				K>>= 1;
				if  (K)		a= a*a;
					else	break;
			}
			return	ret;
		}
}S;

class	ConversionMachine{
	public:
		int 	countAll(string word1, string word2, vector <int> cost, int MC){
			N= word1.length();
			int	sa= 0, sb= 0;
			
			For(i, 1, N)	{	//预处理
				int	x= word1[i-1], y= word2[i-1];
				if	(x == y)	{
					sa++;	continue;
				}
				
				if	(x == 'a' && y == 'b')	M++, MC-= cost[0], sb++;
				lf	(x == 'a' && y == 'c')	M+= 2, MC-= cost[0] + cost[1];
				lf	(x == 'b' && y == 'c')	M++, MC-= cost[1], sb++;
				lf	(x == 'b' && y == 'a')	M+= 2, MC-= cost[1] + cost[2];
				lf	(x == 'c' && y == 'a')	M++, MC-= cost[2], sb++;
					else	M+= 2, MC-= cost[2] + cost[0];
				
				//将必须要进行的变换做掉
				
				if	(MC < 0)	return	0;
			}
			M+= MC / (0ll + cost[0] + cost[1] + cost[2]) * 3;
			
			For(i, 0, N)	For(j, 0, N-i)	ID[i][j]= ++C;
			For(i, 0, N)	For(j, 0, N-i)	{
				int k= N-i-j;
				
				if	(i)	S.A[ID[i][j]][ID[i-1][j]]= i;
				if	(j)	S.A[ID[i][j]][ID[i+1][j-1]]= j;
				if	(k)	S.A[ID[i][j]][ID[i][j+1]]= k;
			}
			
			//构建矩阵
			
			C++;
			S.A[C][C]= 1;
			S.A[ID[N][0]][C]= 1;
			S= S^(M+1);
			
			//快速幂
			
			int	now= ID[sa][sb], Ans= S.A[now][C];
			return	Ans % P;
		}
};