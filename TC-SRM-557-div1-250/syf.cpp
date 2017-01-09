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

class	FoxAndMountainEasy{
	public:
		string possible(int n, int h0, int hn, string h) {	//根据题意大力特判即可。
		  int m = h.length(), i, x = h0;
		  for (i=0;i<m;i++)
			if (h[i] == 'U') x++; else
			if (h[i] == 'D') x--;	//预处理
		  int d = x-hn;
		  if (d < 0) d = -d;
		  if (d > n-m) return "NO";
		  if (d % 2 != (n-m) % 2) return "NO";
		 int up = (n-m-d)/2;
		  if (hn > x) up += hn-x;
		  x = h0+up;
		  for (i=0;i<m;i++) {
			if (h[i] == 'U') x++; else
			if (h[i] == 'D') x--;
			if (x < 0) return "NO";
		  }
		  return "YES";
		}
};