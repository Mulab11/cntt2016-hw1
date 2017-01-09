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

#define	n	55

int		N;

DB		Ans, pro[n];

struct	Pot{	//向量的运算
		int	x, y;
		
		Pot	operator -	(const Pot&b)	const{
			return	(Pot){x-b.x, y-b.y};
		}
		int	operator *	(const Pot&b)	const{
			return	x*b.y - y*b.x;
		}
		int	operator /	(const Pot&b)	const{
			return	x*b.x + y*b.y;
		}
		int	len()	{
			return	x*x + y*y;
		}
}A[n];

class	Constellation{
	public:
		DB	expectation(vector <int> xx, vector <int> yy, vector <int> prob){
			N= xx.size();
			For(i, 1, N)	A[i]= (Pot){xx[i-1], yy[i-1]}, pro[i]= prob[i-1] * .001;
			
			For(i, 1, N)	For(j, 1, N)	if	(i != j)	{	//对任意对点对计算它们出现在结果的概率，累加即可
				DB	t= pro[i] * pro[j];
				
				For(k, 1, N)	if	(k != i && k != j)	{	//计算如果出现了i，j，就不能出现的点的概率
					if	((A[k]-A[i]) * (A[j]-A[i]) > 0)	t*= 1-pro[k];
					if	((A[k]-A[i]) * (A[j]-A[i]) == 0 )	{
						int	x= (A[k]-A[i]) / (A[j]-A[i]), l= (A[j]-A[i]).len();
						
						if	(x > l || x < 0)	t*= 1-pro[k];
					}
				}
				
				Ans+= t * (A[i]*A[j]);
			}
			
			return	Ans * .5;
		}
};