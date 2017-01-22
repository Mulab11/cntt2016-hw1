
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
struct Edge{ int nxt, to; } e[N * 2];
int hd[N], tail;
void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
int dfs(int x, int f){//不难发现对于一个节点来说，至多有一个儿子子树中不含有信标。 
	int ans = 0, flag = 0;
	DFOR(i, x, y) if (y != f){
		int tmp = dfs(y, x);
		ans += max(1, tmp);
		if (tmp == 0) flag = 1;
	}
	return ans - flag;
}
class TPS  
{  
        public:  
        int minimalBeacons(vector <string> A)  
        {  
        	int n = A.size();
			if (n == 1) return 0;
			else{
				MEM(hd, 0), tail = 0;
				FOR(i, n) FOR(j, n) if (A[i][j] == 'Y') add(i, j);
				int ans = inf;
				FOR(i, n) cmin(ans, dfs(i, -1) + 1);//枚举一个信标作为根 
				return ans;
			}
        }  
  
};  
