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

int		NA, NB, SA, SB, SC, M, A[n], B[n], C[n], V[n];

int		Ans= -1;

bool	Cmp(int a, int b)	{
		return	a > b;
}

void	DFS(int d, int a, int b, int sa, int sb){	//O(2^M)枚举每一道的siz
		if	(d > M)	{
			if	(sa > SA || sb > SB)	return;
			
			int	ret= 0, i= 0, j= 0;
			For(k, 1, M)	{	//贪心判断
				if	(V[k] == 0 && i < NA)	ret+= min(A[++i], C[k]);
				lf	(V[k] == 1 && j < NB)	ret+= min(B[++j], C[k]);
			}
			
			Ans= max(Ans, ret);
			return;
		}
		
		V[d]= 0;
		DFS(d+1, a+1, b, sa+C[d], sb);
		
		V[d]= 1;
		DFS(d+1, a, b+1, sa, sb+C[d]);
}

class	ICPCBalloons{
	public:
		int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted){
			For(i, 1, balloonSize.length())
				if	(balloonSize[i-1] == 'M')	NA++, A[NA]= balloonCount[i-1], SA+= A[NA];
					else	NB++, B[NB]= balloonCount[i-1], SB+= B[NB];
			
			M= maxAccepted.size();
			For(i, 1, M)	C[i]= maxAccepted[i-1], SC+= C[i];
			
			//预处理
			
			sort(A+1, A+NA+1, Cmp);
			sort(B+1, B+NB+1, Cmp);
			sort(C+1, C+M+1, Cmp);
			
			Ans= -1;
			DFS(1, 0, 0, 0, 0);
			
			if	(Ans == -1)	return	-1;
			return	SC - Ans;
		}
};