
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
int f[N * 20000], sum[N];
class MayTheBestPetWin  
{  
        public:  
        int calc(vector <int> A, vector <int> B)  
        {  
        	//不难发现最终答案只和某一部分中的ai+bi的和有关。 
        	int n = A.size();
        	MEM(f, 0);
			f[0] = 1;
			REP(i, 1, n) sum[i] = sum[i - 1] + A[i - 1] + B[i - 1];
			FOR(i, n) PER(j, sum[i], 0) f[j + A[i] + B[i]] |= f[j]; 
			int a = 0, b = 0, ans = inf;
			FOR(i, n) a += A[i], b += B[i];
			REP(j, 0, sum[n]) if (f[j]) cmin(ans, max(b - j, j - a));
			return ans;
        }  

};  
