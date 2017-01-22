
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
  
  
class BallsSeparating  
{  
        public:  
        int minOperations(vector <int> red, vector <int> green, vector <int> blue)  
        {  
        	int n = red.size(), ans = inf;
        	if (n < 3) return -1; // 盒子个数小于3则不合法 
        	//我们枚举最终三色球移动到的盒子。 剩余的盒子保留最多个数的球。 
        	FOR(i, n) FOR(j, n) FOR(k, n) if (i != j && j != k && k != i){
        		int tmp = red[i] + green[i]  +  green[j] + blue[j]  +  blue[k] + red[k];
        		FOR(l, n) if (l != i && l != j && l != k) tmp += min(min(red[l] + green[l], green[l] + blue[l]), blue[l] + red[l]);
        		cmin(ans, tmp);
			}
			return ans;
        }  
   
};  

