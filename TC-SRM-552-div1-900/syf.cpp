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

#define n	1000005

int		C, S, M, V[n], L[n], R[n], F[n], Pri[n];

I64		N, Ans, A[n], g[2][n], G[n];

class	HolyNumbers{	//使用O(N^{\frac{3}{4}})的“洲哥筛”做法，详见2016集训队任之洲论文。
	public:
		int		ID(I64 x)	{	//取x是哪一个N/t的t。
			if	(x <= S)	return	x;
			return	M - N/x + 1;
		}
	
		int		Cal(int j, int i){
			return	max(0, R[j] - (i - 1));
		}
	
		I64		count(I64 N, int MaxP){
			::N= N;
			for (S= 1; 1ll*S*S <= N; S++);	S--;
			
			For(i, 1, S)	A[++ M]= i;
			Rep(i, S, 1)	if	(1ll*i*i != N)	A[++ M]= N/i;
			
			For(i, 2, MaxP)	if	(! V[i])	{
				Pri[++ C]= i;
				For(j, 2, MaxP/i)	V[i*j]= 1;
			}	//预处理质数
			
			int st= 0;
			for (; st <= C && Pri[st] <= S; st++);
			
			for (int i= 1, j= 1; i <= M; i++)	{
				for (; j <= C && Pri[j] <= A[i]; j++);
				F[i]= max(0, (j-1) - (st-1));
			}
			
			//对于所有N/t,预处理大于sqrt(N)的质数个数
			
			for (; C && Pri[C] > S; C--);
			
			for (int i= 1, l= 1, r= 1; i <= M; i++)	{
				for (; l <= C && 1ll*Pri[l]*Pri[l] <= A[i]; l++);
				for (; r <= C && Pri[r] <= A[i]; r++);
				
				L[i]= l;
				R[i]= r-1;
			}
			
			g[0][M]= 1;
			for (int i= 1, j= 1; i <= C; i++)	{	//洲哥筛
				int p= i&1, q= p^1;
				
				for (; L[j] == i; j++)	{
					G[j]+= g[q][j];
					Ans+= G[j] * Cal(j, i);
				}	//将小于N^{\frac{3}{4}}的不处理
				
				For(k, j, M)	g[p][k]= 0;
				For(k, j, M)	{
					g[p][k]+= g[q][k];
					
					for (I64 rev= A[k] / Pri[i], c= 1; rev; rev/= 1ll*Pri[i]*Pri[i], c+=2){	//枚举新加入的质数的指数，转移。
						int t= ID(rev);
						if	(t >= j)	g[p][t]+= g[q][k];
							else	Ans+= g[q][k] * Cal(t, i+1), G[t]+= g[q][k];
					}
				}
			}
			
			For(j, 1, M)	{	//计算答案
				if	(L[j] == C+1)	G[j]+= g[C&1][j];
				Ans+= G[j] * (F[j] + 1);
			}
			
			return	Ans;
		}
};