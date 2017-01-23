#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;
const int MAXN = 205;

class MagicalHats{
	public:
		int dp[2000005], n, m, k, hcnt, row[15], col[15], three[15], c;
		pii hpos[15]; bool accept[8505];
		int solve(int dep, int st, int revealed, int hasCoin){ //0: undiscovered 1: doesn't contain coin 2: contains coin
			if(~dp[st]) return dp[st];
			if(dep == hcnt) return dp[st] = (accept[hasCoin] ? 0 : -MAXN);
			dp[st] = -MAXN; int i, op1, op2;
			for(i = 0; i < hcnt; ++ i)
				if((revealed & (1 << i)) == 0){
					op1 = solve(dep + 1, st + 2 * three[i], revealed | (1 << i), hasCoin | (1 << i)) + int(dep < k);
					op2 = solve(dep + 1, st + three[i], revealed | (1 << i), hasCoin);
					if(op1 < 0) dp[st] = max(dp[st], op2);
					else if(op2 < 0) dp[st] = max(dp[st], op1);
					else dp[st] = max(dp[st], min(op1, op2));
				}
			return dp[st];
		}
		void getStatus(int dep, int status, int ccnt, int ocnt){
			if(hcnt - dep + ccnt < c) return;
			if(dep == hcnt){
				accept[status] = !bool(ocnt);
				return;
			}
			if(ccnt != c) getStatus(dep + 1, status | (1 << dep), ccnt + 1, ocnt);
			if(row[hpos[dep].fi] ^= 1) ++ ocnt;
			else -- ocnt;
			if(col[hpos[dep].se] ^= 1) ++ ocnt;
			else -- ocnt;
			getStatus(dep + 1, status, ccnt, ocnt);
			if(row[hpos[dep].fi] ^= 1) ++ ocnt;
			else -- ocnt;
			if(col[hpos[dep].se] ^= 1) ++ ocnt;
			else -- ocnt;
		}
		int findMaximumReward(vector <string> mp, vector <int> coins, int ccnt){
			int i, j;
			sort(coins.begin(), coins.end());
			n = mp.size(), m = mp[0].length(), k = ccnt, c = coins.size();
			for(i = 0; i < n; ++ i)
				for(j = 0; j < m; ++ j)
					if(mp[i][j] == 'H')
						hpos[hcnt ++] = pii(i, j);
			for(i = three[0] = 1; i <= hcnt; ++ i)
				three[i] = three[i - 1] * 3;
			getStatus(0, 0, 0, 0);
			memset(dp, -1, sizeof(dp));
			if(solve(0, 0, 0, 0) < 0) return -1;
			for(i = j = 0; i < solve(0, 0, 0, 0); ++ i)
				j += coins[i];
			return j;
		}
}x;

int main(){
	const char *inp[] = {".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".....H.H.....",
 "......H......",
 ".....H.H.....",
 ".............",
 ".............",
 ".............",
 "............."};
	int c[] = {22}, step = 3;
	vector <string> graph(inp, inp + sizeof(inp) / sizeof(char *));
	vector <int> coin(c, c + sizeof(c) / sizeof(int));
	printf("%d\n", x.findMaximumReward(graph, coin, step));
	return 0;
}
