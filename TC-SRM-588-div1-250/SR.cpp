
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
const int inf = 0x3f3f3f3f;
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

const int N = 100 + 5;
PI a[N];
int f[N][N];

class GUMIAndSongsDiv1  
{  
        public:  
        int maxSongs(vector <int> A, vector <int> B, int T)  
        {  
        	//肯定是从小到大唱或者从大到小唱，顺序无关所以直接排序进行dp即可。 
        	int n = A.size();
        	REP(i, 1, n) a[i] = MP(B[i - 1], A[i - 1]);
        	sort(a + 1, a + n + 1);
        	MEM(f, 0x3f), f[0][0] = 0;
        	REP(i, 1, n) REP(j, 1, i) PER(k, i - 1, 0) 
        		cmin(f[i][j], f[k][j - 1] + (k ? abs(a[i].FT - a[k].FT) : 0) + a[i].SC);
        	
        	int ans = 0;
        	REP(i, 1, n) REP(j, 1, i) if (f[i][j] <= T) cmax(ans, j);
        	return ans;
        }  
    
};  

