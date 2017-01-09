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
#define INF	(1 << 30)

int		N, C1, C2, Ans, A[n], B[n];

void	Work()	{	//贪心计算贡献
	//	For(i, 0, 25)	if	(A[i] != INF)	printf("%d ", A[i]);
	//	puts("");
	
		int	ret= 0, last= -INF;
		for (int i= 0, j= 0, k; i <= 25; )
		if	(A[i] != INF)	{
			if	(A[i] <= last)	return;
			
			for (j= i; j <= 25 && (A[j] == A[i] || A[j] == INF); j++)
				if	(A[j] == A[i])	k= j;
			
		//	printf("%d %d %d\n", i, k, A[i]);
			
			last= A[i];
			if	(k <= last)	ret+= (last - i) * C1;
			lf	(i >= last)	ret+= (k - last) * C2;
				else	ret+= (last - i) * C1 + (k - last) * C2;
			i= j;
		}
		else	i++;
		
	//	printf("%d\n", ret);
		
		Ans= min(Ans, ret);
}

class	NextAndPrev{
	public:
		int getMinimum(int nextCost, int prevCost, string start, string goal){
			if	(start == goal)	return	0;	//特判相同的时候
			
			C1= nextCost;
			C2= prevCost;
			For(i, 0, 25)	A[i]= INF;
			
			N= start.length();
			For(i, 1, N)	{
				int	a= start[i-1] - 'a', b= goal[i-1] - 'a';
				
			//	printf("%d %d\n", a, b);
				
				if	(A[a] == INF)	A[a]= b;
				lf	(A[a] != b)	return	-1;
			}
			
			int	Wei= A[0], flag= 0;
			For(i, 1, 25)	if	(A[i] == INF || (A[i] - i + 26) % 26 != Wei)	flag= 1;
			if	(! flag)	return	-1;
			
			//预处理
			
			Ans= INF;
			For(Tim, 1, 26)	{	//枚举A串的断点
				For(i, 0, 25)	B[i]= A[i];
				
				For(i, 0, 26)	{	//枚举将A中某一个后缀-26
					For(j, 0, 25)	{
						A[j]= B[j];
						if	(A[j] != INF && A[j] > i)	A[j]-= 26;
					}
					Work();
				}
				
				For(i, 0, 26)	{	//枚举将A中某一个前缀+26
					For(j, 0, 25)	{
						A[j]= B[j];
						if	(A[j] != INF && A[j] < i)	A[j]+= 26;
					}
					Work();
				}
				
				For(i, 0, 25)	A[i]= INF;
				
				For(i, 1, start.length())	{	//还原
					int	a= (start[i-1] - 'a' + Tim) % 26, b= (goal[i-1] - 'a' + Tim) % 26;
					A[a]= b;
				}
			}
			
			if	(Ans == INF)	return	-1;
			return	Ans;
		}
}GTW;