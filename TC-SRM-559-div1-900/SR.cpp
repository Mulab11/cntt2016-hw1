
#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const double pi = acos(-1);
const int inf = 0x7fffffff;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

const int N = 50 + 5;
struct Pt{ int x, y; };
struct Cir{ Pt p; int r; }a[N];
vector<pair<double, double> > now;
int n;

template<typename tn> tn sqr(const tn &a){ return a * a; }
inline Pt operator - (const Pt &a, const Pt &b){ return (Pt){a.x - b.x, a.y - b.y}; }
inline int dis(const Pt &a){ return sqr(a.x) + sqr(a.y); }

inline double func(double A){
	while (A > pi) A -= 2 * pi;
	while (A < -pi) A += 2 * pi;
	return A;
}
inline double cosin(double a, double b, double c){ return acos((sqr(a) + sqr(b) - sqr(c)) / (2 * a * b)); }
void push(double &l, double &r){ now.PB(MP(l, r)); }
inline bool query(const Cir &A, const Cir &B, double x){
	Pt V = A.p - B.p;
	double d = sqrt(dis(V));
	if (x + A.r + B.r < d) return 0;//如果之间最短距离小于极限则跳出 
	double t = sqrt(dis(V) - sqr(B.r));
	double fx = atan2(V.y, V.x), ang;
	if (x + A.r <= t) ang = cosin(d, B.r, x + A.r);//如果映射在圆的正半面 
	else{//映射在圆的负半面，那么是一段直线距离加上一段圆弧 
		double tmp = acos(B.r / d);
		if (x + A.r + 1e-10 > t + B.r * (pi - tmp)) return 1;
		ang = tmp + (x + A.r - t) / B.r;
	}
	double L = func(fx - ang), R = func(fx + ang);
	if (L < R) now.PB(MP(L, R));
	else now.PB(MP(-pi, R)), now.PB(MP(L, pi));
	return 0;		
}
inline bool work(double x){
	now.clear();
	//将所有映射区间预处理。 
	REP(i, 2, n) if (query(a[i], a[1], x)) return 0;
	now.PB(MP(-inf, -pi)), now.PB(MP(pi, inf));
	sort(now.begin(), now.end());
	double bf = now[0].SC;
	REP(i, 1, now.size() - 1){
		if (now[i].FT > bf + 1e-10) return 1;
		cmax(bf, now[i].SC);
	}
	return 0;
}

class CircusTents  
{  
        public:  
        double findMaximumDistance(vector <int> x, vector <int> y, vector <int> R)  
        {  
        	n = x.size();
        	REP(i, 1, n) a[i] = (Cir){(Pt){x[i - 1], y[i - 1]}, R[i - 1]};
        	double l = 0, r = 40000; 
        	//二分答案 
        	while (l + 1e-10 < r){
        		double mid = (l + r) / 2;
        		if (work(mid)) l = mid; else r = mid;
			}
			return l;
        }  

  
};  
 
