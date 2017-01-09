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

#define n	25

int		N, M, L[n], R[n], G[n], A[n][n];

DB		Ans, X[n];

void	Cal(DB M){
		int	rev= 0;
		For(i, 1, N)	X[i]= G[i], rev+= (G[i] == -1);
		
		if	(rev)	{	//用拉格朗日乘数法计算极值，用O(N^2)的解方程
			For(i, 1, N)	if	(G[i] == -1)
			For(j, 1, N)	if	(G[j] == -1 && i != j)
				if	(A[i][j] == 0)	return;	//如果没有团就推出
		
			DB a= 0, b= 0;
			For(i, 1, N)	if	(G[i] == -1){
				DB c= 0;
				For(j, 1, N)	if	(G[j] != -1)	c+= A[i][j]*X[j];
				a++, b+= M+c;
			}
			
			DB	lam= (M-b)/a;
			For(i, 1, N)	if	(G[i] == -1){
				DB c= 0;
				For(j, 1, N)	if	(G[j] != -1)	c+= A[i][j]*X[j];
				X[i]= M+c+lam;
			}	//计算出变量的值
			
			For(i, 1, N)	if	( ! (L[i] <= X[i] && X[i] <= R[i]) )	return;
		}
		
		DB	ret= 0;
		For(i, 1, N)	For(j, i+1, N)
			ret+= A[i][j]*X[i]*X[j];
		Ans= max(Ans, ret);
		
	//	puts("---");
	//	For(i, 1, N)	printf("%lf ", X[i]);
	//	puts("");
	//	printf("%lf\n", ret);
}

void	DFS(int d, int sum){	//3^N 枚举每一个变量是否取到上下边界。
		if	(sum > M)	return;
		if	(d > N)	return	Cal(M - sum);
		
		G[d]= -1;
		DFS(d+1, sum);
		
		G[d]= L[d];
		DFS(d+1, sum+L[d]);
		
		G[d]= R[d];
		DFS(d+1, sum+R[d]);
}

class	BoundedOptimization{
	public:
		DB	maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
			string	s= "";
			For(i, 1, expr.size())	s= s + expr[i-1];
			
			N= lowerBound.size();
			For(i, 1, N)	L[i]= lowerBound[i-1], R[i]= upperBound[i-1];
			M= maxSum;
			
			For(i, 1, s.length())	{
				int a= s[i-1] - 'a' + 1, b= s[i] - 'a' + 1;
				A[a][b]= A[b][a]= 1;
				i+=2;
			}
			
			//预处理
			
			int sum= 0;
			For(i, 1, N)	sum+= R[i];
			
			if	(sum <= M)	{	//如果sum<=M，则直接每个变量取最大值
				For(i, 1, N)	For(j, i+1, N)
					Ans+= A[i][j]*R[i]*R[j];
				return	Ans;
			}
			
			DFS(1, 0);
			return	Ans;
		}
};