
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
double h[N][N][N], f[N][N][N];
struct Data{double a, b, c;} a[N], g[N][N][N];
inline Data operator * (const Data &x, const double &y){ return (Data){x.a * y, x.b * y, x.c * y}; }
inline Data operator / (const Data &x, const double &y){ return (Data){x.a / y, x.b / y, x.c / y}; }
inline Data operator += (Data &x, const Data y){ x = (Data){x.a + y.a, x.b + y.b, x.c + y.c}; }
inline double calc(const Data &p){ return max(p.a + p.c * 3, max(p.b + p.a * 3, p.c + p.b * 3)); }
class RockPaperScissors  
{  
        public:  
        double bestScore(vector <int> A, vector <int> B, vector <int> C)  
        {  
        	int n = A.size();
        	MEM(g, 0), MEM(f, 0), MEM(h, 0);
        	h[0][0][0] = 1, f[0][0][0] = 1;
        	REP(i, 1, n) a[i] = (Data){(double)A[i - 1] / 300, (double)B[i - 1] / 300, (double)C[i - 1] / 300};
        	//h表示处理前i个骰子已经掷出了x个石头y个布z个剪刀的概率。 
        	//g表示处理前i个骰子已经掷出了x个石头y个布z个剪刀，在其余骰子中掷出石头布剪刀的概率 
        	REP(i, 1, n) PER(x, i, 0) PER(y, i - x, 0) PER(z, i - x - y, 0){
        		g[x][y][z] += a[i] * h[x][y][z];
        		if (x) g[x][y][z] += g[x - 1][y][z] * a[i].a, h[x][y][z] += h[x - 1][y][z] * a[i].a;
        		if (y) g[x][y][z] += g[x][y - 1][z] * a[i].b, h[x][y][z] += h[x][y - 1][z] * a[i].b;
        		if (z) g[x][y][z] += g[x][y][z - 1] * a[i].c, h[x][y][z] += h[x][y][z - 1] * a[i].c;
			}
			double ans = 0;
			//f表示总游戏中已经掷出了x个石头y个布z个剪刀的概率。 
			FOR(x, n) FOR(y, n - x) FOR(z, n - x - y) if (f[x][y][z] > 0){
				g[x][y][z] = g[x][y][z] / h[x][y][z] / (n - x - y - z);
				f[x + 1][y][z] += f[x][y][z] * g[x][y][z].a;
				f[x][y + 1][z] += f[x][y][z] * g[x][y][z].b;
				f[x][y][z + 1] += f[x][y][z] * g[x][y][z].c;
				ans += calc(g[x][y][z]) * f[x][y][z];
			}
			return ans;
        }  

  
};  

