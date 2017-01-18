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
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	LL Inf=1e10;
const	int P=1e9+7;
const	int N=100005;

inline LL IN(){
	LL x = 0;
	int ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}
template<typename T> inline int chkmin(T &a, const T &b){if(b < a) return a = b, 1; return 0;}
template<typename T> inline int chkmax(T &a, const T &b){if(b > a) return a = b, 1; return 0;}

void renew(int &x, const int &y){
	x += y;
	if(x >= P) x -= P;
	if(x <  0) x += P;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (LL)x * x %p) if(y & 1) a=(LL)a * x%p;
	return a;
}

int n, m;
string str;
int A[N];

namespace work1{
	
	int ans = 1 << 30;
	int X[N], V[N];
	
	void dfs(int x, int y){
		if(x > n){
			PER(i, n, 1) V[i] = V[i + 1] ^ X[i];
			REP(i, 1, n) V[i] ^= A[i];
			int res = 0;
			REP(i, 1, m){
				int cnt[2];
				cnt[0] = cnt[1] = 0;
				for(int j = i; j <= n; j += m) cnt[V[j]] ++;
				res += min(cnt[0], cnt[1]);
			}
			chkmin(ans, y + res);
			return;
		}
		X[x] = 1;
		dfs(x + m, y + 1);
		X[x] = 0;
		dfs(x + m, y);
	}
	
	int Main(){
		dfs(m, 0);
		return ans;
	}
};

namespace work2{
	
	int ans = 1 << 30;
	int X[N], V[N];
	int F[305][2], S;
	
	int work(){
		int res = 0, v = 1;
		REP(i, 1, m) V[i] = X[i];
		REP(i, 1, S) F[i][0] = F[i][1] = 0x3f3f3f3f;
		REP(i, S * m + 1, n){
			res += (V[v] ^ A[i]);
			v ++;
		}
		F[0][0] = F[0][1] = 0;
		REP(i, 1, S){
			int l = (i - 1) * m + 1, r = i * m;
			REP(j, 0, 1) REP(k, 0, 1){
				int sum = F[i - 1][j ^ k];
				int v = 1;
				REP(x, l, r){
					sum += V[v] ^ (A[x] ^ j ^ k);
					v ++;	
				}
				F[i][j] = min(F[i][j], sum + k);
			}
		}
		res += F[S][0];
		return res;
	}
	
	void dfs(int x){
		if(x > m){
			chkmin(ans, work());
			return;
		}
		X[x] = 0;
		dfs(x + 1);
		X[x] = 1;
		dfs(x + 1);
	}
	
	int Main(){
		S = n / m;
		dfs(0);
		return ans;
	}
}

struct FlippingBitsDiv1{
	int getmin(vector<string> S, int M){
		str = accumulate(S.begin(), S.end(), string(""));
		m = M;
		n = str.length();
		REP(i, 1, n) A[i] = str[i - 1] - 48;
		if(n / m <= m) return work1 :: Main();
		else return work2 :: Main();
		return -1;
	}
}s;