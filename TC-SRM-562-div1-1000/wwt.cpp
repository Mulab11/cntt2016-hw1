#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105,Mo = int(1e9) + 9;

int Final[MAXN],To[MAXN],Next[MAXN],Fac[MAXN],Rv[MAXN],C[MAXN][MAXN],tot;
int N,K;

int Quick(int a,int b)
{
	int tmp = 1;
	for(;b;b >>= 1)
	{
		if (b & 1) tmp = 1ll * tmp * a % Mo;
		a = a * 1ll * a % Mo;
	}
	return tmp;
}

namespace Chain
{
	bool Ok[MAXN];
	int All[MAXN],Son[MAXN],Top[MAXN],F[MAXN],Forbid;

	void Dfs(int Now,int Pre,int top,int last) //get chain
	{
		Son[Now] = 1;
		Top[Now] = top;
		int c = 0;
		for(int i = Final[Now];i;i = Next[i]) //degree
			if (To[i] != Pre) ++ c;
		if (last == 0) Ok[Now] = 1; else Ok[Now] = 0;
		if (c >= 2 && Pre) last ++; 
		for(int i = Final[Now];i;i = Next[i])
			if (To[i] != Pre)
				Dfs(To[i], Now, top ? top : To[i], last),Son[Now] += Son[To[i]];
	}

	void Dfs_Dp(int Now)
	{
		All[Now] = 1;
		int mul = 1;
		for(int i = Final[Now];i;i = Next[i]) 
			if (To[i] != Forbid && Son[To[i]] < Son[Now])
				Dfs_Dp(To[i]),mul = 1ll * mul * F[To[i]] % Mo * Rv[All[To[i]]] % Mo,All[Now] += All[To[i]];
		F[Now] = 1ll * mul * Fac[All[Now] - 1] % Mo;
	}

	int Work()
	{
		bool f = 0;
		for(int i = 1;i <= N;i ++)
		{
			Dfs(i,0,0,0);
			for(int j = 1;j <= N;j ++)
				if (i != j && Son[j] == K && Son[i] - Son[Top[j]] == K && Ok[j]) //Find a legal chain
				{
					f = 1;
					Forbid = Top[j];
					Dfs_Dp(i),Dfs_Dp(j);
					return 2 * F[i] * 1ll * F[j] % Mo;
					break;
				}
			if (f) break;
		}
		return 0;
	}
}

namespace Red_And_Blue
{
	const int MAXN = 55;

	bool Walk[MAXN][MAXN];
	int G[MAXN][MAXN][MAXN][MAXN],Bak[MAXN][MAXN],F[MAXN],Son[MAXN],Ans;
		//   Red   Blue
	void Dfs(int Now,int Pre)
	{
		int mul = 1;
		Son[Now] = 0;
		for(int i = Final[Now];i;i = Next[i])
			if (To[i] != Pre)
				Dfs(To[i],Now),mul = 1ll * mul * F[To[i]] % Mo * Rv[Son[To[i]]] % Mo,Son[Now] += Son[To[i]];
		F[Now] = 1ll * mul * Fac[Son[Now]] % Mo;
		if (Walk[Now][Pre]) {Son[Now] ++;return;}
		Walk[Now][Pre] = 1;
		for(int i = 0;i <= N - K;i ++) //clear
			for(int j = 0;j <= N - K;j ++)
				G[Now][Pre][i][j] = 0;
		G[Now][Pre][0][0] = 1;
		//Be a White point
		int cr = 0;
		for(int i = Final[Now];i;i = Next[i])
			if (To[i] != Pre)
			{
				int v = To[i];
				cr += Son[v];
				for(int red = 0;red <= min(cr,N - K);red ++) //clear
					for(int blue = 0;blue <= min(cr - red,N - K);blue ++)
						Bak[red][blue] = G[Now][Pre][red][blue],G[Now][Pre][red][blue] = 0;
				//this part needs to run fast 
				for(int red = 0;red <= min(cr,N - K);red ++)
					for(int blue = 0;blue <= min(cr - red,N - K);blue ++) //merge information
						for(int r = 0;r <= min(Son[v],red);r ++)
							for(int b = 0;b <= min(Son[v] - r,blue);b ++)
							{
								int cv = G[v][Now][r][b] % Mo * 1ll * C[red][r] % Mo * C[blue][b] % Mo;
								cv = 1ll * cv * Bak[red - r][blue - b] % Mo;
								(G[Now][Pre][red][blue] += cv) %= Mo;
							}
			}
		//Be a Red point Or Blue point
		Son[Now] ++;
		if (Son[Now] <= N - K)
		{
			G[Now][Pre][Son[Now]][0] = F[Now];
			G[Now][Pre][0][Son[Now]] = F[Now];
		}
	}
	
	int Work()
	{
		Ans = 0;
		memset(Walk,0,sizeof Walk);
		for(int i = 1;i <= N;i ++)
		{
			Dfs(i,0);
			Ans = (Ans + G[i][0][N - K][N - K]) % Mo;
		}
		for(int i = 1;i <= 2 * K - N;i ++) Ans = Ans * 1ll * i % Mo;
		return Ans * 1ll * Quick(2 * K - N,Mo - 2) % Mo;
	}
}

void Link(int u,int v)
{
	To[++ tot] = v,Next[tot] = Final[u],Final[u] = tot;
}

class InducedSubgraphs
{
public:
	int getCount(vector <int> edge1, vector <int> edge2, int k)
	{
		Fac[0] = 1;
		for(int i = 1;i <= 100;i ++) Fac[i] = Fac[i - 1] * 1ll * i % Mo;
		Rv[100] = Quick(Fac[100],Mo - 2);
		for(int i = 99;i + 1;i --) Rv[i] = Rv[i + 1] * 1ll * (i + 1) % Mo;
		for(int i = 1;i <= 100;i ++) C[i][0] = C[0][i] = 1;
		for(int i = 1;i <= 100;i ++)
			for(int j = 1;j <= i;j ++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mo;
		C[0][0] = 1;
		N = edge1.size() + 1,K = k;
		tot = 0;
		memset(Final,0,sizeof Final);
		for(int i = 0;i < N - 1;i ++)
		{
			int u = edge1[i],v = edge2[i];
			u ++, v ++;
			Link(u,v),Link(v,u);
		}
		if (K == 1) return Fac[N]; //we have to specify this situation
		if (K * 2 <= N) return Chain::Work(); else
			return Red_And_Blue::Work();
	}
};
