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
#define m	1505

int		N, M, S, B[n], A[n][n];

DB		Ans, F[n][m][2];

class	RandomPaintingOnABoard{
	public:
		DB	expectedSteps(vector <string> prob){
			N= prob.size();
			M= prob[0].length();
			
			if	(N < M)	{
				For(i, 1, N)	For(j, 1, M)	A[i][j]= prob[i-1][j-1] - '0';
			}	else	{
				swap(N, M);
				For(i, 1, N)	For(j, 1, M)	A[i][j]= prob[j-1][i-1] - '0';
			}	//将较小维作为行
			
			For(i, 1, N)	For(j, 1, M)	S+= A[i][j];
			
			int U= (1 << N) - 1;	//枚举行状态进行容斥
			For(s, 0, U)	{
				For(i, 1, M)	{	//用DP计算出列合法的方案数
					B[i]= 0;
					For(j, 1, N)	if	(! ((1 << (j-1)) & s))	B[i]+= A[j][i];
				}
				
				For(i, 0, M)	For(j, 0, S)	For(k, 0, 1)	F[i][j][k]= 0;
				
				F[0][0][s>0]= -1;
				For(i, 1, N)	if	((1 << (i-1)) & s)	F[0][0][s>0]*= -1;

				For(i, 1, M)	For(j, 0, S-B[i])	For(k, 0, 1)	{	//枚举这个列的约束选不选择
					DB	val= F[i-1][j][k];
					
					F[i][j][1]-= val;
					F[i][j + B[i]][k]+= val;
				}
				
				For(j, 0, S-1)	Ans+= F[M][j][1] / (1 - 1.*j/S);
			}
			
			return	Ans;
		}
};