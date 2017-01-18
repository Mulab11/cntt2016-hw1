#line 2 "NewArenaPassword.cpp"
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
int n, fa[maxn], cnt[maxn][maxn]; // n是字符个数，fa[i]表示必须与第i个字符相同的最靠前的字符的位置，cnt[i][j]记录fa[x] == i && s[x] == 'a' + j的x的个数。
class NewArenaPassword {
	public:
		int minChange(string s, int K) {
			n = s.size();
			int ans = 0;
			for (int i = 0; i < n; ++i) fa[i] = i;
			cl(cnt);
			for (int i = 0; i < K; ++i)
				fa[n - K + i] = fa[i]; // 根据题目要求，这K对字符相同
			for (int i = 0; i < n; ++i)
				++cnt[fa[i]][s[i] - 'a']; // 统计cnt
			for (int i = 0; i < n; ++i)
				if (fa[i] == i) { // 找到一类必须相同的字符
					int sum = 0, mx = 0; // sum是这些字符的总个数，mx是其中出现最多的相同字符个数
					for (int j = 0; j < 26; ++j)
						sum += cnt[i][j], mx = max(mx, cnt[i][j]);
					ans += sum - mx; // 最优方案是把sum个都改成mx的颜色，代价是sum - mx
				}
			return ans;
		}
};
