
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
  
const int N = 26 + 5;
int cnt[N];
class LittleElephantAndString  
{  
        public:  
        int getNumber(string A, string B)  
        {  
        	//只要看B的最长的后缀 能和A的子序列相匹配即可。 
        	int n = A.size();
        	MEM(cnt, 0);
        	FOR(i, n) ++cnt[A[i] - 'A'], --cnt[B[i] - 'A'];
        	FOR(i, 26) if (cnt[i]) return -1;
        	int j = n - 1;
        	ROF(i, n){
        		while (j >= 0 && B[i] != A[j]) --j;
        		if (j < 0) return i + 1;
        		--j;
			}
			return 0;
        }  
  
};  

