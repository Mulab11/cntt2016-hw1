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

#define n	1005

int		N, M, Ans, A[n], V[n];

class	TeamContest{
	public:
		int worstRank(vector <int> S){	//Ì°ÐÄ½øÐÐÆ¥Åä
			M= max(S[0], max(S[1], S[2])) + min(S[0], min(S[1], S[2]));

			For(i, 4, S.size())	A[++ N]= S[i-1];
			sort(A+1, A+N+1);
			
			For(i, 1, N)	if	(! V[i]){
				int	k= -1;
				Rep(j, N, i+1)	if	(! V[j] && A[i] + A[j] > M)	k= j;
				
				if	(k == -1)	{
					V[i]= 1;
					For(j, i+1, N)	if	(! V[j])	{V[j]= 1; break;}
					For(j, i+1, N)	if	(! V[j])	{V[j]= 1; break;}
				}	else	{
					V[i]= 1;
					V[k]= 1;
					For(j, i+1, N)	if	(! V[j])	{V[j]= 1; break;}
					
					Ans++;
				}
			}
			
			return	Ans + 1;
		}
};