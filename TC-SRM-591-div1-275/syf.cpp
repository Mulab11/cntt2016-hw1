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

#define	n	55

int		N, Ans, A[n];

class	TheTree{
	public:
		int 	maximumDiameter(vector <int> cnt){
			N= cnt.size();
			For(i, 1, N)	A[i]= cnt[i-1];
			A[0]= 1;
			
			For(i, 0, N)	{	//Ã¶¾Ù¼ÆËã´ð°¸
				int	t= N - i;
				For(j, i+1, N)	if	(A[j] >= 2)	t++;
					else	break;
				Ans= max(Ans, t);
			}
			
			return	Ans;
		}
};