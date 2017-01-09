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

int		N, M, cnt[n][2];

class	TheDevice	{
	public:
		int minimumAdditional(vector <string> plates){
			N= plates.size();
			M= plates[0].length();
			
			For(i, 1, N)	For(j, 1, M)	//预处理每一位的情况
				cnt[j][plates[i-1][j-1] - '0']++;
			
			int	Ans= 0;
			For(i, 1, M)	Ans= max(Ans, max(0, 2 - cnt[i][1]) + max(0, 1 - cnt[i][0]));	//对于每一位取最值更新答案
			
			return	Ans;
		}
};