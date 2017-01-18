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

string digits, lowerBound;
int len;
string f[55][55][5];
struct LeftRightDigitsGame2{
	int cmpdigit(int x, int y){
		if(x < y) return 0;
		if(x == y) return 1;
		if(x > y) return 2;
	}
	int cmppre(int a, int x, int y){
		int u = cmpdigit(x, y);
		if(a != 1) return a;
		return u;
	}
	int cmpsuf(int a, int x, int y){
		int u = cmpdigit(x, y);
		if(u != 1) return u;
		return a;
	}
	string minNumber(string digits, string lowerBound){
		:: digits = digits;
		:: lowerBound = lowerBound;
		len = digits.size();
		FOR(i, 0, len) FOR(j, 0, len) REP(k, 0, 2) f[i][j][k] = "a";
		REP(x, 1, len){
			if(x == 1){
				FOR(i, 0, len){
					string us;
					us.pb(digits[0]);
					f[i][i][cmpdigit(digits[0], lowerBound[i])] = us;
				}
			}
			if(x == len) break;
			FOR(i, 0, len){
				int j = i + x - 1;
				if(j >= len) break;
				int u = digits[x];
				string us;
				us.pb(digits[x]);
				REP(a, 0, 2){
					if(f[i][j][a] == "a") continue;
					if(j + 1 < len) chkmin(f[i][j + 1][cmppre(a, u, lowerBound[j + 1])], f[i][j][a] + us);
					if(i - 1 > -1)  chkmin(f[i - 1][j][cmpsuf(a, u, lowerBound[i - 1])], us + f[i][j][a]);
				}
			}
		}
		string ans = min(f[0][len - 1][1], f[0][len - 1][2]);
		if(ans == "a") return "";
		return ans;
	}
}stu;