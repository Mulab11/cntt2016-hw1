// BEGIN CUT HERE

// END CUT HERE
#line 5 "CosmicBlocks.cpp"
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
    if (b < *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
    if (b > *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
void read(T *a) {
    char c;
    while (isspace(c = getchar())) {}
    bool flag = 0;
    if (c == '-') flag = 1, *a = 0;
    else
        *a = c - 48;
    while (isdigit(c = getchar())) *a = *a * 10 + c - 48;
    if (flag) *a = -*a;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
    T res = 1;
    for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
    return res;
}

/*======================= TEMPLATE =======================*/

const int N = 800;
const int M = 20;
const int INF = mo;


int n, Min, Max;
vector<int> idx;
int List[M][M], ls[M];
int cnt[N], dp[1 << 6], Ma[M];
bool used[M], G[M][M];
int base, S, T, f[M][M];

int build() {
	base = 2 * n;
	S = base + 1;
	T = S + 1;
	int ind[10], oud[10];
    CL(ind, 0); CL(oud, 0); CL(f, 0);
	int ans = 0;
    REP(u, 0, n - 1) {
        REP(v, 0, n - 1) {
			if(G[u][v]) {
				f[u][v + n] = INF;
				ind[v]++;
				oud[u]++;
			}
			else f[u][v + n] = 0;
		}
	}

    REP(u, 0, n - 1) {
		f[S][u] = idx[u] - oud[u];
		if(f[S][u] < 0) return -1;
		ans += f[S][u];
	}
    REP(i, 0, ls[0] - 1) {
		int x = List[0][i];
		f[x][base] = INF;
	}
	f[base][T] = INF;
    REP(v, 0, n - 1) {
		f[v + n][T] = idx[v] - ind[v];
		if(f[v + n][T] < 0) return -1;
	}
	return ans;
}

int dfs(int u, int p[], int now) {
	if(u == T) return now;
    REP(v, 0, T) 
        if(p[v] == -1 && f[u][v]){
            p[v] = u;
            int tmp = dfs(v, p, min(now,f[u][v]));
            if(tmp > 0) return tmp;
        }
	return 0;
}

int flow() {
	int ans = 0;
	while(1){
		int p[20];
        CL(p, 0xff);
		p[S] = S;
		int tmp = dfs(S, p, INF);
        if (!tmp) break;
		ans += tmp;
		int v = T;
		while(v!=S){
			int u = p[v];
			f[u][v] -= tmp;
			f[v][u] += tmp;
			v = u;
		}
	}
	return ans;
}

bool check(){
	int r = build();
	if(r < 0) return false;
	int f = flow();
	return f >= r;
}

int calcWays2(int mask){
	if(mask == ((1 << n) - 1)){
		return 1;
	}
	if(dp[mask] > -1) return dp[mask];
	dp[mask] = 0;
    REP(i, 0, n - 1) if(((mask >> i)&1) == 0 ){
		if( (mask&Ma[i]) == Ma[i] ){	
			dp[mask] += calcWays2(mask | (1<<i));	
		}
	}
	return dp[mask];
}

int calcWays(){
	memset(dp, -1, sizeof(dp));
	return calcWays2(0);
}

void init(int l, int k, int pre) {
	if(l > 0 && ls[l-1] == 0) return;
	if(k == n) {
		if(ls[l] == 0) return;
		if(check()){
			int w = calcWays();
			if(Min <= w && w <= Max){
				cnt[w]++;
			}
		}
		return;
	}

    REP(i, pre + 1, n - 1) if(!used[i]){
		List[l][ls[l]++] = i;
		used[i] = true;
		if(l > 0){
			int m = ls[l-1];

			for(int j = 0; j < (1<<m); ++j){
				for(int a = 0; a < m; ++a) if((j>>a)&1){
					int x = List[l-1][a];
					Ma[i] |= (1<<x);
					G[i][x] = 1;
				}

				init(l, k+1, i);
				init(l+1, k+1, -1);
				for(int a = 0; a < m; ++a) if((j>>a)&1){
					int x = List[l-1][a];
					Ma[i] ^= (1<<x);
					G[i][x] = 0;
				}
			}
		}
		else init(l, k+1, i), init(l+1, k+1, -1);
		used[i] = 0;
		ls[l]--;
	}
}

class CosmicBlocks {
public:
	int getNumOrders(vector <int> tps, int minWays, int maxWays) {
		idx = tps;
		Min = minWays;
		Max = maxWays;
		n = tps.size();
        CL(cnt, 0); CL(used, 0);
		init(0, 0, -1);
		int ans = 0;
        REP(i, minWays, maxWays) ans += cnt[i];
		return ans;
	}

};