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

int n;
LL num[N], tar, bas[65];
struct XorCards{
	LL work(){
		memset(bas, 0, sizeof bas);
		int free = 0;
		FOR(i, 0, n){
			LL x = num[i];
			PER(j, 62, 0) if((x >> j) & 1){
				if(!bas[j]){
					bas[j] = x;
					break;
				}else{
					x ^= bas[j];
				}
			}
			if(!x) free ++;
		}
		PER(j, 62, 0) if((tar >> j) & 1){
			if(!bas[j]) return 0;
			tar ^= bas[j];
		}
		return 1LL << free;
	}
	LL numberOfWays(vector<LL> A, LL Lim){
		n = A.size();
		Lim ++;
		LL ans = 0;
		PER(bit, 62, 0)if((Lim >> bit) & 1){
			FOR(i, 0, n){
				num[i] = 0;
				PER(j, 62, bit){
					num[i] <<= 1;
					if((A[i] >> j) & 1) num[i] ++;
				}
			}
			tar = 0;
			PER(j, 62, bit + 1){
				tar <<= 1;
				if((Lim >> j) & 1) tar ++;
			}
			tar <<= 1;
			ans += work();
		}
		return ans;
	}
}s;