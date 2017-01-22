
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
  
const int N = 300 + 5;
int hd[N], tail, A[5], B[5];
struct Edge{ int nxt, to; } e[N * 2];
class TreeUnion  
{  
        public:  
        void add(int x, int y){
        	e[++tail] = (Edge){hd[x], y}, hd[x] = tail;
        	e[++tail] = (Edge){hd[y], x}, hd[y] = tail;
		}
		//分别统计两棵树里距离为1，2，3，4的点。 
        void dfs(int x, int f, int dis, int A[]){
        	if (dis > 4) return;
        	A[dis]++;
        	DFOR(i, x, y) if (y != f) dfs(y, x, dis + 1, A);
		}
        void format(vector <string> tree, int &n, int A[]){
        	MEM(hd, 0), tail = 0, n = 1;
        	int num = 0;
        	VEP(i, tree) VEP(j, tree[i]) 
				if (tree[i][j] == ' ') add(num, n++), num = 0;
				else num = num * 10 + tree[i][j] - '0';
			add(num, n++), num = 0;
			
			FOR(i, n) dfs(i, i, 0, A);
		}
        double expectedCycles(vector <string> tree1, vector <string> tree2, int K)  
        {  
        	int n;
        	MEM(A, 0), MEM(B, 0);
        	format(tree1, n, A), format(tree2, n, B);
        	LL ans = 0;
        	//合并两棵树的答案。 
        	REP(i, 1, 4) if (K - i - 2 > 0 && K - i - 2 <= 4) 
				ans = ans + (LL)A[i] * B[K - i - 2];
			return (double)ans / 2 / n / (n - 1);
        }  
        

};  

