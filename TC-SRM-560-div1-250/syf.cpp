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

int		N, M, S, Ans, A[n], B[n], C[n];

class	TomekPhone{
	public:
		int minKeystrokes(vector <int> frequencies, vector <int> keySizes){
			N= frequencies.size();
			For(i, 1, N)	A[i]= frequencies[i-1];
			
			M= keySizes.size();
			For(i, 1, M)	B[i]= keySizes[i-1], S+= B[i];
			
			if	(S < N)	return	-1;
			
			sort(A+1, A+N+1);	//ÅÅÐò²»µÈÊ½
			Rep(i, N, 1)	{
				int u= -1;
				For(j, 1, M)	if	(C[j] < B[j] && (u == -1 || C[j] < C[u]))	u= j;
				
				C[u]++;
				Ans+= C[u] * A[i];
			}
			
			return	Ans;
		}
};