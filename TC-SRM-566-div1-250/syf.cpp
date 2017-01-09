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

int		A[n], E[n][n];

class	PenguinSledding{
	public:
		long long countDesigns(int N, vector <int> u, vector <int> v){
			For(i, 1, u.size())	A[u[i-1]]++, A[v[i-1]]++, E[u[i-1]][v[i-1]]= E[v[i-1]][u[i-1]]= 1;
			
			I64	Ans= 1 + u.size();
			For(i, 1, N)	Ans+= (1ll << A[i]) - 1 - A[i];	//枚举中点，计算方案
			
			For(i, 1, N)	For(j, i+1, N)	For(k, j+1, N)	//加上三角形的方案
				Ans+= E[i][j] && E[i][k] && E[k][j];
			
			return	Ans;
		}
};