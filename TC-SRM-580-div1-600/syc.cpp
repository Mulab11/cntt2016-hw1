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
const	int N=2555;

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

int n;
int res[N], ID[N];
int Lmin[N], Rmax[N], vis[N];
int L[N], R[N], smax, tmin, fa[N];
string S1000, S100, S10, S1, T1000, T100, T10, T1;

int cmp(const int &a, const int &b){
	return R[a] - L[a] > R[b] - L[b];
}

struct ShoutterDiv1{
	int Inter(int u, int v){
		if(R[v] < L[u] || R[u] < L[v]) return 0;
		return 1;
	}
	void worke(int fr){
		int lmin = fr, rmax = fr;
		REP(i, 1, n) if(Inter(fr, i)){
			if(R[i] > R[rmax] || (R[i] == R[rmax] && L[i] < L[rmax])) rmax = i;
			if(L[i] < L[lmin] || (L[i] == L[lmin] && R[i] > R[lmin])) lmin = i;
		}
		Rmax[fr] = rmax;
		Lmin[fr] = lmin;
	}
	void work(int fr){
		int lmin = Lmin[fr];
		int rmax = Rmax[fr];
		REP(i, 1, n) vis[i] = 0;
		if(Inter(smax, fr)) rmax = smax;
		if(Inter(tmin, fr)) lmin = tmin;
		int ans = 0;
		while(1){
			int done = 1;
			if(rmax != smax){
				ans ++;
				done = 0;
				if(R[rmax] >= L[smax]){
					rmax = smax;
				}else{
					rmax = Rmax[rmax];
				}
			}
			if(lmin != tmin){
				ans ++;
				done = 0;
				if(L[lmin] <= R[tmin]){
					lmin = tmin;
				}else{
					lmin = Lmin[lmin];
				}
			}
			if(done) break;
		}
		res[fr] = ans;
	}
	int get(int x){
		return (fa[x] == x) ? (x) : (fa[x] = get(fa[x]));
	}

	int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1){
		for(auto v : s1000) S1000 += v;
		for(auto v : s100) S100 += v;
		for(auto v : s10) S10 += v;
		for(auto v : s1) S1 += v;
		for(auto v : t1000) T1000 += v;
		for(auto v : t100) T100 += v;
		for(auto v : t10) T10 += v;
		for(auto v : t1) T1 += v;
		n = S1000.size();
		REP(i, 1, n){
			L[i] = (S1000[i - 1] - 48) * 1000 + (S100[i - 1] - 48) * 100 + (S10[i - 1] - 48) * 10 + S1[i - 1] - 48;
			R[i] = (T1000[i - 1] - 48) * 1000 + (T100[i - 1] - 48) * 100 + (T10[i - 1] - 48) * 10 + T1[i - 1] - 48;
		}
		return work();
	}
	int work(){
		int ans = 0;
		smax = tmin = 1;
		REP(i, 2, n) if(L[i] > L[smax]) smax = i;
		REP(i, 2, n) if(R[i] < R[tmin]) tmin = i;
		
		REP(i, 1, n) fa[i] = i;
		REP(i, 1, n) REP(j, 1, n) if(Inter(i, j)) fa[get(i)] = get(j);
		int con = 0;
		REP(i, 1, n) if(get(i) == i) ++ con;
		if(con > 1) return -1;
		
		REP(i, 1, n) worke(i);
		REP(i, 1, n) work(i);
		
		REP(i, 1, n) ID[i] = i;
		sort(ID + 1, ID + n + 1, cmp);
		REP(i, 2, n) FOR(j, 1, i) if(L[ID[j]] <= L[ID[i]] && R[ID[i]] <= R[ID[j]]) chkmin(res[ID[i]], res[ID[j]] + 1);
		REP(i, 1, n) ans += res[i];
		return ans;
		
	}
}s;