
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

const int N = 100 + 5;
int col[N], hd[N], tail;
struct Edge{ int nxt, to, dis; } e[N * N * 2];
void add(int x, int y, int z){
	e[++tail] = (Edge){hd[x], y, z}, hd[x] = tail;
	e[++tail] = (Edge){hd[y], x, z}, hd[y] = tail;
}
int dfs(int x, int f){
	if (~col[x]) if (col[x] == f) return 0; else return 1;
	col[x] = f; DFOR(i, x, y) if (dfs(y, f ^ e[i].dis)) return 1;
	return 0;
}
class ThreeColorability  
{  
        public:  
        vector <string> lexSmallest(vector <string> a)  
        {  
        	//一个合法方案满足对于任意两行或两列序列相反或是相等。
			//那么我们对于每行或每列进行01标号，然后通过染色判断是否合法。
			 
        	int n = a.size(), m = a[0].size();
        	tail = 0, MEM(hd, 0);
        	FOR(i, n) FOR(j, m) if (a[i][j] != '?')
        		if (a[i][j] == 'Z') add(i, j + n, 1); else add(i, j + n, 0);
        		
        	MEM(col, -1);
        	vector<string> ans;
        	if (dfs(0, 0)) return ans;
        	//由于字典序要最小，我们先根据第一行的颜色染所有的列
        	REP(i, n, n + m - 1) if (!~col[i] && dfs(i, col[0])) return ans;
        	//再根第一列的颜色染剩下的行 
        	REP(i, 1, n - 1) if (!~col[i] && dfs(i, col[n])) return ans;
        	FOR(i, n){
        		string s;
				FOR(j, m) s.PB(col[i] ^ col[j + n] ? 'Z' : 'N');
				ans.PB(s);
			}
			return ans;
        }  

};  

