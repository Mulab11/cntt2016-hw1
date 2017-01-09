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

class	FoxAndFencing{
	public:
		string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
		{
			if (d <= mov1 + rng1) {            
				return "Ciel"; // first move
			} else if (d + mov1 <= mov2 + rng2) {
				return "Liss"; // second move
			} else if ( (mov1 > mov2) && (mov2 * 2 + rng2 < mov1 + rng1) ) {
				return "Ciel";
			} else if ( (mov2 > mov1) && (mov1 * 2 + rng1 < mov2 + rng2) ) {
				return "Liss";
			} else {
				return "Draw";
			}
		}
};