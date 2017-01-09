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
#define P	1000000009

#define Vec	vector<int>

int		N, M, A[n], V[n][n];

map<Vec, int>	F[n];

int		DFS(int i, Vec S){	//暴搜
		if	(i == 0)	return	1;
		if	(F[i].count(S))	return	F[i][S];
		
		int ret= 0;
		For(j, 1, M)	{	//枚举放的位置
			Vec	T= S;
			int flag= 1;
			
			For(k, 1, M)	{	//验证
				int t= max(0, A[i] - abs(j-k));
				if	(t)	{
					if	(V[i][k] && t <= S[k])	flag= 0;
					lf	(! V[i][k] && t > S[k])	flag= 0;
				}
				lf	(V[i][k])	flag= 0;
				
				if	(! flag)	break;
				T[k]= max(T[k], t);
			}
			
			if	(! flag)	continue;
			ret= (ret + DFS(i-1, T)) % P;
		}
		
		return	F[i][S]= ret;
}

class	Mountains{
	public:
		int countPlacements(vector <int> heights, vector <string> visibility){
			N= heights.size();
			For(i, 1, N)	A[i]= heights[i-1];
			
			M= visibility[0].length();
			For(i, 1, N)	For(j, 1, M)	V[i][j]= (visibility[i-1][j-1] == 'X');
			
			//预处理
			
			Vec	S;
			For(i, 0, M)	S.push_back(0);
			
			return	DFS(N, S);
		}
};