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

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

const int N = 100 + 5, M = N * N * 4;
struct Edge{ int nxt, to, flow; } e[M];
int tail, s, t, hd[N], sta[N], num[N], q[N];
//ÍøÂçÁ÷Ä£°å 
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
class OldBridges  
{  
        public:  
        string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)  
        {  
        	int n = bridges.size(), flow = 0;
        	++a1, ++a2, ++b1, ++b2;
        	s = 0, t = n + 1;
        	
        	MEM(hd, 0), tail = 1, flow = 0;
        	REP(i, 1, n) REP(j, 1, n) 
				if (bridges[i - 1][j - 1] == 'O') add(i, j, 1); else
				if (bridges[i - 1][j - 1] == 'N') add(i, j, inf);
			add(s, a1, an), add(s, b1, bn);
			add(a2, t, an), add(b2, t, bn);
			while (bfs()) flow += dfs(s, inf);
			if (flow < an + bn) return "No";
			
			MEM(hd, 0), tail = 1, flow = 0;
        	REP(i, 1, n) REP(j, 1, n) 
				if (bridges[i - 1][j - 1] == 'O') add(i, j, 1); else
				if (bridges[i - 1][j - 1] == 'N') add(i, j, inf);
			add(s, a1, an), add(s, b2, bn);
			add(a2, t, an), add(b1, t, bn);
			while (bfs()) flow += dfs(s, inf);
			if (flow < an + bn) return "No";
			
			return "Yes";
        }  
};  
