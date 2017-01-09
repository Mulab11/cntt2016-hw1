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

const	int	cx[]= {-1, 0, 1, 0}, cy[]= {0, -1, 0, 1};

class	RobotHerb{
	public:
		long long getdist(int T, vector <int> a){
			I64	x= 0, y= 0;
			int	k= 0;
			
			For(i, 1, min(T, 4))	For(j, 1, a.size()){	//将前4次的位置求出来，4次后方向不变。
				int s= a[j-1];
				
				x+= cx[k] * s;
				y+= cy[k] * s;
				
				k= (k + s) % 4;
			}
			
			int s= T / 4;
			x*= s;
			y*= s;
			
			For(i, 1, T % 4)	For(j, 1, a.size()){	//更新答案
				int s= a[j-1];
				
				x+= cx[k] * s;
				y+= cy[k] * s;
				
				k= (k + s) % 4;
			}
			
			return	abs(x) + abs(y);
		}
};