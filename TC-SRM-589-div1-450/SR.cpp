
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
#define SFOR(i, x, y) for(int &i = sta[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
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

const int N = 50 + 5, M = N * N * 2;
struct Edge{ int nxt, to, flow; } e[M];
int num[N], sta[N], hd[N], tail, s, t, q[N];

//网络流模板 
void add(int x, int y, int z){
	e[++tail].nxt = hd[x], e[tail].to = y, e[tail].flow = z, hd[x] = tail;
	e[++tail].nxt = hd[y], e[tail].to = x, e[tail].flow = 0, hd[y] = tail;
}
bool bfs(){
	int l, r;
	REP(i, s, t) num[i] = -1, sta[i] = hd[i];
	for (num[q[l = r = 0] = s] = 0; l <= r; l++){
		int x = q[l];
		DFOR(i, x, y)
			if (e[i].flow && !~num[y])
				num[y] = num[x] + 1, q[++r] = y;
	}
	return ~num[t];
}
int dfs(int x, int f){
	if (!f || x == t) return f;
	int g = 0;
	SFOR(i, x, y){
		if (e[i].flow && num[x] + 1 == num[y]){
			int k = dfs(y, min(f - g, e[i].flow));
			e[i].flow -= k, e[i ^ 1].flow += k, g += k;
		}
		sta[x] = i;
		if (f == g) return g;
	}
	return g;
}

int work(int C1, int C2, string C, vector<string> G){
	int n = C.size(), ans = 0;
	MEM(hd, 0), s = 0, t = n + 1, tail = 1;
	FOR(i, n) FOR(j, n) if (C[i] == C1 && C[j] == C2 && G[i][j] == 'Y') add(i + 1, j + 1, 1);
	FOR(i, n) if (C[i] == C1) add(s, i + 1, 1);
	FOR(i, n) if (C[i] == C2) add(i + 1, t, 1);
	while (bfs()) ans += dfs(0, 1 << 30);
	return ans;
}

class GearsDiv1  
{  
        public:  
        int getmin(string C, vector <string> G)  
        {  
        	//不难发现我们可以枚举颜色的方向，然后问题就转化为二分图最小点覆盖的问题。 
        	return min(min(work('R', 'G', C, G), work('G', 'B', C, G)), work('B', 'R', C, G));
        }  
};  

