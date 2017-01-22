
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

int col[N], hd[N], vis[N], tail, n;
struct Edge{ int nxt, to, dis; } e[N * N * 2];
vector<PI> p;
vector<int> w;
class DisjointSemicircles  
{  
        public:  
        void clear_graph(){ tail = 0, MEM(hd, 0); }
        void add(int x, int y, int z){ 
			e[++tail] = (Edge){hd[x], y, z}, hd[x] = tail; 
			e[++tail] = (Edge){hd[y], x, z}, hd[y] = tail; 
		}
        bool label(int x, int tp){
        	if (~col[x])
				if (col[x] == tp) return 1;
				else return 0;
			else{
				col[x] = tp;
				DFOR(i, x, y) if (!label(y, tp ^ e[i].dis)) return 0;
			}
			return 1;
		}
		bool judge(int n){
			MEM(col, -1);
			FOR(i, n) if (!~col[i] && !label(i, 0)) return 0;
			return 1;
		}
		bool dfs(int x, int dep){//算法二，当配对的较多时，我们枚举剩下的配对方式，然后每个配对作为点，建图，然后答案就是判断是否为二分图 
			if (dep == w.size() / 2){
				clear_graph();
				VEP(i, p) VEP(j, p)
					if (p[i].FT < p[j].FT && p[j].FT < p[i].SC && p[i].SC < p[j].SC)
						add(i, j, 1);
				return judge(p.size());	
			}
			while (vis[x]) ++x;
			REP(y, x + 1, w.size() - 1) if (!vis[y]){
				vis[y] = 1, p.PB(MP(x, y));
				if (dfs(x + 1, dep + 1)) return 1;
				vis[y] = 0, p.pop_back();
			}
			return 0;
		}
        bool work2(){
        	MEM(vis, 0);
        	return dfs(0, 0);
		}
        bool work1(){//算法一，当未配对的较多时，枚举配对的半圆的方向，然后转化为01值亦或条件，然后遍历一遍求解。 
        	FOR(now, 1 << p.size()){
        		vector<PI> q[2];
        		VEP(i, p) q[now >> i & 1].PB(p[i]);
        		bool flag = 1;
        		FOR(k, 2) VEP(i, q[k]) REP(j, i + 1, q[k].size() - 1)
        			if (q[k][i].FT < q[k][j].FT && q[k][j].FT < q[k][i].SC && q[k][i].SC < q[k][j].SC) flag = 0;
				if (flag){ 
					clear_graph();
					add(0, n, 0);
					FOR(k, 2) VEP(i, q[k]) add(q[k][i].FT, q[k][i].FT + 1, k), add(q[k][i].SC, q[k][i].SC + 1, k), add(q[k][i].FT + 1, q[k][i].SC, (q[k][i].SC - q[k][i].FT - 1) & 1 & (k ^ 1));
					if (judge(n)) return 1;
				}
			}
			return 0;
		}
        string getPossibility(vector <int> labels)  
        {  
        	p.clear(), w.clear();
        	n = labels.size();
        	FOR(i, n) if (~labels[i]) REP(j, i + 1, n - 1) if (labels[i] == labels[j])
        		p.PB(MP(i, j));
        	FOR(i, n) if (!~labels[i]) w.PB(i);
        	return (p.size() <= 19 ? work1() : work2()) ? "POSSIBLE" : "IMPOSSIBLE";
        }  
   
};  

