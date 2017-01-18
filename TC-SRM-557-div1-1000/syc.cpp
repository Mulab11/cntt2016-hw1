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
const	int inf=2e9;
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

ll b[N], c[N];
class XorAndSum{
public:
	ll maxSum(vector<ll> A){
		Rep(i, 0, A.size()){
			ll u = A[i];
			for(int j = 59; j >= 0; --j) if((u >> j) & 1){
				if(b[j] == 0){
					for(int k = j - 1; k >= 0; --k) if((u >> k) & 1) u ^= b[k];
					b[j] = u;
					for(int k = j + 1; k < 60; ++k) if((b[k] >> j) & 1) b[k] ^= b[j];
					break;
				}else
					u ^= b[j];
			}
		}
		ll mx = 0, res, fir = 1;
		Rep(i, 0, 60) mx ^= b[i];
		res = mx * A.size();
		Forn(i, 59, 0) if(b[i]){
			if(fir) fir = 0; else res += (mx ^ b[i]) - mx;
		}
		return res;
	}
} cla;