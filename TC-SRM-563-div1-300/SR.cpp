
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
char s[N];
int cnt[N][N], a[N][N], now[N];

class FoxAndHandle  
{  
        public:  
        string lexSmallestName(string S)  
        {  
        	int n = S.size();
        	MEM(cnt, 0), MEM(now, 0);
        	REP(i, 1, n) s[i] = S[i - 1];
        	FOR(i, 26) a[n][i] = n + 1;
        	//首先预处理出每个字符往后最近的匹配字符对应的位置
			//以及每个位置往后每个字符的个数 
        	PER(i, n - 1, 0){
        		FOR(j, 26) a[i][j] = a[i + 1][j], cnt[i][j] = cnt[i + 1][j];
        		cnt[i][s[i + 1] - 'a']++;
        		a[i][s[i + 1] - 'a'] = i + 1;
			}
			int i = 0;
			string ans;
			FOR(tmp, n / 2)
				//贪心选取最小的而且合法的字母 
				FOR(j, 26) if (now[j] < cnt[0][j] / 2){
					int k = a[i][j], flag = 1;
					FOR(l, 26) if (now[l] + cnt[k - 1][l] < cnt[0][l] / 2){ flag = 0; break; }
					if (flag) {i = k, now[s[k] - 'a']++, ans.PB(s[k]); break; }
				}
			return ans;
        }  
      
};  
  
