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

int		N, A[n], V[n];

class	BinPacking{
	public:
		int minBins(vector <int> item){
			N= item.size();
			For(i, 1, N)	A[i]= item[i-1];
			sort(A+1, A+N+1);
			
			int	Ans= 0;
			Rep(i, N, 1)	if	(A[i] != 100 && ! V[i]){	//Ì°ÐÄÆ¥Åä
				V[i]= 1;
				Ans++;
				
				Rep(j, i-1, 1)	if	(! V[j] && A[j] + A[i] <= 300)	{
					V[j]= 1;	break;
				}
			}
			
			int	cnt= 0;
			For(i, 1, N)	if	(! V[i])	cnt++;
			
			if	(cnt)	Ans+=  (cnt-1)/3+1;
			
			return	Ans;
		}
};