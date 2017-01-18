#line 2 "StringGame.cpp"
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
#define maxs 30
typedef long long ll;
using namespace std;
// alphabet确定后，一定是把字符从小到大排列最优。此时就像比较数字大小一样比较字符串。逐位确定alphabet，每位上必须选择使得当前串该字符个数不小于任意未被淘汰串的字符个数的字符。如果没有符合条件的，就失败，否则，若有多个符合条件的，它们选择的先后顺序不影响结果，随便选一个就可以了。
int n, m, cnt[maxn][maxs]; // n是字符串的个数，m是字符串的长度，cnt[i][c]表示第i个字符串中字符c的出现次数
bool used[maxs], del[maxn]; // used[c]标记字符c是否在alphabet中使用过，del[i]表示第i个串目前是否已经比当前串大
class StringGame {
	public:
		vector <int> getWinningStrings(vector <string> S) {
			cl(cnt);
			n = S.size(); m = S[0].size();
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < m; ++j)
					++cnt[i][S[i][j] - 'a'];
			vector<int> ans;
			for (int i = 0; i < n; ++i) {
				bool flag = 1; cl(used); cl(del); del[i] = 1;
				for (int dig = 0; dig < 26; ++dig) { // 逐位确定alphabet
					bool found = 0;
					for (int c = 0; c < 26; ++c) {
						if (used[c]) continue; // 尝试使用一个没有用过的字符
						bool ok = 1;
						for (int j = 0; j < n; ++j)
							if (!del[j] && cnt[j][c] > cnt[i][c]) {
								ok = 0; break; // 需要满足：对于前若干位与第i个字符串相等的串，它们的这种字符个数不超过i中该种字符个数
							}
						if (ok) {
							for (int j = 0; j < n; ++j)
								if (!del[j] && cnt[j][c] < cnt[i][c])
									del[j] = 1; // 在当前位比i大，删去
							used[c] = 1;
							found = 1;
							break;
						}
					}
					if (!found) {
						flag = 0; break; // 找不到符合条件的字符
					}
				}
				for (int j = 0; j < n; ++j)
					if (!del[j]) flag = 0; // 之前只保证没有字符串比它大，这一步检查是否所有字符串都比它小
				if (flag) ans.pb(i);
			}
			return ans;
		}
};
