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
  
const int N = 100000 + 5;
int n, a[N], b[N];

bool pd(int x){
	REP(i, 1, n) b[i] = a[i];
	REP(i, 1, n)
		if (b[i] > b[i - 1]) b[i] = max(b[i] - x, b[i - 1] + 1);
		else 
			if (b[i] + x <= b[i - 1]) return 0;
			else b[i] = b[i - 1] + 1;
	return 1;		
}
  
class KingdomAndTrees  
{  
        public:  
        int minLevel(vector <int> heights)  
        {  
			n = heights.size();
			REP(i, 1, n) a[i] = heights[i - 1];
			
			int l = 0, r = inf;
			while (l < r){
				int mid = l + r >> 1;
				if (pd(mid)) r = mid; else l = mid + 1;
			}
			return l;
        }  
        
};  

