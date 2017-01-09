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

#define n	125
#define P	1234567891

int		col, K, Cal[n];

int		D, A[n], ID[10005];

int		C, Dex[n][n];

inline	void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
}

struct	Mat{	//矩阵乘法 + 快速幂
		int 	A[n][n];
		
		Mat()	{
			for	(int i= 0; i <= C; i ++)
				for	(int j= 0; j <= C; j ++)	A[i][j]= 0;
		}
		
		Mat	operator *	(const Mat&b)	const{
			Mat	c, a= *this;
			
			for	(int i= 0; i <= C; i ++)
				for	(int k= 0; k <= C; k ++)	if  (a.A[i][k])
					for	(int j= 0; j <= C; j ++)if  (b.A[k][j])
						c.A[i][j]= (1ll* a.A[i][k]* b.A[k][j] + c.A[i][j])%P;
			return	c;
		}
		Mat	operator ^	(I64 K)	const{
			Mat	ret, a=*this;
			for	(int i= 0; i <= C; i ++)	ret.A[i][i]= 1;
			
			for (;;)	{
				if  (K&1)	ret= ret*a;
				
				K>>= 1;
				if  (K)		a= a*a;
					else	break;
			}
			return	ret;
		}
}S;

int		Num(int x)	{	//计算最大值
		int	a= x/1000, b= x/100%10, c= x/10%10, d= x%10;
		return	max(a, max(b, max(c, d)));
}

int		Wei(int x)	{	//判断两个状态是否可以相接
		int	a= x/1000, b= x/100%10, c= x/10%10, d= x%10;
		
		return	(a == b) + (a == c) + (b == d) + (c == d);
}

int		Gui(int x, int y){	//判断合法性
		int	a0= x/1000, b0= x/100%10, c0= x/10%10, d0= x%10;
		int	a1= y/1000, b1= y/100%10, c1= y/10%10, d1= y%10;
		
		return	(a0 == a1) + (b0 == b1) + (c0 == c1) + (d0 == d1);
}

int		calc(int x){	//计算方案数
		static	int	p[9];
		Rep(i, 8, 1)	p[i]= x%10, x/= 10;
		
		int	tot= max(p[1], max(p[2], max(p[3], p[4]))), ret= 1;
		if	(tot > col)	return	0;
		
		For(i, 5, 8)	{
			int flag= 1;
			For(j, 1, i-1)	if	(p[i] == p[j]){
				flag= 0;	break;
			}
			if	(flag)	ret= 1ll*ret*(col - tot)%P, tot++;
		}
		
		return	ret;
}

int		Trans(int x)	{	//维护并查集操作后的状态
		static	int	p[5], q[5], tot;
		
		p[1]= x/1000, p[2]= x/100%10, p[3]= x/10%10, p[4]= x%10;
		tot= 0;
		
		For(i, 1, 4)	{
			int flag= 0;
			For(j, 1, i-1)	if	(p[j] == p[i])	{
				q[i]= q[j];	flag= 1;	break;
			}
			if	(! flag)	q[i]= ++tot;
		}
		
		return	q[1]*1000 + q[2]*100 + q[3]*10 + q[4];
}

void	DFS(int d, int tot, int num){	//预处理出所有可行的最小表示法
		if	(d > 4)	{
			A[++ D]= num;
			ID[num]= D;
			
		//	printf("%d %d %d %d %d\n", D, num, Wei(num), Num(num), Trans(num));
			return;
		}
		
		DFS(d+1, tot+1, num*10 + tot+1);
		For(i, 1, tot)	DFS(d+1, tot, num*10 + i);
}

void	Pre(int d, int tot, int num){	//预处理转移系数
		if	(d > 8)	{
			int	u= ID[num/10000], v= ID[Trans(num%10000)];
			int	t= Wei(A[v]) + Gui(num/10000, num%10000);
			
		//	if	(num == 12212112)	printf("%d %d %d %d %d\n", num, u, v, t, calc(num));
			
			For(i, 0, K-t)	Plu(S.A[Dex[u][i]][Dex[v][i+t]], calc(num));
			return;
		}
		
		Pre(d+1, tot+1, num*10 + tot+1);
		For(i, 1, tot)	Pre(d+1, tot, num*10 + i);
}

class	TheBrickTowerHardDivOne{
	public:
		int		find(int col, int K, I64 N)	{
			::K= K;
			::col= col;
			
			Cal[0]= 1;
			For(i, 1, 4)	Cal[i]= 1ll*Cal[i-1]*(col-i+1)%P;	//预处理方案数
			
			DFS(1, 0, 0);
			For(i, 1, D)	For(j, 0, K)	Dex[i][j]= ++C;
			For(i, 1, D)	if	(Wei(A[i]) <= K)	S.A[0][Dex[i][Wei(A[i])]]= Cal[Num(A[i])];	//连边，并构建矩阵
			
		/* 	puts("");
			For(i, 0, C)	{
				For(j, 0, C)	printf("%d ", S.A[i][j]);
				puts("");
			} */
			
			Pre(1, 0, 0);
			
			C++;
			For(i, 1, C)	S.A[i][C]= 1;
			S= S^(N+1);
			
			return	S.A[0][C];
		}
}GTW;