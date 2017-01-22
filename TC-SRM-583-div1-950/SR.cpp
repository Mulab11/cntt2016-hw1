
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
  
const int N = 21 + 5, M = 1500 + 5;
int f[N][M][2], s[N], a[N][N];
class RandomPaintingOnABoard  
{  
        public:  
        double expectedSteps(vector <string> prob)  
        {  
        	//答案经过x回合之后游戏没有结束的概率之和。
			//那么我们考虑游戏没有结束时那些行和列还未被覆盖。
			 
        	int n = prob.size(), m = prob[0].size(), All = 0;
        	if (n > m) {swap(n, m); FOR(i, n) FOR(j, m) a[i][j] = prob[j][i] - '0';}
        	else FOR(i, n) FOR(j, m) a[i][j] = prob[i][j] - '0';
        	FOR(i, n) FOR(j, m) All += a[i][j];
        	
        	double ans = 0;
			FOR(now, 1 << n){//枚举哪些行不取 
				MEM(s, 0), MEM(f, 0);
				int tot = 0, sum = 0;
				FOR(i, n) FOR(j, m) if (now >> i & 1) tot += a[i][j]; else s[j] += a[i][j];
				
				//哪些列不取我们可以通过dp容斥出来。 
				f[0][0][__builtin_popcount(now) & 1] = 1;
				FOR(i, m){
					REP(j, 0, sum) FOR(k, 2)
						f[i + 1][j + s[i]][k ^ 1] += f[i][j][k],
						f[i + 1][j][k] += f[i][j][k];
					sum += s[i];
				}
				
				REP(i, 0, sum) FOR(j, 2) if (i + tot) ans += (j ? 1 : -1) * (double)f[m][i][j] * All / (i + tot);
			}
			return ans;
        }  

};  

