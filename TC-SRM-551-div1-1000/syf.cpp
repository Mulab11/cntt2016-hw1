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

#define n	45
#define P	1000000007

int		N, M, MaxS, A[n], F[n], G[n];

namespace	Cal1{
	int		C[n][n], H[n][n];
	
	int		Pow(int a,int b){
		int ret=1;
		for (;b;b>>=1,a=1ll*a*a%P)
			if  (b&1)	ret=1ll*ret*a%P;
		return	ret;
	}
	
	void	Link(int u, int v){	//构建矩阵
		H[u][u]++;
		H[v][v]++;
		H[u][v]--;
		H[v][u]--;
	}
	
	int		Det(){	//计算矩阵行列式，用高斯消元
		int	D= N-1, ret= 1;
		
		For(i, 1, D)	{
			int	j= i;
			for (; j <= D && ! H[j][i]; j++);
			if	(j > D)	return	0;
			
			if	(i ^ j)	{
				ret*= -1;
				For(k, i, D)	swap(H[i][k], H[j][k]);
			}
			
			int	rev= Pow(H[i][i], P-2);
			For(j, i+1, D)	if	(H[j][i]){
				int t= 1ll*H[j][i]*rev%P;
				For(k, i, D)	H[j][k]= (H[j][k] - 1ll*H[i][k]*t)%P;
			}
		}
		
		For(i, 1, D)	ret= 1ll*ret*H[i][i]%P;
		return	(ret + P) % P;
	}
	
	void	Main(){
		For(i, 0, N)	{
			C[i][0]= 1;
			For(j, 1, i)	C[i][j]= (C[i-1][j-1] + C[i-1][j]) % P;
		}
		
		For(great, 0, M)	{	//计算方案数
			For(i, 1, N)	For(j, 1, N)	H[i][j]= 0;
			int bad= N-M;
			
			For(i, 1, great)For(j, i+1, great)	Link(i, j);
			For(i, 1, bad)	For(j, i+1, bad)	Link(M+i, M+j);
			For(i, 1, M)	For(j, 1, bad)	Link(i, M+j);
			
			F[great]= Det();
		}
		
		For(i, 1, M)	For(j, 0, i-1)	//容斥
			F[i]= (F[i] - 1ll*F[j]*C[i][j])%P;
	}
};

namespace	Cal2{
	vector<int>	L[n], R[n];
	
	void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
	}
	
	void	DFS(int l, int r, int num, int sum, int f){	//meet-in-middle 预处理
		if	(l > r)	{
			if	(! f)	L[num].push_back(sum);
				else	R[num].push_back(sum);
			return;
		}
		
		DFS(l+1, r, num, sum, f);
		DFS(l+1, r, num+1, sum+A[l], f);
	}
	
	void	Main(){
		int	Mid= M >> 1;
		DFS(1, Mid, 0, 0, 0);
		DFS(Mid+1, M, 0, 0, 1);
		
		For(i, 0, N)	{
			sort(L[i].begin(), L[i].end());
			sort(R[i].begin(), R[i].end());
		}
		
		For(i, 0, N)	if	(L[i].size())	//用two-point计数
			For(j, 0, N)	if	(R[j].size()){
				for (int l= 0, r= R[j].size()-1; l < L[i].size(); l++)	{
					for (; r >= 0 && L[i][l] + R[j][r] > MaxS; r--);
					if	(r < 0)	break;
					
					Plu(G[i+j], r+1);
				}
			}
	}
};

class	SweetFruits{
	public:
		int		countTrees(vector <int> sweetness, int maxSweetness){
			N= sweetness.size();
			MaxS= maxSweetness;
			For(i, 1, N)	if	(sweetness[i-1] != -1)	A[++ M]= sweetness[i-1];	//预处理
			
			Cal1::Main();
			Cal2::Main();
			
			int	Ans= 0;
			For(i, 0, M)	Ans= (Ans + 1ll*F[i]*G[i])%P;	//计算答案
			
			return	(Ans + P) % P;
		}
};