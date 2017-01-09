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

#define n	20

int		N, K, mo;

int		Pow(int a,int b, int P){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

int		C(int a, int b)	{	//暴力求解组合数
		static	int	rev[n];
		
		For(i, 1, b)	rev[i]= a-i+1;
		For(i, 2, b)	{
			int x= i;
			
			For(j, 1, b){
				int t= __gcd(x, rev[j]);
			
				x/= t;
				rev[j]/= t;
			}
			
			assert(x == 1);
		}
		
		int ret= 1;
		For(i, 1, b)	ret= 1ll*ret*rev[i]%mo;
		return	ret;
}

struct	Mat{	//矩阵乘法
		int 	A[n][n];
		
		Mat()	{
			for	(int i= 0; i <=  K; i ++)
				for	(int j= 0; j <=  K; j ++)	A[i][j]= 0;
		}
		
		Mat	operator *	(const Mat&b)	const{
			Mat	c, a= *this;
			
			for	(int i= 0; i <=  K; i ++)
				for	(int k= 0; k <=  K; k ++)	if  (a.A[i][k])
					for	(int j= 0; j <=  K; j ++)if  (b.A[k][j])
						c.A[i][j]= (1ll* a.A[i][k]* b.A[k][j] + c.A[i][j])%mo;
			return	c;
		}
		Mat	operator ^	(int T)	const{
			Mat	ret, a=*this;
			for	(int i= 0; i <=  K; i ++)	ret.A[i][i]= 1;
			
			for (;;)	{
				if  (T&1)	ret= ret*a;
				
				T>>= 1;
				if  (T)		a= a*a;
					else	break;
			}
			return	ret;
		}
}S;

int		Cal(int B, int mo)	{
		int	ret= 0;
		::mo= mo;
		
		I64	x= B;
		for (; x <= N; x*= B)	{	//对于每一个幂次计算个数
			S= Mat();
			
			For(i, 1, K)	{	//构建矩阵
				For(j, 1, i)	S.A[j][i]= C(x+i-j-1, i-j);
				S.A[0][i]= 1;
			}
			S.A[0][0]= 1;
			
			S= S^(N / x);	//快速幂
			
			int t= (N / x) * x;
			For(i, 1, K)	ret= (ret + 1ll*S.A[0][i]*C(N-t+K-i-1, K-i)) % mo;
		}
		
		return	ret;
}

#define P	1000000009

class	MegaFactorial{
	public:
		int countTrailingZeros(int N, int K, int B){
			::N= N;
			::K= K;
			
			//根据B来确定是计算某一个质数的幂次作为答案
			
			if	(B == 6)	B= 3;
			lf	(B == 10)	B= 5;
			
			if	(B == 4)	return	1ll*(Cal(2, P) - Cal(2, 2) + P)*Pow(2, P-2, P)%P;	//求出答案模a的余数，就可以做到Ans向下除a取整后的模域下的答案
			if	(B == 9)	return	1ll*(Cal(3, P) - Cal(3, 2) + P)*Pow(2, P-2, P)%P;
			if	(B == 8)	return	1ll*(Cal(2, P) - Cal(2, 3) + P)*Pow(3, P-2, P)%P;
			
			return	Cal(B, P);
		}
}GTW;