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
int a[N], f[N][N * N];

class KingdomAndDice  
{  
        public:  
        double newFairness(vector <int> firstDie, vector <int> secondDie, int X)  
        {  
        	MEM(a, 0), MEM(f, 0);
        	
        	sort(firstDie.begin(), firstDie.end());
        	sort(secondDie.begin(), secondDie.end());
        	
        	int tot = 0, n = firstDie.size(), m = 0;
        	
        	RUN(i, firstDie) RUN(j, secondDie) if (*i > *j) ++tot;
        	RUN(i, firstDie) if (*i == 0) ++m;
     		secondDie.PB(X + 1);
     		
     		REP(i, 1, n){
     			a[i] = secondDie[i] - secondDie[i - 1] - 1;
     			RUN(j, firstDie) if (*j > secondDie[i - 1] && *j < secondDie[i]) --a[i];
			}
			
			FOR(i, m) f[i][0] = 1;
			REP(k, 1, n) REP(runtimes, 1, min(a[k], m))
				PER(i, m, 1) REP(j, k, n * i) f[i][j] |= f[i - 1][j - k];
			
			int ans = tot;
			REP(i, 0, n * n) if (f[m][i] && abs(n * n - (tot + i) * 2) < abs(n * n - ans * 2)) ans = tot + i;
			return (double)ans / (n * n);
        }  

};  

