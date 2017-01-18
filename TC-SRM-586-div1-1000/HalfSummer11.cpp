#line 2 "StringWeight.cpp"
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
/*
   串中有四种字母：
   1.第一次出现的，贡献为-pos，
   2.最后一次出现的，贡献为+pos
   3.只出现了这一次的，贡献为0
   4.既不是最后一次也不是第一次出现的，贡献为0
   dp时，依次考虑每一段，枚举其中第1,2类的字母个数，贪心地把它们安排在头/尾处，剩下的字母贪心安排为第4类，再剩下的安排为第3类，因为第3类会对未出现的字母个数造成损失。
*/
int f[maxn][maxn][maxn]; // f[i][j][k]表示考虑前i段，有j个字母还没有出现过，k个字母已经出现过，还要继续出现，此时的贡献和
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class StringWeight {
	public:
		int getMinimum(vector <int> L) {
			int n = L.size();
			int sum = 0;
			memset(f, 0x3f, sizeof(f));
			f[0][26][0] = 0;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j <= 26; ++j) // 还未使用的字母个数
					for (int k = 0; k + j <= 26; ++k) // 已经使用，还未结束的字母个数
						if (f[i][j][k] < oo) {
							int tot = min(L[i], 26); // 此段使用的字母种数
							for (int a = 0; a <= min(tot, j); ++a) // 新出现的字母个数
								for (int c = 0; c <= k && a + c <= tot; ++c) { // 已结束的字母个数
									int d = min(tot - a - c, k - c), b = tot - a - c - d; // d : 既不是第一次出现，也不是最后一次出现的字母个数，b : 只出现一次的字母个数。这里d越大越好，最大不能超过min(tot - a - c, k - c), b则需要省着用O.O...
									if (a + b > j) continue; // a和b都是当前段新出现的字母，不能超过j
									if (d) // 存在中间状态的字母，用它填充中间的位置
										gmin(f[i + 1][j - a - b][k - c + a], f[i][j][k] + c * sum + c * (c + 1) / 2 - a * (sum + L[i]) + a * (a - 1) / 2);
									else // 否则，需要拉长最后一个R/最先一个L/中间的某个只出现一次的，代价都是L[i] - a - c - b
										gmin(f[i + 1][j - a - b][k - c + a], f[i][j][k] + c * sum + c * (c + 1) / 2 - a * (sum + L[i]) + a * (a - 1) / 2 + L[i] - a - c - b);
								}
						}
				sum += L[i];
			}
			int ans = oo;
			for (int i = 0; i <= 26; ++i)
				ans = min(ans, f[n][i][0]);
			return ans;
		}
};
