#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define REP(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define FOR(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define PER(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long ll;
typedef PR<int,int> PII;
const	int inf=2e9;
const	ll Inf=1e10;
const	int P=1e9+7;
const	int N=45;

inline int IN(){
	int x = 0, ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (ll)x * x %p) if(y & 1) a=(ll)a * x%p;
	return a;
}

vector<int> stl[21], str[21];
int vals[N], n, mv, G[N][N], F[N], H[N], C[N][N], gn, s0;
struct SweetFruits{
	void adde(int x, int y){
		++G[x][x];
		--G[x][y];
	}
	void ade(int x, int y){
		adde(x, y);
		adde(y, x);
	}
	void GenGraph(int x){
		memset(G, 0, sizeof G);
		REP(i, 1, x) REP(j, x + 1, x + s0) ade(i, j);
		REP(i, x + 1, gn) REP(j, i + 1, gn) ade(i, j);
	}
	int det(){
		int f = 1, ans = 1, n = gn - 1;
		REP(i, 1, n){
			REP(j, i, n){
				if(G[j][i]){
					if(j != i){
						f = -f;
						REP(k, 1 ,n) swap(G[i][k], G[j][k]);
					}
					break;
				}
			}
			if(!G[i][i]) return 0;
			int inv = Pow(G[i][i], P - 2, P);
			REP(j, 1, n){
				if(j == i) continue;
				int _ = (ll)G[j][i] * inv % P;
				REP(k, 1, n) G[j][k] = (G[j][k] + P - (ll)_ * G[i][k] % P) % P;
			}
		}
		
		REP(i, 1, n) ans = (ll)ans * G[i][i] % P;
		if(f == -1) ans = P - ans;
		return ans % P;
	}
	void dfsl(int x, int r, int c, int v, int f){
		if(x > r){
			stl[c].pb(v * f);
			return;
		}
		dfsl(x + 1, r, c, v + vals[x], f);
		dfsl(x + 1, r, c + 1, v, f);
	}
	void dfsr(int x, int r, int c, int v, int f){
		if(x > r){
			str[c].pb(v * f);
			return;
		}
		dfsr(x + 1, r, c, v + vals[x], f);
		dfsr(x + 1, r, c + 1, v, f);
	}
	int countTrees(vector<int> swt, int mxswt){
		n = swt.size();
		gn = n;
		mv = mxswt;
		REP(i, 1, n) vals[i] = swt[i - 1];
		sort(vals + 1, vals + n + 1);
		reverse(vals + 1, vals + n + 1);
		while(n && vals[n] == -1) n--, s0++;
		if(n >= 2 && n == gn){
			int ans = 0;
			REP(i, 1, n) ans += vals[i];
			if(ans <= mxswt) return Pow(n, n - 2, P);
			return 0;
		}
		if(n <= 1){
			if(gn == 1) return 1;
			return Pow(gn, gn - 2, P);
		}
		REP(i, 0, n){
			C[i][0] = 1;
			REP(j, 1, i) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
		PER(i, n, 0){
			GenGraph(i);
			F[i] = det();
			REP(j, i, n){
				int coef;
				if((j - i) & 1) coef = P - 1;else coef = 1;
				H[i] = (H[i] + (ll)coef * C[n - i][j - i] % P * F[j]) % P;
			}
		}
		
		int l1 = n / 2, l2 = n - l1;
		dfsl(1, l1, 0, 0, 1);
		dfsr(l1 + 1, n, 0, 0, -1);
		vector<int> :: iterator it1, it2;
		int ans = 0;
		REP(c, 0, l1) sort(stl[c].begin(), stl[c].end());
		REP(c, 0, l2) sort(str[c].begin(), str[c].end());
		REP(i, 0, l1)
		REP(j, 0, l2){
			int res = 0, sz = C[l2][j];
			it2 = str[j].begin();
			for(it1 = stl[i].begin(); it1 != stl[i].end(); it1 ++){
				while(it2 != str[j].end() && *it1 - *it2 > mv){
					sz--;
					it2 ++;
				}
				if(!sz) break;
				res = (res + sz) % P;
			}
			ans = (ans + (ll)res * H[i + j]) % P;
		}
		return ans;
	}
} stu;