
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
  
  
class HyperKnight  
{  
        public:  
        long long countCells(int a, int b, int n, int m, int K)  
        {  
        	//我们可以通过将横纵坐标分别划分成5个区域，整个矩形一共划分成25个区域，每个区域的可跳的方案数相同，所以我们每个点选一个数出来判断一下是否可行。 
			//如果方案可行，我们把这块矩形的答案加上便可以。 
    		int A[6] = {0, a, b, n - a, n - b, n},
				B[6] = {0, a, b, m - a, m - b, m},
				X[8] = {a, b, b, a, -a, -b, -b, -a},
				Y[8] = {-b, -a, a, b, b, a, -a, -b};
    		LL ans = 0; 
    		sort(A, A + 6), sort(B, B + 6);
    		REP(i, 1, 5) REP(j, 1, 5){
    			int tot = 0;
    			FOR(k, 8) if (A[i] + X[k] > 0 && A[i] + X[k] <= n && B[j] + Y[k] > 0 && B[j] + Y[k] <= m) ++tot;
    			if (tot == K) ans += LL(A[i] - A[i - 1]) * (B[j] - B[j - 1]);
			}
			return ans;
        }  
    
};  

