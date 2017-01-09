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
#define m	3005

int		N, M, A[m][m], H[n][n];

I64		Now[3], Ans[3];

void	Cover(int x, int y)	{	//模拟
		For(j, 0, 2)	Now[j]= 0;
		
		For(i, 1, N)	For(j, 1, M)	{
			if	(! H[i][j])	continue;
			
			if	(A[x+i-1][y+j-1])	Now[A[x+i-1][y+j-1]-1]--;
			A[x+i-1][y+j-1]= H[i][j];
			Now[H[i][j]-1]++;
		}
}

class	PastingPaintingDivOne{
	public:
		vector<I64> countColors(vector <string> s, int T)	{
			N= s.size();
			M= s[0].length();
			For(i, 1, N)	For(j, 1, M)	{
				if	(s[i-1][j-1] == '.')	H[i][j]= 0;
				lf	(s[i-1][j-1] == 'R')	H[i][j]= 1;
				lf	(s[i-1][j-1] == 'G')	H[i][j]= 2;
					else	H[i][j]= 3;
			}
			
			For(i, 1, min(T, 2500))	{
				Cover(i, i);
				For(j, 0, 2)	Ans[j]+= Now[j];
			}
			
			if	(T > 2500)	{	//2500次后，每次的增量都是定值，直接累加答案。
				int t= T - 2500;
				For(j, 0, 2)	Ans[j]+= Now[j] * t;
			}
			
			return	{Ans[0], Ans[1], Ans[2]};
		}
};