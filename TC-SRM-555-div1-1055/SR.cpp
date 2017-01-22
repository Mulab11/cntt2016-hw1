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

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 40 + 5;  
int n, m;
LL S[N];
char c[N];
vector <LL> P;
class MapGuessing  
{  
        public:  
        LL dfs(int x, LL s){
        	if (x == m) return 1ll << (__builtin_popcountll(s));
       		if (__builtin_popcountll(s) == 0) return 0ll;//如果当前集合为空，停止搜索直接返回答案。 
       		
        	return dfs(x + 1, s) - dfs(x + 1, s & P[x]);
		}
        long long countPatterns(string goal, vector <string> code)  
        {  	
        	string a = goal, b;
			VEP(i, code) b += code[i];
			n = a.size();
			P.clear();
			MEM(S, 0);
			
			FOR(i, n){
				//now存储的是到当前匹配的位置，bad是不匹配的位置。由于当前不匹配之后说不定可以覆盖，所以要记录bad； 
				int k = i;
				LL now = 0, bad = 0;
				MEM(c, -1);
				VEP(j, b){
					if (b[j] == '>') ++k;
					if (b[j] == '<') --k;
					if (b[j] == '1' || b[j] == '0'){
						c[k] = b[j];
						if (a[k] != c[k]) bad |= 1ll << k;
						else now |= 1ll << k, bad &= (1ll << n) - 1 - (1ll << k);
					}
					if (!bad) S[i] |= now;//只有当前不存在不匹配的位置才可以更新集合。 
					if (k < 0 || k >= n) { S[i] = -1; break; }
				}
			}
			FOR(i, n) if (S[i] != -1) P.PB(S[i]);
			m = P.size();
			return (1ll << n) - dfs(0, (1ll << n) - 1);
        }  
};  
