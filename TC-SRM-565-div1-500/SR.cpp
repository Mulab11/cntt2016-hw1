
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
int f[N], a[N], num[N];

class TheDivisionGame  
{  
        public:  
        //判断素数 
        bool prime(int x){
        	int i = 2;
        	while (i * i <= x && x % i) ++i;
        	return i * i > x;
		}
        long long countWinningIntervals(int L, int R)  
        {  
        	//每个数的sg函数为该数可重复质因数数量 
        	MEM(f, 0), MEM(num, 0), MEM(a, 0);
        	REP(i, L, R) a[i - L] = i;
        	//筛法求素数 
        	REP(i, 2, sqrt(R)) if (prime(i))
        		for (int j = ((L - 1) / i + 1) * i; j <= R; j += i)
        			while (!(a[j - L] % i)) a[j - L] /= i, ++f[j - L];
        	REP(i, L, R) if (a[i - L] > 1) ++f[i - L];
        	
        	int now = 0;
        	//通过一个计数数组求出所有的sg为0的函数 
        	LL ans = LL(R - L + 2) * (R - L + 1) / 2;
        	num[0] = 1;
        	REP(i, L, R) now ^= f[i - L], ans -= num[now], num[now]++;
        	return ans;
        }  
        
};  

