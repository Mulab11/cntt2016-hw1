#line 2 "TrafficCongestion.cpp"
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
#define mo 1000000007
typedef long long ll;
using namespace std;
class TrafficCongestion {
	public:
		int theMinCars(int H) {
			int ans = 1;
			for (int i = 1; i <= H; ++i)
				if (i & 1)
					ans = ((ans * 2) % mo + mo - 1) % mo; // 对于H较小的情况找规律，发现当i为奇数时，答案 = ans[i - 1] * 2 - 1,原本在(i - 1)中使用一笔画根结点，连成(i)后可以直接用一笔画完根结点和根的左右儿子。
				else
					ans = (ans * 2 + 1) % mo; // 否则，ans[i] = 2 * ans[i - 1] + 1,需要用额外的一笔画根结点
			return ans;
		}
};
