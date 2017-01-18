#line 2 "CheckerExpansion.cpp"
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
string calc(ll t, ll x, ll y)
{
	// t个回合后，只有以(0, 2t - 2)为底的等腰直角三角形内可能有棋子
	if (y - x > 0ll) return ".";
	if (y < 0ll) return ".";
	if (x + y > 2ll * t - 2ll) return ".";
	ll size = 2;
	while (size - 2 < x + y) size <<= 1ll; // 找到(x, y)所位于的三角形
	string ret;
	if ((x + y) % 4ll == 0) ret = "A"; else ret = "B"; // 若(x, y)处有棋子，它的种类可以由x + y除以4的余数判断出来
	// 棋子摆放情况是一个自相似的三角形，下面把它递归到大小为1的三角形 
	while (size > 2) {
		if (y < size / 4ll) {
			if (x + y > size / 2ll - 2ll && x - y < size / 2ll) return "."; // 位于中间的空白倒三角，返回空白
			if (x >= size / 2ll) x -= size / 2ll;
		} else {
			y -= size / 4ll;
			x -= size / 4ll;
		}
		size /= 2ll;
	}
	return ret;
}
class CheckerExpansion {
	public:
		vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
			vector <string> ans;
			for (int i = 0; i < h; ++i) {
				string str = "";
				for (int j = 0; j < w; ++j)
					str = str + calc(t, x0 + j, y0 + h - i - 1);
				ans.pb(str);
			}
			return ans;
		}
};


