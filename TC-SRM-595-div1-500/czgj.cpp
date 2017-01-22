/*
	Brute force
	Pre-process
	Prefix (suffix?) sum
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 2560;
int sum[MAXN][MAXN], val[MAXN][MAXN];

class LittleElephantAndRGB {
	public:
	long long getNumber(vector <string> list, int mg) {
		memset(sum, 0, sizeof sum);
		string st; rep(i, 0, (int)list.size() - 1) st += list[i];
		int n = st.length();
		// for each substring find the longest prefix, suffix, substring consists of only 'G'
		rep(i, 0, n - 1){
			int pre = 0, str = 0, suf = 0; bool brk = 0;
			rep(j, i, n - 1){
				if (st[j] == 'G') pre += !brk, str = max(str, ++suf);
					else suf = 0, brk = 1;
				sum[i][str >= mg ? mg : min(pre, mg)]++;
				val[i][j] = str >= mg ? 0 : max(0, mg - suf);
			}
		}
		red(i, n - 1, 0) red(j, mg, 0) sum[i][j] += sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1]; // suffix sum
		LL ret = 0;
		rep(i, 0, n - 1) rep(j, i, n - 1) ret += sum[j + 1][val[i][j]]; // for each [a, b] find the number of [c, d]
		return ret;
	}
};

/*
	Spicy chicken game
	Steal my money
	Rob my life
		- NO SSR PLZ
*/
