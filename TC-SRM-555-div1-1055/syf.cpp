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
#define Bit	bitset<n>

int		N, A[n], B[n], V[n], sum[n];

I64		Ans;

Bit		G[n];

void	DFS(int d, int flag, Bit x){	//容斥
		if	(d > N)	{
			if	(flag)	Ans+= flag * (1ll << (x.count()));
			return;
		}
		
		if	(flag && x.count() == 0)	{
			if	(! sum[d])	Ans+= flag * (1ll << (x.count()));
			return;
		}
		
		DFS(d+1, flag, x);	//不选
		if	(V[d])	{	//选
			if	(! flag)	DFS(d+1, 1, G[d]);
				else	DFS(d+1, -flag, x & G[d]);
		}
}

class	MapGuessing{
	public:
		I64		countPatterns(string goal, vector <string> GT)	{
			N= goal.length();
			For(i, 1, N)	A[i]= goal[i-1] - '0';
			
			string	Code= "";
			For(i, 1, GT.size())	Code= Code + GT[i-1];
			
			For(i, 1, N)	{	//预处理每一个位置作为指针起点后，可以覆盖到哪些位置。
				For(j, 1, N)	B[j]= -1;
				
				int	x= i, GTW= 0;
				For(j, 1, Code.length())	{	//模拟操作
					if	(Code[j-1] == '<')	x--;
					lf	(Code[j-1] == '>')	x++;
					lf	(Code[j-1] == '0')	B[x]= 0;
						else	B[x]= 1;
					
					if	(x < 1 || x > N)	{	//判断
						GTW= -1;	break;
					}
					
					int	flag= 1;
					For(k, 1, N)	if	(B[k] != -1 && B[k] != A[k])	flag= 0;
					if	(! flag)	continue;
					
					GTW= 1;
					For(k, 1, N)	if	(B[k] != -1)	G[i][k]= 1;	//取最大值
				}
				
				if	(GTW == -1)	V[i]= 0;
					else	V[i]= 1;
			}
			
			Rep(i, N, 1)	sum[i]= sum[i+1] + (V[i] == 1);
			
			DFS(1, 0, G[0]);
			
			return	Ans;
		}
};