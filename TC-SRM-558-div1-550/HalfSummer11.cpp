#line 2 "Ear.cpp"
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
#define maxn 350
typedef long long ll;
using namespace std;
int n, m, rx[maxn], bx[maxn], by[maxn]; // n是红点的个数，m是蓝点的个数，rx是红点的横坐标，bx是蓝点的横坐标，by是蓝点的纵坐标
int read(int &pos, string s) { // 从s的第pos位开始读一个整数
	int len = s.length();
	int ret = 0;
	while (pos < len && s[pos] == ' ') ++pos;
	while (pos < len && s[pos] >= '0' && s[pos] <= '9') {
		ret = ret * 10 + s[pos] - '0'; ++pos;
	}
	return ret;
}
int count(int l, int r) { // 在排序的rx数组中，寻找位于(l, r)中的数的个数
	return lower_bound(rx + 1, rx + n + 1, r) - rx - 1 - (upper_bound(rx + 1, rx + n + 1, l) - rx - 1);
} 
class Ear {
	public:
		long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY) {
			string tmp = ""; int pos; // 读入数据
			for (int i = 0; i < redX.size(); ++i)
				tmp = tmp + redX[i];
			pos = 0; n = 0; 
			while (pos < tmp.size()) 
				rx[++n] = read(pos, tmp);
			tmp = "";
			for (int i = 0; i < blueX.size(); ++i)
				tmp = tmp + blueX[i];
			pos = 0; m = 0;
			while (pos < tmp.size())
				bx[++m] = read(pos, tmp);
			tmp = "";
			for (int i = 0; i < blueY.size(); ++i)
				tmp = tmp + blueY[i];
			pos = 0; m = 0;
			while (pos < tmp.size())
				by[++m] = read(pos, tmp);
			sort(rx + 1, rx + n + 1);
			ll ans = 0;
			for (int l = 1; l <= n; ++l) // 枚举耳朵的最左端点
				for (int i = 1; i <= m; ++i) // 上面的蓝点
					for (int j = 1; j <= m; ++j)  // 下面的蓝点
						if (rx[l] < bx[i] && 1ll * (bx[i] - rx[l]) * by[j] - 1ll * (bx[j] - rx[l]) * by[i] < 0 && by[i] > by[j]) { // 若这几个点可能成为一个耳朵的一部分
							ll now = count(rx[l], bx[j]); // 第二个红点的个数
							if (now <= 0) continue;
							int lb = bx[j], rb = bx[i]; // 第三个红点的横坐标需要大于lb，它只要在下面这个蓝点的右边就可以了；第四个红点的横坐标需要大于rb，它不仅需要在上面那个蓝点的右边，还需要在两个蓝点所在直线与x轴的交点右边，此时才能保证下方蓝点在大三角形内
							if (bx[i] != bx[j])
								rb = max(rb, int(floor((1.0 * bx[i] * by[j] - 1.0 * bx[j] * by[i]) / 1.0 / (by[j] - by[i])))); // 计算两个蓝点所在直线与x轴的交点
							if (rb <= lb) { // 由于第四个红点需要在第三个蓝点右侧，因此lb < x3 < x4, 方案数就是在lb右侧的红点中任选两个的方案数
								int cnt = count(lb, rx[n] + 1); 
								if (cnt < 2) continue;
								ans += 1ll * now * cnt * (cnt - 1ll) / 2ll;
							} else {
								int cnt1 = count(lb, rx[n] + 1), cnt2 = count(rb, rx[n] + 1); 
								cnt1 -= cnt2; // 否则，第四个红点有cnt2种选择，第一种选择对应了cnt1个可选的第三个红点，第二种对应了cnt1+1个...总方案数是cnt1 + (cnt1 + 1) + ... + (cnt1 + cnt2 - 1)
								if (cnt1 < 0 || cnt2 <= 0) continue;
								ans += 1ll * now * (2ll * cnt1 + cnt2 - 1ll) * cnt2 / 2ll;
							}
						}
			return ans;
		}
};
