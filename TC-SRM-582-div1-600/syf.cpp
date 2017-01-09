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

#define n	2505
#define P	1000000009

int		N, M, A[n];

int		F[n][n], Mul[n], Sum[n], Rev[n];

map<int, int>	G;

int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
}

class	ColorfulBuilding{
	public:
		int 	count(vector <string> color1, vector <string> color2, int L)	{
			string	C1= "", C2= "";
			
			For(i, 1, color1.size())	C1+= color1[i-1];
			For(i, 1, color2.size())	C2+= color2[i-1];
			
			N= C1.size();
			For(i, 1, N)	{
				int	t= C1[i-1] * 200 + C2[i-1];
				
				if	(G.count(t))	A[i]= G[t];
					else	A[i]= G[t]= ++M;
			}
			
			Sum[1]= F[1][A[N]]= 1;
			For(i, 1, N)	Mul[i]= Rev[i]= 1;
			
			//从朴素N^3的Dp，加些优化优化至N^2
			
			Rep(i, N-1, 1)	{
				int t= N-i, r= Pow(t, P-2);
				
				For(j, 1, t)	{
					Mul[j]= 1ll*Mul[j]*t%P;	//第一维为j的Dp数组全部乘上多少
					Sum[j]= 1ll*Sum[j]*t%P;	//第一维为j的DP数组总和
					Rev[j]= 1ll*Rev[j]*r%P;	//处理逆元
				}
				
				Rep(j, t, 1)	{	//转移
					int	x= 1ll*(Sum[j] - 1ll*F[j][A[i]]*Mul[j])%P*r%P;
					
					F[j+1][A[i]]= (F[j+1][A[i]] + 1ll*x*Rev[j+1])%P;
					Sum[j+1]= (Sum[j+1] + x) % P;
					
					int	y= 1ll*F[j][A[i]]*Mul[j]%P*r%P;
					F[j][A[i]]= (F[j][A[i]] + 1ll*y*Rev[j])%P;
					Sum[j]= (Sum[j] + y) % P;
				}
			}
			
			return	(Sum[L] + P ) % P;
		}
};