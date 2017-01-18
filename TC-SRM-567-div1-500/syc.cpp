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

int n, cnt[N][26], gao[N], use[30];
struct StringGame{
	VI getWinningStrings(vector<string> S){
		n = S.size();
		FOR(i, 0, n){
			for(auto w : S[i]) cnt[i + 1][w - 'a']++;
		}
		VI ans;
		REP(i, 1, n){
			REP(j, 1, n) gao[j] = 1;
			gao[i] = 0;
			REP(x, 0, 25) use[x] = 0;
			int valid = 1;
			REP(x, 0, 25){
				int fd = -1;
				REP(v, 0, 25)if(!use[v]){
					int ok = 1;
					REP(j, 1, n) if(gao[j] && cnt[j][v] > cnt[i][v]) ok = 0;
					if(ok){
						fd = v;
						use[v] = 1;
						break;
					}
				}
				if(fd == -1){
					valid = 0;
					break;
				}
				REP(j, 1, n) if(gao[j] && cnt[j][fd] < cnt[i][fd]) gao[j] = 0;
				int brk = 1;
				REP(j, 1, n) brk &= !gao[j];
				if(brk) break;
			}
			REP(j, 1, n) if(gao[j]) valid = 0;
			if(valid) ans.pb(i - 1);
		}
		return ans;
	}
}stu;