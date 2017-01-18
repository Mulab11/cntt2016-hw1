#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>
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

int n, m;
int rx[355];
struct po{
	int x, y;
	po operator +(const po &a)const{
		return (po){x + a.x, y + a.y};
	}
	po operator -(const po &a)const{
		return (po){x - a.x, y - a.y};
	}
	int operator *(const po &a)const{
		return x * a.y - y * a.x;
	}
	po(){}
	po(int xx , int yy) : x(xx), y(yy) {}
}b[355];
LL sm[355], bg[355];

LL C(LL x){
	return x * (x - 1) / 2;
}

struct Ear{
	LL getCount(vector<string> redX, vector<string> blueX, vector<string> blueY){
		string V1 = "", V2 = "", V3 = "";
		for(auto x : redX)  V1 += x;
		for(auto x : blueX) V2 += x;
		for(auto x : blueY) V3 += x;
		stringstream iss1(V1), iss2(V2), iss3(V3);
		int x = 0, y = 0;
		while(iss1 >> x) rx[++n] = x;
		while(iss2 >> x){
			iss3 >> y;
			b[++m] = (po){x, y};
		}
		sort(rx + 1, rx + n + 1);
		REP(i, 1, m){
			REP(j, 1, n) if(b[i].x < rx[j]) ++ bg[i];
			REP(j, 1, n) if(b[i].x > rx[j]) ++ sm[i];
		}
		LL ans = 0;
		REP(i, 1, m) REP(j, 1, m) if(b[j].y < b[i].y){
			int l = -1;
			int r = -1;
			REP(k, 1, n){
				po d = po(rx[k], 0);
				if((b[i] - d) * (b[j] - d) < 0) l = k;
				if((b[i] - d) * (b[j] - d) > 0 && r == -1) r = k;
			}
			if(l == -1 || r == -1) continue;
			if(b[j].x == b[i].x){
				ans += C(l) * C(n - r + 1);
			}else
			if(b[j].x > b[i].x){
				LL lf = C(sm[i]) + sm[i] * (sm[j] - sm[i]);
				LL rg = C(n - r + 1) + (n - r + 1) * (bg[j] - (n - r + 1));
				ans += lf * rg;
			}else
			if(b[j].x < b[i].x){
				LL lf = C(l) + l * (sm[j] - l);
				LL rg = C(bg[i]) + bg[i] * (bg[j] - bg[i]);
				ans += lf * rg;
			}
		}
		return ans;
	}
} stu;