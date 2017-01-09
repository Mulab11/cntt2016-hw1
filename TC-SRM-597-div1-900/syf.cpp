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

#define	n	2000005
#define P	1000000007

int		U[n], D[n], P2[n];

int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

int		C(int a, int b)	{	//求解组合数
		return	1ll*U[a]*D[b]%P*D[a-b]%P;
}

int		Work(int N, int A, int B)	{
		int	ret= 0;
		For(x0, 0, N)	{	//枚举其中一种空挡的个数
			int	x1= N - x0 + A - B,
				x2= N - x0 + B - A;	//求解另外两种
			
			if	(x1 < 0 || x2 < 0 || x1%2 || x2%2)	continue;
			
			x1>>= 1;
			x2>>= 1;
			
			int	c= A - x1 - x0;
			if	(c < 0)	continue;
			
			ret= (ret + 1ll *C(N + c - 1, c) * P2[x0] % P * U[N] % P * D[x0] % P * D[x1] % P * D[x2] % P) % P;	//计算答案
		}
		
		return	ret;
}

class	LittleElephantAndBoard{
	public:
		int		getNumber(int M, int R, int G, int B){
			U[0]= 1;
			For(i, 1, n-1)	U[i]= 1ll*U[i-1]*i%P;
			
			D[n-1]= Pow(U[n-1], P-2);
			Rep(i, n-1, 1)	D[i-1]= 1ll*D[i]*i%P;
			
			P2[0]= 1;
			For(i, 1, n-1)	P2[i]= P2[i-1] * 2 % P;
			
			R= M - R;
			G= M - G;
			B= M - B;
			
			if	(R < 0 || G < 0 || B < 0)	return	0;
			
			int	Ans= Work(B+1, R, G);
			if	(B)		Ans= (Ans + 2ll*Work(B, R, G))%P;
			if	(B > 1)	Ans= (Ans + Work(B-1, R, G))%P;	//分情况统计答案
			
			return	Ans * 2 % P;
		}
};