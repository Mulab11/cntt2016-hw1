#line 2 "TheDevice.cpp"
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
int n, m, cnt[maxn][2]; // n是数的个数，m是数的位数，cnt[i][j]表示第i位上j出现了几个
class TheDevice {
	public:
		int minimumAdditional(vector <string> p) {
			cl(cnt);
			n = p.size(); m = p[0].size();
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					++cnt[j][p[i][j] - '0'];
			int ans = 0;
			for (int i = 0; i < m; ++i) {
				if (cnt[i][1] >= 2 && cnt[i][0] >= 1) continue; // 有至少2个1，1个0，才能分辨出这位上的运算符
				ans = max(ans, max(2 - cnt[i][1], 0) + max(1 - cnt[i][0], 0));
			}
			return ans;
		}
};
