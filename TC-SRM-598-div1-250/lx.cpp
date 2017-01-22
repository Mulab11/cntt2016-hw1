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

class BinPacking {
public :
	// 贪心
	// 贪心配对能装 2 个物品的桶
	// 再把能装三个物品的桶装好
	int minBins(vector<int> obj) {
		sort(obj.begin(), obj.end());		//按重量排序
		int n = obj.size(), c100 = 0;
		int res = 0;
		down (i, n-1, 0) {			//从大到小考虑每个物品
			if (obj[i] > 0) {
				if (obj[i] == 100) {		//特别考虑重量为100的物品
					++c100;
				} else {
					down (j, i-1, 0) {
						if (obj[j] > 0 && obj[i] + obj[j] <= 300) {		//贪心配对
							obj[j] = -1;
							break ;
						}
					}
					++res;
				}
			}
		}
		return res + (c100 + 2) / 3;
	}
};
