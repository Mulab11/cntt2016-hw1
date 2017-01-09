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

#define	n	25

int		N, A[n];

class	TheJediTest{
	public:
		int minimumSupervisors(vector <int> students, int K){	//贪心
			N= students.size();
			For(i, 1, N)	A[i]= students[i-1];
			
			int	rev1= 0, rev2= 0, Ans= 0;
			For(i, 1, N)	{	//分情况特判
				if	(! rev1 && ! rev2)	{
					Ans+= A[i] / K;
					rev1= A[i] % K;
				}
				lf	(! rev2)	{
					if	(rev1 + A[i] < K)	rev2= rev1, rev1= A[i];
					else	{
						Ans+= (rev1 + A[i]) / K;
						
						int t= (rev1 + A[i]) / K * K - rev1;
						rev2= 0, rev1= A[i] - t;
					}
				}
				else	{
					Ans+= (rev2 - 1) / K + 1;
					int t= ((rev2 - 1 ) / K + 1) * K - rev2;
					
					if	(t <= rev1)	{
						rev2= rev1 - t;
						rev1= A[i];
					}
					else	{
						rev2= 0;
						rev1= max(0, A[i] - (t-rev1));
					}
					
					if	(rev1 + rev2 >= K)	{
						Ans+= (rev1 + rev2) / K;
						
						int t= (rev1 + rev2) / K * K - rev2;
						rev2= 0;
						rev1-= t;
					}
				}
			}
			
			if	(rev1 + rev2)	Ans+= (rev1 + rev2 - 1) / K + 1;
			
			return	Ans;
		}
}GTW;