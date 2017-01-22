
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
  
int f[(1 << 12) + 5][500 + 5];
class KeyDungeonDiv1  
{  
        public:  
        int maxKeys(vector <int> AR, vector <int> AG, vector <int> BR, vector <int> BG, vector <int> BW, vector <int> key)  
        {  
        	int n = AR.size();
        	MEM(f, -1);
        	
        	//考虑状态压缩dp,f[i][j]表示开过的门状态为i，自己拥有j把红钥匙时，拥有最多的白钥匙数量。
			//因为开过的门确定下来了，那么钥匙总数就确定了，同时我们在绿钥匙和白钥匙之间，我们保持白钥匙数量最多一定是最优的。 
        	f[0][key[0]] = key[2];
        	int ans = 0;
        	FOR(now, 1 << n){
        		int tot = key[0] + key[1] + key[2];
        		FOR(i, n) if (now >> i & 1) tot += - AR[i] - AG[i] + BR[i] + BG[i] + BW[i];
        		FOR(i, n) if (now >> i & 1 ^ 1)
        			REP(j, 0, tot) if (~f[now][j]){
        				int tmpR = j, tmpW = f[now][j], tmpG = tot - tmpR - tmpW;
        				if (tmpR < AR[i]) tmpW -= AR[i] - tmpR, tmpR = 0; else tmpR -= AR[i];
        				if (tmpG < AG[i]) tmpW -= AG[i] - tmpG;
        				if (tmpW >= 0) cmax(f[now | 1 << i][tmpR + BR[i]], tmpW + BW[i]);
					}
				REP(i, 0, tot) if (~f[now][i]) cmax(ans, tot);
			}
			return ans;
        }  
};  
