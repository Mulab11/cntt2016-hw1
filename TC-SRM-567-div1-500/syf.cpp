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
#define Vec	vector<int>

int		N, M, V[n], G[n], A[n][n];

bool	check(int s)	{
		For(i, 1, N)	V[i]= 0;
		V[s]= 1;
		
		For(j, 0, 25)	G[j]= 0;
		
		For(Tim, 0, 25)	{
			int u= -1;
			
			For(i, 0, 25)	if	(! G[i])	{	//每次枚举一个合法的字符删去
				int flag= 1;
				For(j, 1, N)	if	(! V[j] && A[j][i] > A[s][i])	flag= 0;
				
				if	(flag)	{
					u= i;	break;
				}
			}
			
			if	(u == -1)	return	0;
			
			For(j, 1, N)	if	(A[j][u] < A[s][u])	V[j]= 1;
			G[u]= 1;
		}
		
		For(i, 1, N)	if	(! V[i])	return	0;
		return	1;
}

class	StringGame{
	public:
		vector <int> getWinningStrings(vector <string> S){
			N= S.size();
			M= S[0].length();
			
			For(i, 1, N)	For(j, 1, M)	A[i][S[i-1][j-1]-'a']++;
			
			Vec	Ans;
			For(i, 1, N)	if	(check(i))	Ans.push_back(i-1);	//枚举答案，验证
			
			return	Ans;
		}
};