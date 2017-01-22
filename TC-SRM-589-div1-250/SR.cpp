
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
int cnt[N], fa[N], mx[N];
int getfa(int x){ return x == fa[x] ? x : fa[x] = getfa(fa[x]); }
class GooseTattarrattatDiv1  
{  
        public:  
        int getmin(string S)  
        {  
        	int n = S.size(), ans = 0;
        	//如果回文对应位置的两个字母不相同那么，他们最终肯定要变成同一个字母
			//所以我们用并查集维护这种关系，并获得答案。 
        	MEM(cnt, 0);
        	FOR(i, n) cnt[S[i] - 'a']++;
			FOR(i, 26) fa[i] = i, mx[i] = cnt[i];
			FOR(i, n / 2) fa[getfa(S[i] - 'a')] = getfa(S[n - i - 1] - 'a');
			FOR(i, 26) if (fa[i] != i) cnt[getfa(i)] += cnt[i], cmax(mx[getfa(i)], mx[i]);
			FOR(i, 26) if (fa[i] == i) ans += cnt[i] - mx[i];
			return ans;
        }  

};  

