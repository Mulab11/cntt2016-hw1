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

int A[555][555], S[555][555], B[555][555];

struct DrawingPointsDivOne{
	int maxSteps(VI xx, VI yy){
		if(xx.size() == 1) return -1;
		for(int i = 0; i < (int)xx.size(); i ++){
			A[xx[i] + 75][yy[i] + 75] = 1;
			B[xx[i] + 75][yy[i] + 75] = 1;
		}
		REP(k, 1, 150){
			PER(i, 300, 0)
			PER(j, 300, 0){
				A[i][j] |= (i > 0 && A[i - 1][j]) | (j > 0 && A[i][j - 1]) | (i > 0 && j > 0 && A[i - 1][j - 1]);
			}
			
			REP(i, 0, 300) REP(j, 0, 300){
				S[i][j] = A[i][j];
				if(i) S[i][j] += S[i - 1][j];
				if(j) S[i][j] += S[i][j - 1];
				if(i && j) S[i][j] -= S[i - 1][j - 1];
			}
			
			REP(i, k, 300) REP(j, k, 300){
				int sum = S[i][j];
				if(i > k) sum -= S[i - k - 1][j];
				if(j > k) sum -= S[i][j - k - 1];
				if(i > k && j > k) sum += S[i - k - 1][j - k - 1];
				if(sum == (k + 1) * (k + 1) && !B[i - k][j - k])
					return k - 1;
			}
		}
		return -1;
	}
}stu;