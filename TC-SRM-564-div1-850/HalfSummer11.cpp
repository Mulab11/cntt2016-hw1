#line 2 "DefectiveAddition.cpp"
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
#define mo 1000000007
typedef long long ll;
using namespace std;
int n, val[maxn][maxn], digit[maxn][maxn], ans; // n是数的个数，val[i][d]表示第i个数后d位上的数值，digit[i][d]表示第i个数第d位上的数, ans是答案
int f[maxn][2]; // f[i][j]表示考虑前i个数，当前位上的异或结果为d，这种情况下前i个数的选取方案数
void add(int &a, int b) {
	a += b; a %= mo;
}
class DefectiveAddition {
	public:
		int count(vector <int> a, int goal) {
			n = a.size(); ans = 0;
			for (int i = 0; i < n; ++i) 
				for (int d = 0; d <= 30; ++d) {
					val[i][d] = (a[i] & ((1 << (d + 1)) - 1));
					digit[i][d] = bool(a[i] & (1 << d));
				}
			int tmp = 0;
			for (int i = 0; i < n; ++i) tmp ^= a[i]; // 所有数均达到上限的情况
			if (tmp == goal) add(ans, 1);
			for (int d = 30; d >= 0; --d) { // 一个数若没有达到上限，存在一个位置，使得这个位置前这个数与上限相同，这个位置上比上限小。枚举所有数中这个位置的最大值(最靠前的)d
				tmp = 0;
				for (int i = 0; i < n; ++i)
					tmp ^= a[i];
				if ((tmp ^ goal) >= (1 << (d + 1))) continue; // 所有数第d位之前的部分都与上限相同，验证这部分是否与goal相符
				for (int fir = 0; fir < n; ++fir) { // 枚举这个0最早出现，且编号最小的数fir。因为fir的d以后的位可以任取，所以，只要使得第d位的异或和与goal相符，别的数d以后的位就可以在取值范围内任取，通过fir的后d - 1位调整为与goal相符
					if (digit[fir][d] == 0) continue; // 需要满足上限在该位为1
					int now = 0, meth = 1; cl(f); // now记录第d位上当前的异或和，meth记录方案数
					for (int i = 0; i < fir; ++i) { // 编号比它小的数，第d位均与上限相同，后d - 1位在上限内任取
						now ^= digit[i][d];
						if (d) meth = 1ll * meth * (val[i][d - 1] + 1) % mo;
					}
					f[fir][now] = 1;
					for (int i = fir + 1; i < n; ++i) // 枚举之后的每个数第d位的选择
						for (int j = 0; j <= 1; ++j) {
							if (digit[i][d] == 0) 
								add(f[i][j], 1ll * f[i - 1][j] * (d ? (val[i][d - 1] + 1) : 1) % mo); // 只能取0，后面在上限内任取
							else {
								add(f[i][j ^ 1], 1ll * f[i - 1][j] * (d ? (val[i][d - 1] + 1) : 1) % mo); // 可以取1，后面在上限内任取
								add(f[i][j], 1ll * f[i - 1][j] * (1 << d) % mo); // 取0，后面任取
							}
						}
					meth = 1ll * f[n - 1][bool(goal & (1 << d))] * meth % mo;
					add(ans, meth);
				}
			}
			return ans;
		}
};
