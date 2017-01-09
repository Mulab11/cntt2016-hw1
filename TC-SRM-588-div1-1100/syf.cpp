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
#define	m	2505

int		N, M, ID[n][n];

int		C, D, S, T, st[m];

int		Dis[m], Dep[m];

struct	Lin{
		int v, next;
}E[m << 1];

void	Link(int u, int v)	{
		if	(!u || !v)	return;
		
		E[++ D]= (Lin){v, st[u]};	st[u]= D;
		E[++ D]= (Lin){u, st[v]};	st[v]= D;
}

void	DFS(int u, int f, int d)	{	//DFS
		Dis[u]= Dep[u]= d;
		
		for (int i= st[u], v; i; i= E[i].next)
			if	((v= E[i].v) != f)	{
				DFS(v, u, d+1);
				Dep[u]= max(Dep[u], Dep[v]);
			}
}

class	GameInDarknessDiv1{
	public:
		string	check(vector <string> s){	//结论题，直接找是否有一个点，使得以这个为根时，他的儿子中深度大于等于3的有多少个。
			N= s.size();
			M= s[0].length();
			
			For(i, 1, N)	For(j, 1, M)
				if	(s[i-1][j-1] != '#')	{
					ID[i][j]= ++C;
					
					if	(s[i-1][j-1] == 'A')	S= C;
					if	(s[i-1][j-1] == 'B')	T= C;
				}
			
			For(i, 1, N)	For(j, 1, M)	{
				Link(ID[i+1][j], ID[i][j]);
				Link(ID[i][j+1], ID[i][j]);
			}	//建树
			
			For(p, 1, C)	{	//枚举点
				DFS(p, 0, 0);
				
				if	(Dis[S] < Dis[T] + 2)	continue;
				
				int	cnt= 0;
				for (int i= st[p]; i; i= E[i].next)	{
					int v= E[i].v;
					if	(Dep[v] >= 3)	cnt++;
				}
				
				if	(cnt >= 3)	return	"Bob wins";	//判断
			}
			
			return	"Alice wins";
		}
}GTW;