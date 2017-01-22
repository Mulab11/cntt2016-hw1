
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

const int N = 50 + 5, M = (1 << 16) + 5;
vector<int> All, sub[M];
int f[N][M], hd[N], g[M], n, m, can[M], tail, tmp[N];

struct Edge{ int nxt, to; } e[N];  
void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
bool cmp(const string &a, const string &b){ return a.size() < b.size(); }

void dfs(int x){
	//dp 
	f[x][0] = 1;
	DFOR(i, x, y){
		dfs(y);
		VEP(j, All) g[All[j]] = 0;
		VEP(j, All){
			int A = All[j];
			VEP(k, sub[A]){
				int B = sub[A][k];
				g[A] = (g[A] + (LL)f[x][B] * f[y][A - B]) % MOD;
			}
		}
		VEP(j, All) f[x][All[j]] = g[All[j]];
	}
	if (x != n)
		ROF(i, All.size()){
			int A = All[i];
			for (int tmp = A, B = A & (-A); tmp; tmp -= B, B = tmp & (-tmp))
				f[x][A] = (f[x][A] + f[x][A - B]) % MOD;
		}
}
class SimilarNames  
{  
        public:  
        int count(vector <string> s, vector <int> a, vector <int> b)  
		{ 
			All.clear(), MEM(f, 0), MEM(can, 0), MEM(hd, 0), tail = 0;
			
			n = s.size(), m = a.size();
			
			//离散化 
			int tot = 0;
			FOR(i, m) tmp[++tot] = a[i], tmp[++tot] = b[i];
			sort(tmp + 1, tmp + tot + 1);
			tot = unique(tmp + 1, tmp + tot + 1) - tmp - 1;
			FOR(i, m)
				a[i] = lower_bound(tmp + 1, tmp + tot + 1, a[i]) - tmp - 1,
				b[i] = lower_bound(tmp + 1, tmp + tot + 1, b[i]) - tmp - 1;
					
			//预处理可能状态及其子集					
			FOR(now, 1 << tot){
				bool flag = 1;
				FOR(i, m) if ((now >> a[i] & 1) && (now >> b[i] & 1 ^ 1)){ flag = 0; break; }
				if (flag) All.PB(now), can[now] = 1; 
			}
			VEP(i, All){
				sub[All[i]].clear();
				for(int A = All[i], B = A; ; B = (B - 1) & A){
					if (can[B] && can[A - B]) sub[A].PB(B);
					if (!B) break;
				}
			}
			
			//建树 
			sort(s.begin(), s.end(), cmp);
			FOR(i, n){
				int fa = n;
				PER(j, i - 1, 0) if (s[i].substr(0, s[j].size()) == s[j]){ fa = j; break; }
				add(fa, i);
			}

			dfs(n);
			int ans = f[n][(1 << tot) - 1];
			FOR(i, n - tot) ans = (LL)ans * (i + 1) % MOD;
			return ans;
        }  

};  

