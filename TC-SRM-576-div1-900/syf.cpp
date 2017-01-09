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

#define n	15
#define P	1000000009
#define INF	(1 << 30)

int		N, M;

struct	Hash{	//HASH表去重
	#define mo	23333
	
	int		D, st[mo], X[mo], Y[mo], Next[mo];
	
	void	Clear(){
		For(i, 1, D)	st[X[i] % mo]= 0;
		D= 0;
	}
	
	int		count(int x)	{
		for (int i= st[x%mo]; i; i= Next[i])
			if	(X[i] == x)	return	1;
		return	0;
	}
	
	int		ID(int x){
		for (int i= st[x%mo]; i; i= Next[i])
			if	(X[i] == x)	return	i;
		
		X[++ D]= x;
		Y[D]= 0;
		Next[D]= st[x%mo];
		st[x%mo]= D;
		
		return	D;
	}
	
	void	add(int x, int y)	{
		int t= ID(x);
		Y[t]+= y;
	}
	
	void	Cov(int x, int y)	{
		int t= ID(x);
		Y[t]= y;
	}
}F, G;

int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

vector<int>	H[n][n << 1];

class	CharacterBoard{
	public:
		int 	countGenerators(vector <string> A, int W, int i0, int j0){
			N= A.size();
			M= A[0].length();
			
			For(i, 0, N-1)	For(j, 1-M, M-1)	{	//预处理i行j列所代表的的数的因子
				I64 t= 1ll * i * W + j;
				if	(t <= 0)	continue;
				
				for (int l= max(1ll, (t-1)/W + 1); l <= t / l && l <= W; l++)
					if	(t % l == 0)	H[i][j+M].push_back(l), H[i][j+M].push_back(t/l);
			}
			
			For(x1, 0, N-1)	For(y1, 0, M-1)	{	
				G.Clear();
				
				For(x2, x1, N-1)	For(y2, 0, M-1)	//两两枚举冲突
				if	(y2 > y1 || x2 > x1)	{
					int	x= x2 - x1, y= y2 - y1 + M;
					
					if	(A[x1][y1] != A[x2][y2])	{
						For(i, 1, H[x][y].size())	F.Cov(H[x][y][i-1], -INF);	//枚举约束
					}	else	{
						For(i, 1, H[x][y].size())	if	(! G.count(H[x][y][i-1]))	F.add(H[x][y][i-1], 1), G.Cov(H[x][y][i-1], 1);
					}
				}
			}
			
			int	Ans= 1ll * (Pow(26, W+1) - 26) * Pow(25, P-2) % P * Pow(Pow(26, N*M), P-2) % P;
			
			For(i, 1, F.D)	{	//减去不合法的答案
				int	x= F.X[i], y= F.Y[i];
				
				Ans= (Ans - Pow(26, x - N*M + P-1)) % P;
				
				if	(y > 0)	{
					assert(x-N*M+y >= 0);
					Ans= (Ans + Pow(26, x-N*M+y)) % P;
				}
			}
			
			return	(Ans + P) % P;
		}
}GT;