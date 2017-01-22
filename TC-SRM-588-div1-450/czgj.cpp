/*
	Brute force dp
	With a little optimization...
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 1 << 12;
int sum[MAXN];
int dp[MAXN][233];
class KeyDungeonDiv1 {
	public:
	int maxKeys(vector <int> dR, vector <int> dG, vector <int> rR, vector <int> rG, vector <int> rW, vector <int> keys) {
		int n = dR.size(), m = (1 << n) - 1;
		rep(i, 0, m) sum[i] = keys[0] + keys[1] + keys[2];
		rep(i, 0, 11) rep(j, 0, m) if (j >> i & 1) sum[j] += rR[i] + rG[i] + rW[i] - dR[i] - dG[i]; // subset sum
		memset(dp, -1, sizeof dp); // -1 for invalid
		dp[0][keys[0]] = keys[2]; // initial state
		int ret = 0;
		rep(i, 0, m) rep(j, 0, 150) if (dp[i][j] != -1){ // if ok
			ret = max(ret, sum[i]); // upd
			int R = j, W = dp[i][j], G = sum[i] - R - W;
			rep(k, 0, n - 1) if (~i >> k & 1){ // attempt to open door #k
				int R1 = R - min(R, dR[k]), G1 = G - min(G, dG[k]), W1 = W - max(dR[k] - R, 0) - max(dG[k] - G, 0);
				if (W1 < 0) continue; // not enough keys
				R1 += rR[k]; G1 += rG[k]; W1 += rW[k];
				dp[i | 1 << k][R1] = max(dp[i | 1 << k][R1], W1); // trans
			}
		}
		return ret;
	}
};

/*
	Oto mo naku tobi kau
	Toki no kakera
		- Naraku no Hana
*/
