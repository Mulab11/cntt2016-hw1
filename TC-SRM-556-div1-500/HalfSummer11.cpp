#line 2 "LeftRightDigitsGame2.cpp"
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
bool f[maxn][maxn]; // f[l][r]为1，表示可以使得最终数字的[l, r]这些位与目标相符
int n;
bool check(string s, string t) { // 检查能否使得最终数字的情况为t
	cl(f);
	for (int i = 0; i <= n; ++i) f[i + 1][i] = 1;
	for (int l = n; l >= 1; --l)
		for (int r = l; r <= n; ++r) { 
			int k = n - (r - l + 1); // 目前的空位是[l, r],下一个被放的是s中的第k个字符
			if (s[k] == t[l - 1] || t[l - 1] == '?') f[l][r] |= f[l + 1][r]; // 可以放在最左端
			if (s[k] == t[r - 1] || t[r - 1] == '?') f[l][r] |= f[l][r - 1]; // 可以放在最右端
		}
	return f[1][n];
}
class LeftRightDigitsGame2 {
	public:
		string minNumber(string s, string lim) {
			n = s.length(); reverse(s.begin(), s.end()); // 将s翻转，放数字的规则变为：每次取出第一个数字，放在空位的最左端或者最右端
			for (int pos = n - 1; pos >= -1; --pos) { // 枚举答案串和lim最后一个相同的位pos
				string tmp = lim;
				for (int i = 0; i < n; ++i) tmp[i] = '?';
				for (int i = 0; i <= pos; ++i) tmp[i] = lim[i]; // 前pos位与lim相同
				if (check(s, tmp)) { 
					if (pos == n - 1) // 若能造出和lim一样的串，返回它 
						return tmp;
					else {
						for (char k = lim[pos + 1] + 1; k <= '9'; ++k) { // 枚举第pos + 1位的数字
							tmp[pos + 1] = k;
							if (check(s, tmp)) { // 若可行，就确定了答案串的前pos+1位
								for (int i = pos + 2; i < n; ++i) { // 剩下的位逐位枚举数字，确定答案
									for (char k = '0'; k <= '9'; ++k) {
										tmp[i] = k;
										if (check(s, tmp)) break;
									}
								}
								return tmp;
							}
						}
					}
				}
			}
			return "";
		}
};
