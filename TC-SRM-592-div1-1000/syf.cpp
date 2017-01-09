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

#define	n	35

const	DB	PI= acos(-1), eps= 1e-9;

int		N, A[n], G[n];

vector<int>	Ans;

struct	Cpx{	//复数域的操作
		DB	x, y;
		
		Cpx	operator +	(const Cpx&b)	{
			return	(Cpx){x+b.x, y+b.y};
		}
		
		Cpx	operator *	(const Cpx&b)	{
			return	(Cpx){x*b.x - y*b.y, x*b.y + y*b.x};
		}
		
		Cpx	Sqrt()	{	//复数开根
			if	(abs(y) < eps)	{
				if	(x >= 0)	return	(Cpx){sqrt(x), 0};
				return	(Cpx){0, sqrt(-x)};
			}
			
			DB	b= sqrt((-4*x + sqrt(16*(x*x+y*y))) / 8);
			DB	a= sqrt((4*x + sqrt(16)));
			return	(Cpx){a, b};
		}
		
		void	minus(){
			x*= -1;
			y*= -1;
		}
}B[n], C[n], w[2][n];

bool	check()	{
		For(i, 1, N-1)	if	(G[i] != G[N-i])	return	0;
		For(i, 0, N-1)	if	(G[i] < 0)	return	0;
	
		For(i, 0, N-1)	{
			int	t= 0;
			For(j, 0, N-1)	t+= G[j] * G[(i-j+N)%N];
			if	(t != A[i])	return	0;
		}
		return	1;
}

void	Upd()	{	//更新答案
		if	(! Ans.size())	{
			For(i, 0, N-1)	Ans.push_back(G[i]);
		}
		else	{
			int	flag= 0;
			For(i, 0, N-1)	if	(Ans[i] != G[i]){
				if	(Ans[i] < G[i])	return;
				flag= 1;
				break;
			}
			
			if	(flag)	{
				For(i, 0, N-1)	Ans[i]= G[i];
			}
		}
}

class	SplittingFoxes2{
	public:
		vector<int> getPattern(vector<int> amount)	{
			N= amount.size();
			For(i, 0, N-1)	A[i]= amount[i];
			
			For(i, 0, N-1)	{
				w[0][i]= (Cpx){cos(2*PI/N*i), sin(2*PI/N*i)};
				w[1][i]= (Cpx){cos(2*PI/N*i), -sin(2*PI/N*i)};
			}	//预处理单位根
			
			For(i, 0, N-1)	{
				Cpx	t= (Cpx){0, 0};
				For(j, 0, N-1)	t= t + w[0][i*j%N] * (Cpx){1. * A[j], 0};
				B[i]= t.Sqrt();
			}	//将读入的数开根，取其中一个解
			
			int	U= (1 << (N/2 + 1)) - 1;
			For(s, 0, U)	{	//枚举将那些根取负
				For(i, 0, N-1)	C[i]= B[i];
				For(i, 0, N-1)	if	((1 << min(i, N-i)) & s)	C[i].minus();
				
				For(i, 0, N-1)	{	//计算DFT
					Cpx	t= (Cpx){0, 0};
					For(j, 0, N-1)	t= t + w[1][i*j%N] * C[j];
					G[i]= (int)(t.x / N + .5);
				}
				
				if	(check())	Upd();	//验证
			}
			
			if	(! Ans.size())	Ans.push_back(-1);
			return	Ans;
		}
}GTW;