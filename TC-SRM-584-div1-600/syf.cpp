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

#define n	105

int		N, M, A[n], B[n], D[n], ID[n], cnt[n];

I64		Ans, F[n], G[n], C[n][n];

class	Excavations{
	public:
		I64		count(vector <int> kind, vector <int> depth, vector <int> found, int K){
			For(i, 1, found.size())	ID[found[i-1]]= ++M;
			
			N= kind.size();
			For(i, 1, N)	A[i]= ID[kind[i-1]], B[i]= D[i]= depth[i-1];
			
			sort(D+1, D+N+1);
			*D= unique(D+1, D+N+1) - D - 1;
			
			For(i, 0, N)	{
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= C[i-1][j-1] + C[i-1][j];
			}
			
			For(i, 1, *D)	{	//枚举最小值
			//	printf("--- %d\n", D[i]);
				
				For(j, 0, M)	cnt[j]= 0;
				
				int	tot= 0, gt= 0;
				For(j, 1, N)	{	//将合法的统计一下
					if	(B[j] <= D[i])	cnt[A[j]]++;
						else	tot++;
					
					if	(B[j] == D[i] && A[j])	gt++;	//用于减去不合法的方案数
				}
				
				int	flag= 1;
				For(j, 1, M)	if	(! cnt[j])	flag= 0;
				if	(! flag)	continue;
				
				For(j, 0, N)	G[j]= F[j], F[j]= 0;
				F[0]= 1;
				
			//	printf("%d %d\n", tot, gt);
			//	For(j, 1, M)	printf("%d ", cnt[j]);
			//	puts("");

				For(j, 1, M)	Rep(k, N, 0)	For(t, 1, min(k, cnt[j]-1))	F[k]+= F[k-t];	//背包，事实上还可以退背包优化
				
			//	For(j, 0, N)	printf("%lld ", F[j]);
			//	puts("");
				
				int	rev= K - M;
				For(j, 0, N)	{	//统计答案
					I64 t= F[j];
					if	(j >= gt)	t-= G[j - gt];
					Ans+= t * C[tot + j][rev];
				}
				
			//	printf("-- %lld\n", Ans);
			}
			
			return	Ans;
		}
}GTW;