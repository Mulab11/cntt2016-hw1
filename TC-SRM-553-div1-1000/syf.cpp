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
#define PA	pair<I64, I64>

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
#define m	505
#define Vec	vector<int>

#define INF	(1ll << 40)

int		D, st[n];

PA		Dis[n];

struct	Lin{
		PA	c;
		int	v, next;
}E[m];

void	Link(int u, int v, PA c){
		E[++ D]= (Lin){c, v, st[u]};	st[u]= D;
}

PA		Plu(PA a, PA b){
		return	MK(a.fi + b.fi, a.se + b.se);
}

PA		Cal(int N, Vec s1, Vec t1, Vec l1, Vec s2, Vec t2, Vec l2, I64 len)	{
		D= 0;
		For(i, 0, N)	st[i]= 0;
		
		For(i, 1, N)	Link(i, i-1, MK(-1, 0));
		Link(N, 0, MK(-len, -1));
		Link(0, N, MK(len, 1));
		
		For(i, 1, s1.size()){
			int u= s1[i-1], v= t1[i-1], w= l1[i-1];
			
			if	(v > u)	Link(v, u, MK(-w, 0));
				else	Link(v, u, MK(len-w, 1));
		}
		
		For(i, 1, s2.size()){
			int u= s2[i-1], v= t2[i-1], w= l2[i-1];
			
			if	(v > u)	Link(u, v, MK(w, 0));
				else	Link(u, v, MK(w-len, -1));
		}
		
		//构图
		
		For(i, 0, N)	Dis[i]= MK(INF, INF);
		Dis[0]= MK(0, 0);
		
		int	relax= 0;
		PA	last;
		
		For(Tim, 1, N*N)	{	//贝尔曼福特算法求负环
			relax= 0;
			
			For(u, 0, N)	if	(Dis[u].fi < INF)
				for (int i= st[u], v; i; i= E[i].next)
					if	(Plu(Dis[u], E[i].c).fi < Dis[v= E[i].v].fi){
						Dis[v]= Plu(Dis[u], E[i].c);
						relax= 1;
						last= Dis[v];
					}
		}
		
		if	(! relax)	return	MK(1, 0);	//无负环
		return	MK(0, last.se);
}

class	YamanoteLine{
	public:
		I64		howMany(int N, Vec s1, Vec t1, Vec l1, Vec s2, Vec t2, Vec l2){
			I64	Min= -1, Max= -1;
			
			{	//二分下界
				I64 L= N-1, R= INF;
				for (; L + 1 < R; )	{
					I64 Mid= (L+R) >> 1;
					
					PA	ret= Cal(N, s1, t1, l1, s2, t2, l2, Mid);
					if	(ret.fi || ret.se < 0)	{
						if	(ret.fi)	Min= Mid;
						R= Mid;
					}	else	L= Mid;
				}
			}
			
			{	//二分上界
				I64 L= N-1, R= INF;
				for (; L + 1< R; )	{
					I64 Mid= (L+R) >> 1;
					
					PA	ret= Cal(N, s1, t1, l1, s2, t2, l2, Mid);
					if	(ret.fi || ret.se > 0)	{
						if	(ret.fi)	Max= Mid;
						L= Mid;
					}	else	R= Mid;
				}
			}
			
			if	(Min == -1 && Max == -1)	return	0;	//判断无解
			if	(Max > INF / 2)	return	-1;	//判断无限解
			return	Max - Min + 1;
		}
};