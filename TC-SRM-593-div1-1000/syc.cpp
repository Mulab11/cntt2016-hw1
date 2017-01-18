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
const	int N=2000005;

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

bool stt;
int n;
int sum[N];
char s[N];
int po[N];
set<PII> st;
bool en;
struct WolfDelaymasterHard{
	int ao, aw;
	int calc(int x, int l, int r){
		if(l > r) return 0;
		int lsum = (x - 2 * l >= 0) ? sum[x - 2 * l] : 0;
		int rsum = (x - 2 * r >= 0) ? sum[x - 2 * r] : 0;
		return (lsum + P - rsum) % P;
	}
	int work(int x){
		if(s[x] == 'w') return 0;
		int val = 0;
		int lenmax = min(x - aw + 1, (x - po[aw] + 2) >> 1);
		if(s[x] != 'o'){
			int u = (x - ao + 2) >> 1;
			if(u > lenmax) u = lenmax;
			val = calc(x, 1, u);
		}
		for(auto ww : st){
			int w = ww.se;
			int l = x - w + 1, r = (x - po[w] + 2) >> 1;
			if(l >= lenmax) continue;
			if(r > lenmax) r = lenmax;
			renew(val, calc(x, l, r));
		}
		return val;
	}
	int Main(){
		aw = ao = 0;
		REP(i, 1, n){
			po[i] = ao;
			if(s[i] == 'w') aw = i;
			if(s[i] == 'o') ao = i;
		}
		sum[0] = 1;
		aw = 0;
		ao = 0;
		REP(i, 1, n){
			if(s[i] == 'o') st.insert(mk(2 * i - ao, i));
			while(st.size() && (st.begin())->fi < i) st.erase(st.begin());
			int val = work(i);
			if(i == n) return val;
			if(s[i] == 'w') aw = i;
			if(s[i] == 'o') ao = i;
			if(i >= 2){
				sum[i] = sum[i - 2] + val;
				if(sum[i] >= P) sum[i] -= P;
			}
		}
		return -1;
	}
	int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		::n = n;
		REP(i, 1, n) s[i] = '?';
		LL x = w0;
		REP(i, 1, wlen){
			s[x + 1] = 'w';
			x = (x * wmul + wadd) % n;
		}
		x = o0;
		REP(i, 1, olen){
			s[x + 1] = 'o';
			x = (x * omul + oadd) % n;
		}
		return Main();
	}
}stu;