#line 2 "Mountains.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define mo 1000000009
typedef long long ll;
using namespace std;
/* 倒着放山，一座山在某个位置是否可见，取决于它放入之前这个位置上的最大高度。
   以每个位置的最大高度，目前放了的山数为状态记忆化搜索，可以证明状态数是O(W * 2 ^ n)的
*/
map <pair <string, int>, int> M; // M[mp<S, i>]表示后i座山放完后，m个位置的最大高度为S时，此时放接下来山的方案数
vector <int> H; // H[i]是第i座山的高度
vector <string> V; // V[i][j]表示第i座山在第j个位置是否可见
int n, m;
int dfs(pair <string, int> sta) { // 记忆化搜索
	if (sta.sc == n) return 1;
	if (M.count(sta)) return M[sta];
	M[sta] = 0;
	int &ret = M[sta];
	int x = n - sta.sc - 1;
	for (int pos = 0; pos < m; ++pos) { // 枚举第x座山的山顶位置pos
		bool flag = 1; string nxt = "";
		for (int j = 0; j < m; ++j) { // 判断每个位置是否合法，并记录最大高度
			int h = H[x] - abs(j - pos);
			if (h > int(sta.fr[j])) {
				nxt = nxt + char(h);
				if (V[x][j] == '-') {
					flag = 0; break;
				}
			} else {
				nxt = nxt + sta.fr[j];
				if (V[x][j] == 'X') {
					flag = 0; break;
				}
			}
		}
		if (flag) ret = (ret + dfs(mp(nxt, sta.sc + 1))) % mo;
	}
	return ret;
}
class Mountains {
	public:
		int countPlacements(vector <int> heights, vector <string> visability) {
			H = heights; V = visability; n = H.size(); m = V[0].size();
			M.clear(); string sta = "";
			for (int i = 0; i < m; ++i) sta = sta + char(0); // 初始最大高度均为0
			return dfs(mp(sta, 0));
		}
};

