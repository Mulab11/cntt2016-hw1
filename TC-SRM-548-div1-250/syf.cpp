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

class	KingdomAndTrees{
	public:
		#define FOR(i,a,b) for (int i = a; i <= b; i++)
	bool check(vector < int > h, int x) { //check that whether the spell level x can do
		int prev = 0, n = h.size();
		//prev store the height of the previous tree

		FOR (i, 0, n - 1) {
			//if we can make tree[i] higher than previous one
			if (h[i] + x <= prev) return false;
			//reset the value of prev for the next step
			prev = max(prev + 1, h[i] - x);
		}
		return true;
	}

	int minLevel(vector < int > heights) {
		int l = 0, r = 1000000000, res = -1;
		//binary search
		while (l <= r) {
			int m = (l + r) / 2;
			if (check(heights, m)) {
			//if spell level m can do it, we search in range [l, m - 1]
				res = m;
				r = m - 1;
			}
			else l = m + 1;
		}
		return res;
	}
};