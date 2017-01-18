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

struct po{
	int x, y;
	po(){}
	po(int xx, int yy) : x(xx), y(yy) {}
	po operator -(const po &a)const{
		return (po){x - a.x, y - a.y};
	}
}a[N];
int n;
db rd[N], rad[N];

const db pi = acos(-1);
vector<pair<double, double> > val;
struct CircusTents{
	void add(db l, db r){
		if(l < -pi) val.pb(mk(l + 2 * pi, pi)), l = -pi;
		if(r > pi)  val.pb(mk(-pi, r - 2 * pi)), r = pi;
		val.pb(mk(l, r));
	}
	
	int check(db v){
		REP(i, 2, n) rad[i] = rd[i] + v;
		rad[1] = rd[1];
		val.clear();
		REP(i, 2, n){
			int dis = a[i].x * a[i].x + a[i].y * a[i].y;
			if(dis > (rad[i] + rad[1]) * (rad[i] + rad[1])) continue;
			if(dis >= rad[i] * rad[i] + rad[1] * rad[1]){
				db alp = atan2(a[i].y, a[i].x);
				//a ^ 2 + b ^ 2 - 2abcosx = c ^ 2
				//cosx = c * c - a * a - b * b 
				db bet = rad[1] * rad[1] + dis - rad[i] * rad[i];
				bet /= 2 * rad[1] * sqrt(dis);
				bet = acos(bet);
				add(alp - bet, alp + bet);
			}else{
				db alp = atan2(a[i].y, a[i].x);
				//a ^ 2 + b ^ 2 - 2abcosx = c ^ 2
				//cosx = c * c - a * a - b * b 
				db bet = acos(rad[1] / sqrt(dis));
				db gam = (rad[i] - sqrt(dis - rad[1] * rad[1])) / rad[1];
				if(bet + gam >= pi) return 0;
				add(alp - bet - gam, alp + bet + gam);
				
			}
		}
		sort(val.begin(), val.end());
		db ma = -pi;
		for(auto v : val){
			if(v.fi > ma) return 1;
			chkmax(ma, v.se);
		}
		return ma < pi;
	}
	
	db findMaximumDistance(vector<int> x, vector<int> y, vector<int> rad){
		n = x.size();
		REP(i, 1, n) a[i] = po(x[i - 1], y[i - 1]);
		REP(i, 2, n) a[i] = a[i] - a[1];
		REP(i, 1, n) rd[i] = rad[i - 1];
		
		db l = 0, r = 1e5, aim = r;
		REP(i, 1, 100){
			db md = (l + r) / 2;
			if(check(md)){
				aim = md;
				l = md;
			}else{
				r = md;
			}
		}
		check(aim);
		return aim;
	}
}stu;