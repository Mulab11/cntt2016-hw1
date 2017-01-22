
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
struct Pt{ int x, y; } a[N];
vector<Pt> D, U;
Pt f[200000 + 5];
inline bool operator < (const Pt &a, const Pt &b){ return a.x < b.x || a.x == b.x && a.y < b.y; }
inline bool operator != (const Pt &a, const Pt &b){ return a < b || b < a; }
inline Pt operator - (const Pt &a, const Pt &b){ return (Pt){a.x - b.x, a.y - b.y}; }
inline LL operator * (const Pt &a, const Pt &b){ return (LL)a.x * b.y - (LL)b.x * a.y; }
double calc(const Pt &a, const Pt &b, const int x){
	return double(b.y - a.y) * double(x - a.x) / double(b.x - a.x) + a.y;
}
class ConvexPolygonGame  
{  
        public:  
        string winner(vector <int> X, vector <int> Y)  
        {  
        	//直接判断凸包内是否存在一个三角形即可
			//然后如果统计所有点，点个数超过200001即可跳出。 
        	D.clear(), U.clear();
        	int n = X.size(), l = 0, r = 0, tot = 0;
        	FOR(i, n){
				a[i] = (Pt){X[i], Y[i]};
				if (a[i] < a[l]) l = i;
				if (a[r] < a[i]) r = i;
			}
        	for (int x = l; x != r; x += 1, x %= n) D.PB(a[x]); D.PB(a[r]);
        	for (int x = l; x != r; x += n - 1, x %= n) U.PB(a[x]); U.PB(a[r]);
        	int u = 0, d = 0;
        	REP(x, a[l].x, a[r].x){
        		while (U[u + 1].x < x) ++u;
        		while (D[d + 1].x < x) ++d;
        		int low, high;
        		if (U[u].x == U[u + 1].x && x == U[u].x) high = max(U[u].y, U[u + 1].y);
        		else high = int(floor(calc(U[u], U[u + 1], x) + 1e-10));
        		if (D[d].x == D[d + 1].x && x == D[d].x) low = min(D[d].y, D[d + 1].y);
        		else low = int(ceil(calc(D[d], D[d + 1], x) - 1e-10));
        		REP(y, low, high) if ((Pt){x, y} != U[u] && (Pt){x, y} != D[d] && (Pt){x, y} != U[u + 1] && (Pt){x, y} != D[d + 1]){
        			f[++tot] = (Pt){x, y};
	      			if (tot >= 3 && ((f[1] - f[2]) * (f[tot] - f[2]) != 0))	return "Masha";
        			if (tot > 200001) return "Masha";
				}
				
			}
			return "Petya";
        }  
  
};  

