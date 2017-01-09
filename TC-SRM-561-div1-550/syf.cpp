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

#define n	505

int		N, Tim, V[n], H[n], SG[n], GT[n], mex[n];

struct	Nod{
		int x, y, r;
}A[n];

bool	Cmp(const Nod&a, const Nod&b)	{	//将所有圆按照半径排序
		return	a.r < b.r;
}

bool	Inside(const Nod&a, const Nod&b)	{
		DB	dis= sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
		return	a.r + dis <= b.r;
}

class	CirclesGame{
	public:
		string whoCanWin(vector <int> x, vector <int> y, vector <int> r){
			N=	x.size();
			For(i, 1, N)	A[i]= (Nod){x[i-1], y[i-1], r[i-1]};
			sort(A+1, A+N+1, Cmp);
			
			For(i, 1, N)	{	//逐个枚举每一个圆，计算它的SG值
				Tim++;
				
				For(j, 1, i)	if	(Inside(A[j], A[i]))	{	//枚举它的每一个后继
					if	(i != j && ! V[j])	V[j]= i, GT[i]^= SG[j];
					++ *H;
					
					int	t= 0;
					For(k, 1, i-1)	if	(Inside(A[j], A[k]) || Inside(A[k], A[j]))	H[k]= *H;
					Rep(k, i-1, 1)	if	(Inside(A[k], A[i]) && H[k] != *H && (V[k] == i || H[V[k]] == *H))	t^= SG[k];	//计算SG
					t^= GT[j];
					
					mex[t]= Tim;
				}
				
				for (; mex[SG[i]] == Tim; SG[i]++);
			}
			
			int	Ans= 0;
			For(i, 1, N)	if	(! V[i])	Ans^= SG[i];
			return	Ans ? "Alice" : "Bob";
		}
}GTW;