
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

const int N = 2000 + 5, M = N * 16, K = 25 + 5;
struct Edge{int nxt, to, flow, val; } e[M];
int q[2000000 + 5], s, t, tail, hd[N], d[N], b[N], fa[N], fa_edge[N];
char f[K][K];
int pos[K][K], LR[K][K], UD[K][K];

void add(int x, int y, int flow, int value){
	if (x == -1 || y == -1) return;
	e[++tail].nxt = hd[x], e[tail].to = y, e[tail].flow = flow, e[tail].val = value, hd[x] = tail;
	e[++tail].nxt = hd[y], e[tail].to = x, e[tail].flow = 0, e[tail].val = -value, hd[y] = tail;
}
int spfa(){
	REP(i, s, t) d[i] = inf, b[i] = 0;
	d[q[0] = s] = 0, b[s] = 1;
	for (int l = 0, r = 0; l <= r; l++){
		int x = q[l];
		DFOR(i, x, y)
			if (e[i].flow && d[x] + e[i].val < d[y]){
				d[y] = d[fa[y] = x] + e[fa_edge[y] = i].val;
				if (!b[y]) b[q[++r] = y] = 1;
			}
		b[x] = 0;
	}
	return d[t];
}
int augment(int x, int f){
	if (x == s) return f;
	int i = fa_edge[x];
	int flow = augment(fa[x], min(f, e[fa_edge[x]].flow));
	e[i].flow -= flow, e[i ^ 1].flow += flow;
	return flow;
}
class CurvyonRails  
{  
        public:  
        
        int getmin(vector <string> field)  
        {  
        	//最小费用最大流模型。 
        	int tot = 0, A = 0, B = 0;
        	int n = field.size(), m = field[0].size();
        	MEM(pos, -1), MEM(hd, 0);
        	
        	REP(i, 1, n) REP(j, 1, m) f[i][j] = field[i - 1][j - 1];
        	REP(i, 1, n) REP(j, 1, m) 
				if (f[i][j] != 'w'){
					pos[i][j] = ++tot, LR[i][j] = ++tot, UD[i][j] = ++tot;
					if ((i ^ j) & 1) ++A; else ++B;
				}
        	
        	s = 0, t = tot + 1, tail = 1;
        	//LR 表示该点在横方向的映射， UD 代表纵方向的映射 
			REP(i, 1, n) REP(j, 1, m) if (f[i][j] != 'w')
				if ((i ^ j) & 1){
					add(s, pos[i][j], 2, 0);
					add(pos[i][j], LR[i][j], 1, 0), add(pos[i][j], LR[i][j], 1, f[i][j] == 'C'); //如果该点是关键点的话，往同一个方向的映射的话，需要1的费用。 
					add(pos[i][j], UD[i][j], 1, 0), add(pos[i][j], UD[i][j], 1, f[i][j] == 'C');
					add(LR[i][j], LR[i][j + 1], 1, 0), add(LR[i][j], LR[i][j - 1], 1, 0);
					add(UD[i][j], UD[i + 1][j], 1, 0), add(UD[i][j], UD[i - 1][j], 1, 0);
				}
				else{
					add(pos[i][j], t, 2, 0);
					add(LR[i][j], pos[i][j], 1, 0), add(LR[i][j], pos[i][j], 1, f[i][j] == 'C');
					add(UD[i][j], pos[i][j], 1, 0), add(UD[i][j], pos[i][j], 1, f[i][j] == 'C');
				}
			
			if (A != B) return -1;	//如果黑点个数不等于白点则不合法 
			int ans = 0, maxflow = 0;	
			while (spfa() < inf){
				int flow = augment(t, inf);
				maxflow += flow;
				ans += flow * d[t];
			}
			return maxflow == A * 2 ? ans : -1;//如果最大流没有流满说明不合法 
        }  
        
  
};  

