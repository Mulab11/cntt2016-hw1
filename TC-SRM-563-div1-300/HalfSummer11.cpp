#line 2 "FoxAndHandle.cpp"
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
int n, rest[26][maxn], used[26], poi[26], cnt[26], pos[26][maxn];
// n 是字符串的长度，rest[i][j]记录从第j个位置到字符串末尾，有多少个字符i，used[i]记录当前答案中i字母出现的次数，poi[i]表示在当前位置之后，第一个出现的字母i，是所有字母i中的第几个，cnt[i]表示字母i在S中出现的总次数，pos[i][j]表示第j个i字母出现的位置
class FoxAndHandle {
	public:
		string lexSmallestName(string S) {
			cl(cnt); cl(rest); cl(used); cl(poi);
			n = S.size();
			for (int i = 0; i < n; ++i)
				pos[S[i] - 'a'][++cnt[S[i] - 'a']] = i; // 记录每种字母的每个出现位置
			for (int i = 0; i < 26; ++i) cnt[i] /= 2;
			for (int i = n - 1; i >= 0; --i) 
				for (int j = 0; j < 26; ++j)
					rest[j][i] = rest[j][i + 1] + (S[i] - 'a' == j); // 计算rest
			string ans = ""; int now = 0;
			for (int c = 0; c < 26; ++c) poi[c] = 1; // 指针初始置为1
			for (int i = 0; i < n / 2; ++i) { // 逐位确定答案
				for (int c = 0; c < 26; ++c) // 找尽量小的字母
					if (poi[c] <= 2 * cnt[c] && used[c] < cnt[c]) { // 条件，ans中这个字母还没有出现足够的次数，且S中这个字母还没用完（其实判前者就行了……
						bool flag = 1; ++used[c]; // 假设c出现在答案的这一位
						for (int d = 0; d < 26; ++d)
							if (rest[d][pos[c][poi[c]] + 1] < cnt[d] - used[d]) // 如果选了这个字母之后，后面的字母不够凑出余下的ans
								flag = 0;
						if (flag) {
							now = pos[c][poi[c]] + 1; // 移动指针
							for (int d = 0; d < 26; ++d) // 移动每个字母对应的指针
								while (poi[d] <= 2 * cnt[d] && pos[d][poi[d]] < now) ++poi[d];
							ans = ans + char('a' + c);
							break;
						} else {
							--used[c];
						}
					}
			}
			return ans;
		}
};
