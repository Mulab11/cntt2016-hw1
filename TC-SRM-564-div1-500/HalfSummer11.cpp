#line 2 "AlternateColors2.cpp"
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
typedef long long ll;
using namespace std;
ll C2(ll n) { // C(n, 2)
	return n >= 2ll ? n * (n - 1) / 2ll : 0ll;
}
class AlternateColors2 {
	public:
		long long countWays(int n, int k) {
			ll ans = 0;
			if (k % 3 == 1) // 前k - 1个是RGBRGBRGBRGB...
				ans += C2(n - k + 2); // 后面的n - k个分成三份
			for (int i = 0; 2 * i <= k - 1; ++i) // R与G/B中一个在之前各出现i次，另一种颜色出现k - 1 - 2 * i, 比i少，已经用完了
				if (k - 1 - 2 * i < i) 
					ans += 2ll * (n - k + 1); // 2是G/B中选一个，剩下n - k个球分成两份
			for (int i = 0; i <= k - 1; ++i) // R之前用了i个，G和B用的个数都比i少
				if (k - 1 - i <= 2 * i - 2) // G/B都比i少
					if (k - 1 - i > i - 1)
						ans += 3ll * i - k; // 分配方案数
					else
						ans += k - i;
			return ans;
		}
};
