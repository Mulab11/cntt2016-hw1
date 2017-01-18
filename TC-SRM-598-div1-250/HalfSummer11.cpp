#line 2 "BinPacking.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
bool used[maxn]; // used[i]标记第i个item是否已经装好
class BinPacking {
	public:
		int minBins(vector <int> item) {
			sort(item.begin(), item.end());
			reverse(item.begin(), item.end()); // 从大到小排序
			int n = item.size();
			int ret = 0;
			cl(used);
			for (int i = 0; i < n; ++i) {
				if (used[i]) continue;
				if (item[i] == 100) // 表示之后的n - i个均为100，还需要ceil((n - i) / 3)个桶
					return ret + ((n - i) + 2) / 3;
				for (int j = i + 1; j < n; ++j) // 否则，桶里最多能装下两个item，寻找最大的可以和它放在一起的item j
					if (!used[j] && item[i] + item[j] <= 300) {
						used[j] = 1; break;
					}
				++ret;
			}
			return ret;
		}
};
