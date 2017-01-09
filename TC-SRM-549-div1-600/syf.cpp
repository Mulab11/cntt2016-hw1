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

#define n	15
#define m	1600005

int		N, M, C, D, U, A[n], B[n];

int		V[m], F[m], NumC[n], NumR[n];

PA		H[n];

inline	bool	Empty(int s, int i)	{
		return	s / B[i-1] % 3 == 2;
}
inline	int		Put(int s, int i, int x){
		return	s + (x-2)*B[i-1];
}

void	Pre(int s, int revC, int revH){	//预处理Dp处理
		if	(revC > revH)	return;
		if	(V[s] != -1)	return;
		
		if	(revC == 0)	{	//验证奇偶性是否合法
			int	flag= 1;
			For(i, 1, D)	NumC[H[i].fi]^= 1, NumR[H[i].se]^= 1;
			For(i, 1, N)	if	(NumC[i])	flag= 0;
			For(i, 1, M)	if	(NumR[i])	flag= 0;
			For(i, 1, D)	NumC[H[i].fi]^= 1, NumR[H[i].se]^= 1;
			
			V[s]= flag;
			return;
		}
		
		V[s]= 0;
		For(i, 1, D)	if	(Empty(s, i)){	//枚举放那一个
			int a= Put(s, i, 0), b= Put(s, i, 1);
			
			Pre(a, revC, revH-1);
			
			NumC[H[i].fi]^= 1;
			NumR[H[i].se]^= 1;
			Pre(b, revC-1, revH-1);
			NumC[H[i].fi]^= 1;
			NumR[H[i].se]^= 1;
			
			if	(V[a] == 1 || V[b] == 1)	V[s]= 1;
		}
}

void	Dp(int s, int revG){	//计算答案
		if	(revG == 0)	{
			F[s]= 0;	return;
		}
		if	(F[s] != -1)	return;
		
		For(i, 1, D)	if	(Empty(s, i)){	//枚举放哪一个
			int	ret= 1 << 30, a= Put(s, i, 0), b= Put(s, i, 1);
			
			if	(V[a] == 1)	{
				Dp(a, revG-1);
				ret= min(ret, F[a]);
			}
				
			if	(V[b] == 1)	{
				Dp(b, revG-1);
				ret= min(ret, F[b] + 1);
			}
			
			//分情况转移一下
			
			if	(ret != (1<<30))	F[s]= max(F[s], ret);
		}
}

class	MagicalHats{
	public:
		int		findMaximumReward(vector <string> board, vector <int> coins, int K){
			//预处理

			N= board.size();
			M= board[0].length();
			
			For(i, 1, N)	For(j, 1, M)
				if	(board[i-1][j-1] == 'H')	H[++ D]= MK(i, j);
			if	(K > D)	return	-1;
			
			C= coins.size();
			For(i, 1, C)	A[i]= coins[i-1];
			sort(A+1, A+C+1);
			For(i, 1, C)	A[i]+= A[i-1];
			
			B[0]= 1;
			For(i, 1, D)	B[i]= B[i-1] * 3;
			For(s, 0, B[D])	V[s]= F[s]= -1;
			
			//预处理每一个Dp状态是否合法，使用记忆化搜索
			
			U= B[D]-1;
			Pre(U, C, D);
			
			if	(V[U] != 1)	return	-1;
			
			//Dp出每一个状态的答案
			
			Dp(U, K);
			return	A[F[U]];
		}
};