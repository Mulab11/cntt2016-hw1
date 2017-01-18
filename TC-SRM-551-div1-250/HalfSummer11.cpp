#line 2 "ColorfulChocolates.cpp"
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
vector <int> pos[maxn]; // pos[i]存第i种颜色出现的位置
int n;　// 序列的长度
class ColorfulChocolates {
	public:
		int maximumSpread(string c, int lim) {
			n = c.size();
			for (int i = 0; i < 26; ++i) pos[i].clear();
			for (int i = 0; i < n; ++i) pos[c[i] - 'A'].pb(i);
			for (int len = n; len >= 1; --len) // 枚举连续相同段的长度len,开始位置l
				for (int l = 0; l + len - 1 < n; ++l) 
					for (int ch = 0; ch < 26; ++ch) // 枚举这段的颜色
						for (int s = 0; s + len - 1 < pos[ch].size(); ++s) {　// 挪到这段的，一定是这种颜色所有出现位置中连续的一段，这里枚举这连续一段的开始
							int sum = 0;
							for (int i = s; i < s + len; ++i) 
								sum += abs(pos[ch][i] - (l + i - s));　// 移到对应位置所需要的交换次数
							if (sum <= lim) return len;　// 若能在要求的步数内完成，这个len就是可行的
						}
			return 0;
		}
};


