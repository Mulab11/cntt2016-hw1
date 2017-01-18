#line 2 "FoxPaintingBalls.cpp"
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
ll calc(ll l, ll r) { // 计算l + (l + 1) + ... + r
	if (l > r) return 0;
	return 1ll * (l + r) * (r - l + 1) / 2ll;
}
class FoxPaintingBalls {
	public:
		long long theMax(long long R, long long G, long long B, int N) {
			// a, b分别表示放在三角形最上方的那种颜色的球和剩下两种颜色的球在一个三角形中的出现次数
			ll a = calc(1ll, (N + 2ll) / 3ll) + calc(1ll, N / 3ll) + calc(0, (N + 1ll) / 3ll - 1ll);
			ll b = calc(0ll, (N + 2ll) / 3ll - 1) + calc(1ll, (N + 1ll) / 3ll) + calc(1ll, N / 3ll);
			if (a == b) return min(R, min(G, B)) / a; // 如果三种球出现的次数相同，答案显然是最少的球 / 每个三角形所需个数
			ll r = (R + G + B) / (2ll * b + a); // 否则，a = b + 1, 限制三角形个数的有两个因素：1.球的总数. 2.最少的那种颜色有多少个球，这里分别作出处理
			if (b) r = min(r, min(R, min(G, B)) / b);
			return r;
		}
};

