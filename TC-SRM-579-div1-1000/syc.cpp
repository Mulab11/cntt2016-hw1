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
const	int N=55;

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

db SP[N][N][N][5];
db SG[N][N][N][5];
VI A[5];
int n;
struct RockPaperScissors{
	db bestScore(VI rock_prb, VI paper_prb, VI scissor_prb){
		n = rock_prb.size();
		A[0] = rock_prb;
		A[1] = paper_prb;
		A[2] = scissor_prb;
		REP(i, 0, 2){
			SP[0][0][0][i] = 1;
			SG[0][0][0][i] = accumulate(A[i].begin(), A[i].end(), 0.) / 300.;
		}
		REP(i, 1, n){
			db p0 = A[0][i - 1] / 300.;
			db p1 = A[1][i - 1] / 300.;
			db p2 = A[2][i - 1] / 300.;
			db P[3] = {p0, p1, p2};
			REP(w, 0, 2)
			PER(a, i, 0)
			PER(b, i - a, 0)
			PER(c, i - a - b, 0){
				db s = n - a - b - c + 1;
				s /= (a + b + c);
				if(!s) continue;
				if(a == 1 && b == 1 && c == 0)
					a = 1;
				if(a){
					SP[a][b][c][w] += SP[a - 1][b][c][w] * p0 / s;
					SG[a][b][c][w] += SG[a - 1][b][c][w] * p0 / s + SP[a - 1][b][c][w] * (-P[w]) * p0 / s;
				}
				if(b){
					SP[a][b][c][w] += SP[a][b - 1][c][w] * p1 / s;
					SG[a][b][c][w] += SG[a][b - 1][c][w] * p1 / s + SP[a][b - 1][c][w] * (-P[w]) * p1 / s;
				}
				if(c){
					SP[a][b][c][w] += SP[a][b][c - 1][w] * p2 / s;
					SG[a][b][c][w] += SG[a][b][c - 1][w] * p2 / s + SP[a][b][c - 1][w] * (-P[w]) * p2 / s;
				}
			}
		}
		
		db ans = 0;
		REP(a, 0, n)
		REP(b, 0, n - a)
		REP(c, 0, n - a - b){
			if(a + b + c == n) continue;
			db u = SG[a][b][c][0] / (n - a - b - c);
			db v = SG[a][b][c][1] / (n - a - b - c);
			db w = SG[a][b][c][2] / (n - a - b - c);
			ans += max(max(3 * u + v, 3 * v + w), 3 * w + u);
		}
		return ans;
	}
}s;