
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
  
const int N = 2500 + 5;
int s[N], t[N], f[N], q[N], D1[N], D2[N];
void bfs(int d[], int x, int n){
	REP(i, 1, n) d[i] = -1;
	int l, r;
	for(d[q[l = r = 1] = x] = 0; l <= r; x = q[++l])
		REP(y, 1, n) if (!~d[y] && s[x] <= t[y] && s[y] <= t[x]) d[q[++r] = y] = d[x] + 1;
}
class ShoutterDiv1  
{  
        public:  
        void get(int a[], vector <string> A, vector <string> B, vector <string> C, vector <string> D, int &n){
        	n = 0; VEP(i, A) VEP(j, A[i]) a[++n] += (A[i][j] - '0') * 1000;
        	n = 0; VEP(i, B) VEP(j, B[i]) a[++n] += (B[i][j] - '0') * 100;
        	n = 0; VEP(i, C) VEP(j, C[i]) a[++n] += (C[i][j] - '0') * 10;
        	n = 0; VEP(i, D) VEP(j, D[i]) a[++n] += (D[i][j] - '0') * 1;
		}
        int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)  
        {  
        	int n;
        	MEM(s, 0), MEM(t, 0);
        	get(s, s1000, s100, s10, s1, n);
        	get(t, t1000, t100, t10, t1, n);
        	//设l为 ti最小的元素, r为si最大的元素, 那么i的消息被看到当且仅当这则消息被l和r都看到了.
        	int l = 0, r = 0;
        	REP(i, 1, n){
        		if (!l || t[i] < t[l]) l = i;
        		if (!r || s[i] > s[r]) r = i;
        	}
        	//从l，r开始bfs，找出最短距离 
        	bfs(D1, l, n), bfs(D2, r, n);
        	int ans = 0;
        	REP(i, 1, n) if (D1[i] == -1 || D2[i] == -1) return -1;
        	REP(i, 1, n) f[i] = max(D1[i] - 1, 0) + max(D2[i] - 1, 0);
        	//注意一种特殊转移。 
			REP(i, 1, n) REP(j, 1, n) if (s[i] <= s[j] && t[j] <= t[i]) cmin(f[j], f[i] + 1);
        	REP(i, 1, n) ans += f[i];
			return ans;
        }  
        

};  

