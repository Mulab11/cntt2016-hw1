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
#define Bit	bitset<n>

int		N, K, Ans, val[n], A[n], S[n], ID[n], Deg[n];

Bit		B[n];

bool	Cmp(int a, int b){
		return	val[a] > val[b] || (val[a] == val[b] && Deg[a] < Deg[b]);	//将val相同时，按照度数排序，可以加速。
}

void	DFS(int d, int cnt, int sum, Bit G)	{
		if	(N-d+1 + cnt < K)	return;
		if	((int)G.count() + cnt < K)	return;	//如果剩下可能合法的点加上已经选上的点都构不成可行解，则剪枝。
		if	(sum + S[N] - S[d-1] <= Ans)	return;
		if	(A[d] * (int)G.count() + sum <= Ans)	return;	//如果剩下点的都选上，权值和还是没有答案大，则剪枝。
		
		if	(d == N+1)	{
			Ans= sum;	return;
		}
		if	(cnt >= K)	Ans= max(Ans, sum);	//时时维护最优解
		
		if	(G[d])	DFS(d+1, cnt+1, sum+A[d], G & B[d]);
		DFS(d+1, cnt, sum, G);	//优先搜索“选”的分治，可以加速。
}

class	MagicMolecule{
	public:
		int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
			N= magicPower.size();
			For(i, 1, N)	val[i]= magicPower[i-1], ID[i]= i;
			For(i, 1, N)	For(j, 1, N)	Deg[i]+= magicBond[i-1][j-1] == 'Y';
			
			sort(ID+1, ID+N+1, Cmp);
			For(i, 1, N)	A[i]= val[ID[i]], S[i]= S[i-1] + A[i];
			//把所有点按照点权排序
			
			For(i, 1, N)	{
				int u= ID[i];
				For(j, i+1, N)	{
					int v= ID[j];
					if	(magicBond[u-1][v-1] == 'Y')	B[i][j]= 1;
				}
			}
			//预处理所有点对之间的连边情况。
			
			Ans= -1;
			for (K=1; 3*K < 2*N; K++);
			
			For(i, 1, N)	B[0][i]= 1;
			DFS(1, 0, 0, B[0]);
			//搜索
			
			return	Ans;
		}
};