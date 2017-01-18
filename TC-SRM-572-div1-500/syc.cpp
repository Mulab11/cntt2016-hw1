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

int hit[55];
int Lef[55][15], Rig[55][15];
int K, L, n, R, dig[15];
map<VI, string> mps;
map<VI, int>    cnt;
int anscnt;
string ans;
struct EllysBulls{
	
	void dfsL(int x){
		if(x > L){
			VI res;
			string xx = "";
			REP(j, 1, L) xx.pb(dig[j] + 48);
			REP(x, 1, n){
				int in = 0;
				REP(j, 1, L) if(dig[j] == Lef[x][j]) ++ in;
				res.pb(in);
			}
			cnt[res]++;
			mps[res] = xx;
			return;
		}
		REP(i, 0, 9){
			dig[x] = i;
			dfsL(x + 1);
			dig[x] = 0;
		}
	}
	
	void dfsR(int x){
		if(anscnt > 1) return;
		if(x > R){
			VI res;
			string xx = "";
			REP(j, 1, R) xx.pb(dig[j] + 48);
			REP(x, 1, n){
				int in = 0;
				REP(j, 1, R) if(dig[j] == Rig[x][j]) ++ in;
				res.pb(hit[x] - in);
			}
			if(cnt.count(res)){
				anscnt += cnt[res];
				ans = mps[res] + xx;
			}
			return;			
		}
		REP(i, 0, 9){
			dig[x] = i;
			dfsR(x + 1);
			if(anscnt > 1) return;
			dig[x] = 0;
		}
	}
	
	string getNumber(vector<string> guesses, VI bulls){
		n = guesses.size();
		K = guesses[0].size();
		L = K >> 1;
		R = K - L;
		REP(i, 1, n) hit[i] = bulls[i - 1];
		REP(i, 1, n){
			REP(j, 1, L) Lef[i][j] = guesses[i - 1][j - 1] - 48;
			REP(j, L + 1, K) Rig[i][j - L] = guesses[i - 1][j - 1] - 48;
		}
		dfsL(1);
		dfsR(1);
		
		if(anscnt == 0) return "Liar";
		if(anscnt >  1) return "Ambiguity";
		return ans;
		
	}
}stu;