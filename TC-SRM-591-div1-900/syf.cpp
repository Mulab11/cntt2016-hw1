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

class	StringPath{
	static const int MOD = 1000000009; 
	I64 dp[9][9][1<<8][1<<8];
	string A, B;
	int n, m;
	
	public:
		int newMask(int y, int prefix, bool eq)
		{
			bool prev = 0;
			if (y >= 1) {
				prev = ( (prefix & (1<<(y-1)) ) != 0 );
			}
			bool up = prefix & (1<<y);
			if (eq && (prev || up) ) {
				// Add column y:
				return prefix | (1<<y);
			} else {
				// Remove column y (if it is in the set):
				return prefix - (prefix & (1<<y));
			}
		}
		 
		I64 f(int x, int y, int prefixA, int prefixB)
		{
			I64 & res = dp[x][y][prefixA][prefixB];
			if (res == -1) {
				if (x == n) {
					//base case: We need (m-1) to be in both sets:
					res = ( (prefixA & (1<<(m-1)) ) && (prefixB & (1<<(m-1)) ) ); 
				} else if (y == m) {
					// next row:
					res = f(x+1, 0, prefixA, prefixB);
				} else {
					//what to do with cell (x,y)?
					int p = x + y;
					res = 0;
					// Choose a letter:
					for (char ch = 'A'; ch <= 'Z'; ch++) {
						// update the sets:
						int pa2 = newMask(y, prefixA, A[p]==ch );
						int pb2 = newMask(y, prefixB, B[p]==ch );
						 
						// add partial result:
						res += f(x, y+1, pa2, pb2);
					}
					res %= MOD;
				}
			}
			return res;
		}
		 
		int countBoards(int n, int m, string A, string B)
		{
			this->n = n;
			this->m = m;
			this->A = A;
			this->B = B;
			 
			memset(dp, -1, sizeof(dp));
			 
			return f(0,0, 1, 1);
		}
};