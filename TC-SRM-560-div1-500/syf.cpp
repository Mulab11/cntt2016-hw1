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

#define n	1005

int		N, A[n], B[n];

int		F[2][n][n], sum[n][n];

class	DrawingPointsDivOne	{
	public:
		int maxSteps(vector <int> x, vector <int> y){
			N= x.size();
			For(i, 1, N)	{
				A[i]= x[i-1] * 2 + 500;
				B[i]= y[i-1] * 2 + 500;
				F[0][A[i]][B[i]]= 1;
			}
			
			int	Ans= -1;
			For(Tim, 1, 300)	{	//枚举答案
				int p= Tim&1, q= p^1;
				
				For(i, 1, 1000)	For(j, 1, 1000)	F[p][i][j]= 0;
				
				For(i, 1, 1000)	For(j, 1, 1000)
					if	(F[q][i-1][j-1] || F[q][i-1][j+1] || F[q][i+1][j-1] || F[q][i+1][j+1])	F[p][i][j]= 1;
				
				For(i, 1, 1000)	For(j, 1, 1000)	sum[i][j]= 0;
				For(i, 1, 1000)	For(j, 1, 1000)	sum[i][j]= F[p][i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
				
				//2维前缀和
				
				int	cnt= 0, d= 2*Tim+1;
				For(i, d, 1000)	For(j, d, 1000){	//通过判断一个矩阵是否全满，来判断是否合法。
					int t= sum[i][j] - sum[i-d][j] - sum[i][j-d] + sum[i-d][j-d];
					if	(t == (Tim+1)*(Tim+1))	cnt++;
				}
				
				if	(cnt > N)	{
					Ans= Tim-1;
					break;
				}
			}
			
			return	Ans;
		}
};