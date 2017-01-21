#include <bits/stdc++.h>

#define MOD 1000000009

using namespace std ; 

const int MAXN = 105  ;  

int N,K ; 

int fn[MAXN],to[MAXN],Next[MAXN],Fac[MAXN],Inv[MAXN],C[MAXN][MAXN],tot ; 

int qpow(int a,int b) {
		int tmp = 1 ; 
		for( ; b ; b >>= 1, a = 1LL * a * a % MOD )  if (b & 1) tmp = 1LL * tmp * a % MOD ; 
		return tmp ; 
}


namespace RAB {
		const int MAXN = 55 ; 

		bool Walk[MAXN][MAXN] ; 
		int G[MAXN][MAXN][MAXN][MAXN],Bak[MAXN][MAXN],F[MAXN],Son[MAXN],Ans ; 
		void Dfs(int Now,int Pre) {
				int mul = 1 ; 
				Son[Now] = 0 ; 
				for(int i = fn[Now] ; i ; i = Next[i])
						if (to[i] != Pre)
								Dfs(to[i],Now),mul = 1LL * mul * F[to[i]] % MOD * Inv[Son[to[i]]] % MOD,Son[Now] += Son[to[i]] ; 
				F[Now] = 1LL * mul * Fac[Son[Now]] % MOD ; 
				if (Walk[Now][Pre]) {Son[Now] ++ ; return ; }
				Walk[Now][Pre] = 1 ; 
				for(int i = 0 ; i <= N - K ; i ++) 
						for(int j = 0 ; j <= N - K ; j ++)
								G[Now][Pre][i][j] = 0 ; 
				G[Now][Pre][0][0] = 1 ; 
				int cr = 0 ; 
				for(int i = fn[Now] ; i ; i = Next[i])
						if (to[i] != Pre) {
								int v = to[i] ; 
								cr += Son[v] ; 
								for(int red = 0 ; red <= min(cr,N - K) ; red ++) 
										for(int blue = 0 ; blue <= min(cr - red,N - K) ; blue ++)
												Bak[red][blue] = G[Now][Pre][red][blue],G[Now][Pre][red][blue] = 0 ; 
								
								for(int red = 0 ; red <= min(cr,N - K) ; red ++)
										for(int blue = 0 ; blue <= min(cr - red,N - K) ; blue ++) 
												for(int r = 0 ; r <= min(Son[v],red) ; r ++)
														for(int b = 0 ; b <= min(Son[v] - r,blue) ; b ++) {
																int cv = G[v][Now][r][b] % MOD * 1LL * C[red][r] % MOD * C[blue][b] % MOD ; 
																cv = 1LL * cv * Bak[red - r][blue - b] % MOD ; 
																(G[Now][Pre][red][blue] += cv) %= MOD ; 
														}
						}
				Son[Now] ++ ; 
				if (Son[Now] <= N - K) {
						G[Now][Pre][Son[Now]][0] = F[Now] ; 
						G[Now][Pre][0][Son[Now]] = F[Now] ; 
				}
		}
		int Work() {
				Ans = 0 ; 
				memset(Walk,0,sizeof Walk) ; 
				for(int i = 1 ; i <= N ; i ++) {
						Dfs(i,0) ; 
						Ans = (Ans + G[i][0][N - K][N - K]) % MOD ; 
				}
				for(int i = 1 ; i <= 2 * K - N ; i ++) Ans = Ans * 1LL * i % MOD ; 
				return Ans * 1LL * qpow(2 * K - N, MOD - 2) % MOD ; 
		}
}



namespace Chain {
		bool Ok[MAXN] ; 
		int All[MAXN],Son[MAXN],top[MAXN],F[MAXN],Forbid ; 

		void Dfs(int Now,int Pre,int t,int last)  {
				Son[Now] = 1 ; 
				top[Now] = t ; 
				int c = 0 ; 
				for(int i = fn[Now] ; i ; i = Next[i]) 
						if (to[i] != Pre) ++ c ; 
				if (last == 0) Ok[Now] = 1 ;  else Ok[Now] = 0 ; 
				if (c >= 2 && Pre) last ++ ; 
				for(int i = fn[Now] ; i ; i = Next[i])
						if (to[i] != Pre)
								Dfs(to[i], Now, t ? t : to[i], last),Son[Now] += Son[to[i]] ; 
		}

		void Dfs_Dp(int Now) {
				All[Now] = 1 ; 
				int mul = 1 ; 
				for(int i = fn[Now] ; i ; i = Next[i])
						if (to[i] != Forbid && Son[to[i]] < Son[Now])
								Dfs_Dp(to[i]),mul = 1LL * mul * F[to[i]] % MOD * Inv[All[to[i]]] % MOD,All[Now] += All[to[i]] ; 
				F[Now] = 1LL * mul * Fac[All[Now] - 1] % MOD ; 
		}

		int Work() {
				bool f = 0 ; 
				for(int i = 1 ; i <= N ; i ++) {
						Dfs(i,0,0,0) ; 
						for(int j = 1 ; j <= N ; j ++)
								if (i != j && Son[j] == K && Son[i] - Son[top[j]] == K && Ok[j])  {
										f = 1 ; 
										Forbid = top[j] ; 
										Dfs_Dp(i),Dfs_Dp(j) ; 
										return 2 * F[i] * 1LL * F[j] % MOD ; 
										break ; 
								}
						if (f) break ; 
				}
				return 0 ; 
		}
}
void addedge(int u,int v) {
		to[++ tot] = v,Next[tot] = fn[u],fn[u] = tot ; 
}

class InducedSubgraphs {
		public:
				int getCount(vector <int> edge1, vector <int> edge2, int k) {
						Fac[0] = 1 ; 
						for(int i = 1 ; i <= 100 ; i ++) Fac[i] = Fac[i - 1] * 1LL * i % MOD ; 
						Inv[100] = qpow(Fac[100],MOD - 2) ; 
						for(int i = 99 ; i + 1 ; i --) Inv[i] = Inv[i + 1] * 1LL * (i + 1) % MOD ; 
						for(int i = 1 ; i <= 100 ; i ++) C[i][0] = C[0][i] = 1 ; 
						for(int i = 1 ; i <= 100 ; i ++)
								for(int j = 1 ; j <= i ; j ++)
										C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD ; 
						C[0][0] = 1 ; 
						N = edge1.size() + 1,K = k ; 
						tot = 0 ; 
						memset(fn,0,sizeof fn) ; 
						for(int i = 0 ; i < N - 1 ; i ++) {
								int u = edge1[i],v = edge2[i] ; 
								u ++, v ++ ; 
								addedge(u,v),addedge(v,u) ; 
						}
						if (K == 1) return Fac[N] ;  
						if ((K << 1) <= N) return Chain::Work() ;  
						else return RAB::Work() ; 
				}
} ; 
