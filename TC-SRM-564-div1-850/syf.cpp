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
#define P	1000000007

int		N, A[n], F[n][2][2];

int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

class	DefectiveAddition{
	public:
		int 	count(vector <int> cards, int M)	{
			N= cards.size();
			For(i, 1, N)	A[i]= cards[i-1];
			
			int	Ans= 0;
			Rep(d, 29, 0)	{	//枚举最大的高位，使得存在一个B_i这一位是0，A_i这一位是1
				int flag= (1 << (d+1)) & M;
				For(i, 1, N)	flag^= (1 << (d+1)) & A[i];
				if	(flag)	break;
				
				For(i, 0, N)	For(j, 0, 1)	For(k, 0, 1)	F[i][j][k]= 0;
				F[0][0][0]= 1;
				
				For(i, 1, N)	{	//枚举每一个数，Dp
					int t= (1 << d) & A[i];
					
					if	(! t)	{	//这一位是0，转移唯一
						For(j, 0, 1)	For(k, 0, 1)
							F[i][j][k]= (F[i][j][k] + 1ll*F[i-1][j][k]*((A[i]&((1<<d)-1)) + 1))%P;
					}	else	{	//这一位是1，两种转移
						For(j, 0, 1)	For(k, 0, 1)	{
							F[i][j^1][k]= (F[i][j^1][k] + 1ll*F[i-1][j][k]*((A[i]&((1<<d)-1)) + 1))%P;
							F[i][j][1]= (F[i][j][1] + 1ll*F[i-1][j][k]*(1 << d))%P;
						}
					}
				}
				
				Ans= (Ans + 1ll*F[N][((1<<d) & M) > 0][1]*Pow(1<<d, P-2)) % P;
			}
			
			For(i, 1, N)	M^= A[i];
			return	Ans + (M == 0);
		}
};