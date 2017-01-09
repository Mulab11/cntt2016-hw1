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

int		N, M, F[n], D[n];

char	A[n][n];

vector<string>	Ans;

int		Get(int x)	{
		if	(F[x] == x)	return	x;
		int t= Get(F[x]);
		
		D[x]^= D[F[x]];
		return	F[x]= t;
}

bool	Merge(int x, int y, int w)	{	//并查集
		int fx= Get(x), fy= Get(y);
		
		if	(fx != fy)	F[fx]= fy, D[fx]= w^D[x]^D[y];
		lf	(D[x]^D[y]^w)	return	0;
		
		return	1;
}

bool	check()	{	//用二分图判断合法性
		For(i, 1, N)	F[i]= i, D[i]= 0;
		
		For(i, 1, M)	{
			For(a, 1, N)	if	(A[a][i] != '?')
				For(b, a+1, N)	if	(A[b][i] != '?')	{
					if	(! Merge(a, b, A[a][i] != A[b][i]))	return	0;
				}
		}
		
		return	1;
}

class	ThreeColorability{
	public:
		vector <string> lexSmallest(vector <string> cells){
			N= cells.size();
			M= cells[0].length();
			
			For(i, 1, N)	For(j, 1, M)	A[i][j]= cells[i-1][j-1];
			
			if	(! check())	return	Ans;
			
			For(i, 1, N)	For(j, 1, M)	if	(A[i][j] == '?')	{	//逐位确定答案
				A[i][j]= 'N';
				if	(check())	continue;
				A[i][j]= 'Z';
			}
			
			For(i, 1, N)	{
				string	t= "";
				For(j, 1, M)	t+= A[i][j];
				
				Ans.push_back(t);
			}
			
			return	Ans;
		}
};