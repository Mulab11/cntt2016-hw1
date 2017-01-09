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
#define Bit	bitset<n>

int		N, C;

I64		Ans, A[n];

Bit		H[n];

/*
I64		Cal(){
		int	ret= N, i= 1, j= 1;
		
		for (; i <= C && j <= N; )	{
			int t= i;
			for (; t <= C && ! H[t][j]; t++);
			
			if	(t > C)	{
				j++;
				continue;
			}
			
			swap(H[t], H[i]);
			ret--;
			
			For(k, i+1, C)	if	(H[k][j])	H[k]^= H[i];
			
			i++;
			j++;
		}
		
		For(k, i, C)	if	(H[k][0])	return	0;
		return	1ll << ret;
}
*/

Bit		F[n];

I64		Cal(){
		For(i, 1, N)	F[i].reset();
		
		int	ret= N;
		For(i, 1, C)	{	//线性基
			Bit	x= H[i];
			int	flag= 0;
			
			Rep(j, N, 1)	if	(x[j]){
				if	(F[j].count() == 0)	{
					F[j]=x;
					flag= 1;
					ret--;
					break;
				}
				x^= F[j];
			}
			
			if	(! flag && x[0])	return	0;
		}
		
		return	1ll << ret;
}

class	XorCards{
	public:
		I64		numberOfWays(vector<I64> number, I64 M)	{
			N= number.size();
			For(i, 1, N)	A[i]= number[i-1];
			
			M++;
			For(i, 0, 50)	if	((1ll << i) & M)	{	//从最高位枚举小于的位
				C= 0;
				For(j, i, 50)	{	//建立方程
					H[++ C].reset();
					For(k, 1, N)	if	((1ll << j) & A[k])	H[C][k]= 1;
					
					if	(j == i)	H[C][0]= 0;
						else	H[C][0]= ((1ll << j) & M) > 0;
				}
				Ans+= Cal();	//2的自由元个数次幂就是答案
			}
			
			return	Ans;
		}
}GTW;