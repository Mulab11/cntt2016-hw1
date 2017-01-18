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
#define For(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define Rep(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define Forn(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long ll;
typedef PR<int,int> PII;
const	int inf=66;
const	ll Inf=1e10;
const	int P=1e9+7;
const	int N=100005;

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

ll ans, U, res, gg[N];
int sz, n, val[N], tot;
string gl, co;

void check(int pos){
	memset(val, -1, sizeof val);
	int tap = pos;
	res = 0;
	Rep(i, 0, sz){
		char u = co[i];
		if(u == '<'){
			--tap;
			if(tap <= 0) return;
		}else
		if(u == '>'){
			++tap;
			if(tap > n) return;
		}else{
			val[tap] = u - 48;
		}
		int ok = 1;
		For(i, 1, n) if(val[i] != -1 && val[i] + 48 != gl[i - 1]){
			ok = 0;
			break;
		}
		if(!ok) continue;
		ll cur = 0;
		For(i, 1, n) if(val[i] != -1) cur |= (1LL << (i - 1));
		res = cur;
	}
//	cerr << res << endl;
	gg[++tot] = res;
}

void dfs(int x, int w, ll st){
	if(!st) return;
	if(x > tot){
//		cerr << st << " " << w << " ";
//		cerr << __builtin_popcountll(st) << endl;
		if(st ^ U) res += (ll)w * ((1LL<<__builtin_popcountll(st)) - 1);
		return;
	}
	dfs(x + 1, w, st);
	dfs(x + 1, -w, st & gg[x]);
}

class MapGuessing{
public:
	ll countPatterns(string s0,vector<string> c0){
		gl = s0;
		co = "";
		Rep(i,0,c0.size()) co += c0[i];
		sz = co.size();
		n = gl.size();
		For(st, 1, n) check(st);
		if(!tot) return 0;
		res = 1;
		U = (1LL << (n + 1)) - 1;
		dfs(1, -1, U);
		return res;
	}
}tt;