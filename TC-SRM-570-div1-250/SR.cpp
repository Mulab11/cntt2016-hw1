
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
  
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
class RobotHerb  
{  
        public:  
        long long getdist(int T, vector <int> a)  
        {  
        	//由于每四次运行该序列的话，会回到原来的方向，那么我们可以对4取一个循环算出相对位移，剩余的进行模拟。 
        	LL x = 0, y = 0;
        	int fx = 0;
        	FOR(NUM, 4) VEP(i, a) x += dx[fx] * a[i], y += dy[fx] * a[i], (fx += a[i]) %= 4;
        	x *= T / 4, y *= T / 4, T %= 4;
        	FOR(NUM, T) VEP(i, a) x += dx[fx] * a[i], y += dy[fx] * a[i], (fx += a[i]) %= 4;
        	return abs(x) + abs(y);
        }  
        
};  

