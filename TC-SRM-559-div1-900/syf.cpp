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

const	DB	PI= acos(-1), eps= 1e-11;

#define n	505
#define sqr(x)	((x)*(x))

int		N, C;

DB		X[n], Y[n], R[n];

struct	Opt{
		DB	x;
		int	v;
}Q[n];

bool	Cmp(const Opt&a, const Opt&b){
		return	a.x < b.x;
}

void	Push(DB l, DB r){	//加入队列
	//	printf("%.12lf %.12lf\n", l, r);
	
		for (; l < 0; l+= 2*PI);
		for (; l > 2*PI; l-= 2*PI);
		for (; r < 0; r+= 2*PI);
		for (; r > 2*PI; r-= 2*PI);
		
		if	(l <= r)	Q[++ C]= (Opt){l, 1}, Q[++ C]= (Opt){r, -1};
		else	{
			Q[++ C]= (Opt){l, 1}, Q[++ C]= (Opt){2*PI, -1};
			Q[++ C]= (Opt){0, 1}, Q[++ C]= (Opt){r, -1};
		}
}

bool	check(DB k)	{
	//	printf("-- %.12lf\n", k);
	
		C= 0;
		For(i, 2, N)	{
			DB	a= sqrt(sqr(X[i] - X[1]) + sqr(Y[i] - Y[1])),
				o= atan2(Y[i]-Y[1], X[i]-X[1]),
				v= acos(R[1] / a),
				b= sqrt(sqr(a) - sqr(R[1]));
			
		//	printf("%.12lf %.12lf %.12lf %.12lf\n", a, o, v, b);
			
			if	(k+R[i] <= a-R[1])	continue;	//没有交
			if	(k+R[i] <= b)	{	//没有越过切线
				DB	t= acos((sqr(R[1]) + a*a - sqr(k+R[i])) / (2*R[1]*a));
				Push(o-t, o+t);
			}	else	{	//越过公切线的单独计算
				DB	x= (R[i]+k-b) / R[1];

				if	(x >= PI - v)	return	0;
				v+= x;
				
				Push(o-v, o+v);
			}
		}
		
		Q[++ C]= (Opt){0, 0};
		Q[++ C]= (Opt){2*PI, 0};
		sort(Q+1, Q+C+1, Cmp);
		
		int	now= 0;
		for	(int i= 1, j; i <= C; i= j+1)	{	//计算圆弧并
			now+= Q[i].v;
			for (j= i; j < C && fabs(Q[j+1].x - Q[j].x) < eps; )	now+= Q[++ j].v;
			
			if	(j != C && now == 0)	return	1;
		}
		
		return	0;
}

class	CircusTents{
	public:
		DB	findMaximumDistance(vector <int> x, vector <int> y, vector <int> rad)	{
			N= x.size();
			For(i, 1, N)	X[i]= x[i-1], Y[i]= y[i-1], R[i]= rad[i-1];
			
			DB	l= 0, r= 30000;
			for (; l + eps < r; )	{	//二分答案
				DB	Mid= (l+r) * .5;
				if	(check(Mid))	l= Mid;
					else	r= Mid;
			}
			
			return	l;
		}
};