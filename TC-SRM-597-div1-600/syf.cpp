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
#define m	200005
#define INF	(1 << 30)

#define eps	(1e-6)

int		N, M, U[m], D[m];

DB		L[m], R[m];

struct	Nod{	//向量运算
		int	x, y;
		
		Nod	operator -	(const Nod&b)	const{
			return	(Nod){x-b.x, y-b.y};
		}
		I64	operator *	(const Nod&b)	const{
			return	1ll*x*b.y - 1ll*y*b.x;
		}
}A[n], S, T;

map<PA, int>	G;

void	Upd(int x, DB y)	{	//更新每一维的最大最小值
		L[x]= min(L[x], y);
		R[x]= max(R[x], y);
}

class	ConvexPolygonGame{
	public:
		string winner(vector <int> X, vector <int> Y)	{
			N= X.size();
			For(i, 1, N)	A[i]= (Nod){X[i-1] + 100000, Y[i-1] + 100000}, G[MK(A[i].x, A[i].y)]= 1;
			A[N+1]= A[1];
			
			M= 200000;
			For(i, 0, M)	L[i]= 1e9, R[i]= - L[i];
			
			For(i, 1, N)	{
				Nod	a= A[i], b= A[i+1];
				if	(a.x > b.x)	swap(a, b);
				
				if	(a.x == b.x)	Upd(a.x, a.y), Upd(a.x, b.y);
				else	{
					For(j, a.x, b.x)	{
						DB	t= a.y + 1. * (b.y-a.y) * (j-a.x) / (b.x-a.x);
						Upd(j, t);
					}
				}
			}
			
			I64	tot= 0;
			For(i, 0, M)	{
				U[i]= ceil(L[i] - eps);
				D[i]= floor(R[i] + eps);
				
				if	(G.count(MK(i, U[i])))	U[i]++;
				if	(G.count(MK(i, D[i])))	D[i]--;
			
				if	(U[i] <= D[i])	tot+= D[i] - U[i] + 1;
			}	//计算总点数
			
			if	(tot > 200001)	return	"Masha";
			if	(tot < 3)	return	"Petya";	//特判
			
			int	flag= 0;
			For(i, 0, M)	For(j, U[i], D[i])	{	//枚举所有点，用叉积判断答案
				if	(! flag)	flag= 1, S= (Nod){i, j};
				lf	(flag == 1)	flag= 2, T= (Nod){i, j};
				lf	((T-S) * ((Nod){i, j} - S))	return	"Masha";
			}
			
			return	"Petya";
		}
}GTW;