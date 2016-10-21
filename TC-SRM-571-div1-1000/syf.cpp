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

int		N, V[n][n];

DB		X[n], Y[n], R[n], low[n], high[n], Dis[n][n];

map<PA, int>	G;

inline	void	Max(DB&a, DB b)	{a= max(a, b);}
inline	void	Min(DB&a, DB b)	{a= min(a, b);}

class	CandyOnDisk{
	public:
		string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
			if	(sx == tx && sy == ty)	return	"YES";	//特判
			
			For(i, 1, x.size())	{
				if	(G.count(MK(x[i-1], y[i-1])))	{
					Max(R[G[MK(x[i-1], y[i-1])]], r[i-1]);
					continue;
				}
				
				G[MK(x[i-1], y[i-1])]= ++N;
				X[N]= x[i-1];
				Y[N]= y[i-1];
				R[N]= r[i-1];
				
				low[N]= 2e9;
				high[N]= - 2e9;
			}	//将圆心相同的圆合并，取半径最大的圆。
			
			For(i, 1, N)	For(j, 1, N)
				Dis[i][j]= sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
			
			For(i, 1, N)	{
				DB	t= sqrt((sx-X[i])*(sx-X[i]) + (sy-Y[i])*(sy-Y[i]));
				if	(t <= R[i])	low[i]= high[i]= t;
			}	//预处理
			
			for	(int flag= 1; flag;)	{	//暴力迭代
				flag= 0;
				For(i, 1, N)	For(j, 1, N)	if	(i != j && !V[i][j]){
					if	(high[i] < Dis[i][j]-R[j] || low[i] > Dis[i][j]+R[j])	continue;	//如果无法更新则退出
					
					V[i][j]= 1;
					flag= 1;
					
					Min(low[i], max(0., Dis[i][j]-R[j]));
					Max(high[i], min(R[i], Dis[i][j]+R[j]));
					
					Min(low[j], max(0., Dis[i][j]-R[i]));
					Max(high[j], min(R[j], Dis[i][j]+R[i]));
					
					//i圆和j圆的low、high分别取并。
				}
			}
			
			For(i, 1, N)	{
				DB	t= sqrt((tx-X[i])*(tx-X[i]) + (ty-Y[i])*(ty-Y[i]));
				if	(low[i] < t && t < high[i])	return	"YES";
			}	//判断是否可行。
			
			return	"NO";
		}
};