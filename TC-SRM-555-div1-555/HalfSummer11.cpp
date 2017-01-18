#line 2 "XorBoard.cpp"
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
#define maxn 3010
#define mo 555555555
typedef long long ll;
using namespace std;
int c[maxn][maxn]; //  组合数
void add(int &a, int b) {
	a += b; a %= mo;
}
class XorBoard {
	public:
		int count(int H, int W, int R, int C, int S) {
			int up = max(max(H, W), max(R / 2 + H, C / 2 + W));
			int ans = 0;
			for (int i = 0; i <= up; ++i) { // 预处理组合数
				c[i][0] = 1;
				for (int j = 1; j <= i; ++j)
					c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
			}
			for (int n = 0; n <= H; ++n) // 枚举被翻了奇数次的行数n
				for (int m = 0; m <= W; ++m) // 枚举被翻了奇数次的列数m
					if ((H - n) * m + (W - m) * n == S) // 算1的个数
						if (R >= n && (R - n) % 2 == 0 && C >= m && (C - m) % 2 == 0) { // 需要翻n次不同的行，接着每个行都被翻偶数次，因此要满足R >= n && (R - n) % 2 == 0, C与m同理
							int now = 1ll * c[H][n] * c[(R - n) / 2 + H - 1][H - 1] % mo; // 对于行，先从H个行里挑出n个，各翻一次，方案数C(H, n),剩下的R - n次两两配对，随意地分给H个行，方案数C((R - n) / 2 + H - 1, H - 1)
							now = 1ll * now * c[W][m] % mo * c[(C - m) / 2 + W - 1][W - 1] % mo; // 列与行同理
							add(ans, now); 
						}
			return ans;
		}
};

