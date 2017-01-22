#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 9;
const int M = 1 << 8 | 1;

inline void upd(int &x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}

class StringPath {
private :
	int dp[2][9][M][M];	
	// dp[i][j][S1][S2] 表示dp到(i,j) 两个串的存在情况为 S1, S2 的方案数
	// 此处的存在情况指是否存在一条从 (1,1) 到某位置的串和给定串的前缀相匹配
	inline bool exist(int s, int p) {
		return ((s >> p) & 1) || ((s >> (p+1)) & 1);
	}
	inline int set1(int s, int p) {
		return (s & p) ? s : s ^ p;
	}
	inline int set0(int s, int p) {
		return (s & p) ? s ^ p : s;
	}
public :
	// 集合DP
	// 发现A,B 两串每一位出现的位置是一条斜线
	// 将棋盘旋转45度，进行按格转移的状压DP
	// 转移时枚举填入的字符是否是 A,B 对应位字符即可
	int countBoards(int n, int m, string A, string B) {
		if (A[0] != B[0])  return 0;
		int t = 0, sm = min(n, m), bi = max(n, m);
		dp[t][0][1][1] = 1;
		rep (i, 1, n+m-2) {
			int f = n >= i+1;
			// f 为 1 当且仅当当前DP的这条斜线的左下角格只和上一条斜线的一个格子相邻
			int len = i+1 < bi ? min(i+1, sm) : n+m-i-1;
			// len 表示这一条斜线上的点数
			rep (p, 0, len - 1) {
				rep (l1, 0, bin(8) - 1) {
					rep (l2, 0, bin(8) - 1) {
						if (dp[t][p][l1][l2]) {
							int x = dp[t][p][l1][l2];
							int t1 = l1, t2 = l2;
							if (!p && f) {
								t1 <<= 1, t2 <<= 1;
							}
							int v1 = exist(t1, p) << p;		//v1, v2 记录填入A,B 串对应字符之后，串的存在情况是否会发生变化
							int v2 = exist(t2, p) << p;
							t1 = set0(t1, bin(p));		//t1, t2 记录填入其他字符之后，转移到的新状态
							t2 = set0(t2, bin(p));
							if (p == len-1) {
								t1 = set0(t1, bin(len));
								t2 = set0(t2, bin(len));
							}
							if (A[i] == B[i]) {
								upd(dp[t][p + 1][t1 ^ v1][t2 ^ v2], x);
								upd(dp[t][p + 1][t1][t2], (LL) x * 25 % mo);
							} else {
								upd(dp[t][p + 1][t1 ^ v1][t2], x);
								upd(dp[t][p + 1][t1][t2 ^ v2], x);
								upd(dp[t][p + 1][t1][t2], (LL) x * 24 % mo);
							}
						}
					}
				}
			}
			memcpy(dp[t ^ 1][0], dp[t][len], sizeof(dp[t][len]));
			memset(dp[t], 0, sizeof(dp[t]));
			t ^= 1;
		}
		return dp[t][0][1][1];
	}
};
