
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
typedef pair<LL, int> PI;
const LL inf = 0x7ffffffffffffffll;
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
  
const int K = 50 + 5, N = K * K;
int v[K][K], pos[K][K], e[N][N];
LL d[N];
priority_queue<PI, vector<PI>, greater<PI> > q;
void add(int x, int y, int z){ e[x][y] = z; }
class SkiResorts{  
        public:  
        long long minCost(vector <string> a, vector <int> b)  
        {  
        	MEM(e, -1);
        	
        	int n = a.size();
        	
        	int tot = 0;
        	
        	//以一个二元组[i, j]作为一个节点，表示i号节点修改为b[j]值得时候的答案
			//然后两两之间建边 
        	FOR(i, n) FOR(j, n) pos[i][j] = ++tot, v[i][j] = abs(b[i] - b[j]);
        	
        	int s = 0, t = tot + 1;
        	FOR(i, n) FOR(j, n)	FOR(k, n) FOR(l, n)
				if (a[i][k] == 'Y' && b[j] >= b[l]) add(pos[i][j], pos[k][l], v[k][l]);
			FOR(i, n) add(0, pos[0][i], v[0][i]);
			FOR(i, n) add(pos[n - 1][i], t, 0);
			
			REP(i, s, t) d[i] = inf;
			
			//dijkstra 
			q.push(MP(d[0] = 0, 0));
			while (!q.empty()){
				int x = q.top().SC;
				if (q.top().FT == d[x]){
					q.pop();
					REP(y, s, t) if (e[x][y] != -1 && d[x] + e[x][y] < d[y]) q.push(MP(d[y] = d[x] + e[x][y], y));
				}
				else q.pop();	
			}
			return d[t] == inf ? -1 : d[t]; 
        }  

};  

