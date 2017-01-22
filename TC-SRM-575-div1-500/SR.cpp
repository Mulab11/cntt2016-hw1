
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
  
const int N = 1000000 + 5;
double f[N];
class TheSwapsDivOne  
{  
        public:  
        double find(vector <string> a, int k)  
        {  
        	vector<int> b;
        	VEP(i, a) VEP(j, a[i]) b.PB(a[i][j] - '0');
        	int n = b.size();
        	double ans = 0;
        	f[0] = 0;
        	//f[k]表示经过k次交换，i位置转移到j位置的概率(i!=j) 那么i==j的情况答案就是1-(n-1)*f[k]。 
        	REP(i, 1, k) f[i] = (f[i - 1] * (n - 1) * (n - 2) / 2 + 1 - (n - 1) * f[i - 1] + (n - 2) * f[i - 1]) * 2 / (n * (n - 1));
        	int sum = 0;
        	FOR(i, n) sum += b[i];
        	FOR(i, n) ans += (i + 1) * (n - i) * (f[k] * (sum - b[i]) + (1 - (n - 1) * f[k]) * (b[i]));
        	ans = ans * 2 / (n * (n + 1));
        	return ans;
        }  
        

  
};  

