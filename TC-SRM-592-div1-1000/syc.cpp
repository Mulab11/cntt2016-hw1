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
typedef double	db;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	LL Inf=1e10;
const	int P=1e9+7;
const	int N=30;
const	db pi = acos(-1);

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

int V[N], gt[N];
VI ans;
struct comp{
	db re, im;
	comp(){re = im = 0;}
	comp(db a, db b){
		re = a;
		im = b;
	}
	comp operator +(const comp &a)const{
		return comp(re + a.re, im + a.im);
	}
	comp operator -(const comp &a)const{
		return comp(re - a.re, im - a.im);
	}
	comp operator *(const comp &a)const{
		return comp(re * a.re - im * a.im, re * a.im + im * a.re);
	}
	void print(){
		printf("%.10lf %.10lf\n", re, im);
	}
}v1[N], v2[N], A[N], fA[N], w[2][N * N], fB[N], C[N], fC[N];

void sqrt(comp u, comp &x1, comp &x2){
	x1.re = x1.im = 0;
	x2.re = x2.im = 0;
	if(fabs(u.im) < 1e-7){
		if(u.re < 0){
			x1.im = sqrt(-u.re);
			x2.im = -x1.im;
		}else{
			x1.re = sqrt(u.re);
			x2.re = -x1.re;
		}
//		(x1 * x1).print();
//		u.print();
	}else{
		x1.re = sqrt((u.re + sqrt(u.re * u.re + u.im * u.im)) / 2);
		x1.im = u.im / (2 * x1.re);
		x2.re = -x1.re;
		x2.im = -x1.im;
		
//		(x1 * x1).print();
//		u.print();
	}
}

int n, lim;
//5 0 1 2 3 4
//6 0 1 2 3 4 5 6

struct SplittingFoxes2{
	
	void dfs(int x){
		if(x > lim){
			VI res;
			FOR(i, 0, n){
				comp u;
				FOR(j, 0, n) u = u + fB[j] * w[1][i * j];
				u.re /= n;
				int val = int(u.re + 0.49);
				if(val < 0) return;
				res.pb(val);
			}
			FOR(i, 0, n) gt[i] = 0;
			FOR(i, 0, n){
				int u = i;
				FOR(j, 0, n){
					gt[u] += res[i] * res[j];
					u ++;
					if(u == n) u = 0;
				}
			}
			FOR(i, 0, n) if(gt[i] != V[i]) return;
			if(!ans.size() || res < ans) ans = res;
			return;
		}
		fB[x] = fB[n - x] = v1[x];
		dfs(x + 1);
		fB[x] = fB[n - x] = v2[x];
		dfs(x + 1);
	}
	
	VI Main(){
		dfs(0);
		if(!ans.size()) ans.pb(-1);
		return ans;
	}
	
	VI getPattern(VI amount){
		n = amount.size();
		lim = n >> 1;
		FOR(i, 0, n) A[i].re = V[i] = amount[i];
		FOR(i, 0, n * n){
			w[0][i].re = cos(2 * pi * i / n);
			w[0][i].im = sin(2 * pi * i / n);
			w[1][i].re = w[0][i].re;
			w[1][i].im = -w[0][i].im;
		}
		FOR(i, 0, n) FOR(j, 0, n) fA[i] = fA[i] + A[j] * w[0][i * j];
		FOR(i, 0, n) sqrt(fA[i], v1[i], v2[i]);
		return Main();
	}
}s;