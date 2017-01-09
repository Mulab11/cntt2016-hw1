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

#define n	20
#define m	(1 << 18) + 5

int		U, A[n], cnt[m];

I64		F[m][n];

class	PolygonTraversal{
	public:
		I64		count(int N, vector <int> points){
			U= (1 << N) - 1;
			
			{
				int	st= 0;
				For(i, 1, points.size())	st|= 1 << (points[i-1] - 1);
				F[st][points.back()]= 1;
			}
			
			//状压DP，F[i][j]表示N个点的使用状态下， 结尾是j点的方案数。
			
			For(i, 1, U)	{
				cnt[i]= cnt[i >> 1] + (i&1);
				
				For(j, 1, N)	if	(F[i][j]){	
					For(k, 1, N)	A[k]= 0;
					For(k, 1, N)	if	(((1 << (k-1)) & i) && k != j)	A[k]= 1;
					For(k, 1, N)	A[k]+= A[k-1];
					
					For(k, 1, N)	if	(! ((1 << (k-1)) & i))	{	//枚举下一个是什么
						int	x= min(j, k), y= max(j, k);
						
						if	(A[y] - A[x-1] > 0 && A[y] - A[x-1] < cnt[i]-1)
							F[i | (1 << (k-1))][k]+= F[i][j];
					}
				}
			}
			
			I64	Ans= 0;
			For(i, 1, N)	if	((i-points[0]+N-1)%N+1 != 1 && (points[0]-i+N-1)%N+1 != 1)	Ans+= F[U][i], printf("%d %lld\n", i, F[U][i]);
			
			return	Ans;
		}
}GTW;