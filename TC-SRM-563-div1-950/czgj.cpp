#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
typedef pair<PI, PI> PII;
const int MAXN = 44;
const int MOD = 1000000009;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
bool valid[MAXN][MAXN];
int label[MAXN][MAXN], newlabel[MAXN][MAXN];
int pow2[MAXN * MAXN], cnt[MAXN * MAXN];
int n, m, scnt, ans;
map<PII, int> id;
// Attempt a move from (x, y) to the direction d and return the label
int Label(int x, int y, int d){
	return valid[x + dx[d]][y + dy[d]] ? label[x + dx[d]][y + dy[d]] : label[x][y];
}
class CoinsGame {
	public:
	int ways(vector <string> board) {
		n = board.size(); m = board[0].size();
		memset(valid, 1, sizeof valid); // Set the outer border to be valid.
		pow2[0] = 1; scnt = 0;
		for (int i = 1; i <= n * m; ++i)
			pow2[i] = (pow2[i - 1] * 2) % MOD;
		// Initially, label = 1 for every valid grid inside, = 0 for every grid outside.
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
			scnt += label[i][j] = valid[i][j] = board[i - 1][j - 1] == '.';
		int tot = 0, ans = pow2[scnt] - 1;
		bool changed = 0;
		do{
			id.clear(); tot = changed = 0;
			// Calculate new labels and set their numbers & counts.
			for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (valid[i][j]){
				PII tmp = PII(PI(Label(i, j, 0), Label(i, j, 1)), PI(Label(i, j, 2), Label(i, j, 3)));
				if (!id.count(tmp)) cnt[id[tmp] = ++tot] = 0;
				++cnt[newlabel[i][j] = id[tmp]];
			}
			// Update the labels.
			for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
				if (valid[i][j] && newlabel[i][j] != label[i][j]){
					changed = 1;
					label[i][j] = newlabel[i][j];
				}
		}while(changed);
		// Exclude the invalid cases for each group.
		for (int i = 1; i <= tot; ++i)
			ans = (ans + MOD - (pow2[cnt[i]] - 1)) % MOD;
		return ans;
	}
};
