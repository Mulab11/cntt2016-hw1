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

char	Cal(I64 x, I64 y, I64 t){
		I64 a= x+y, b= y;
		if	(a&1)	return	'.';	//先判断奇偶
		
		a>>= 1;
		if	(a < b)	return	'.';	//判断大小
		
		if	((a&b) != b)	return	'.';	//判断组合数模域下的值。
		if	(a >= t)	return	'.';
		
		if	(a&1)	return	'B';
		return	'A';
}

#define n	55

string	A[n];

class	CheckerExpansion{
	public:
		vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
			For(i, 0, h-1)	For(j, 0, w-1)	//对于每一个格子判断是否合法。
				A[i]+= Cal(x0+j, y0+h-i-1, t);
			
			vector<string>	Ans;
			For(i, 0, h-1)	Ans.push_back(A[i]);	//输出
			
			return	Ans;
		}
};