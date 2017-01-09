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

map<PA, int>	F[n];

int		Rev(int A)	{
		static	int	num[15];
		
		*num= 0;
		for (; A; A/= 10)	num[++ *num]= A%10;
		
		int	ret= 0;
		For(i, 1, *num)	ret= ret*10 + num[i];
		return	ret;
}

int		Work(int d, int A, int B)	{
	//	printf("%d %d %d\n", d, A, B);
	
		if	(A == B)	return	1;
		if	(d > 200)	return	0;
		
		if	(F[d].count(MK(A, B)))	return	F[d][MK(A,B)];	//用Map存储状态
		
		if	(d&1)	{	//转移
			if	(A/10)	F[d][MK(A, B)]|= Work(d+1, A/10, B);
			F[d][MK(A, B)]|= Work(d+1, Rev(A), B);
		}	else	{
			F[d][MK(A, B)]= 1;
			if	(B/10)	F[d][MK(A, B)]&= Work(d+1, A, B/10);
			F[d][MK(A, B)]&= Work(d+1, A, Rev(B));
		}
		
		return	F[d][MK(A, B)];
}

class	TheNumberGame{
	public:
		string determineOutcome(int A, int B){
			return	Work(1, A, B) ? "Manao wins" : "Manao loses";	//状态数很少，可以暴搜求出一个局面的胜负性
		}
}GTW;