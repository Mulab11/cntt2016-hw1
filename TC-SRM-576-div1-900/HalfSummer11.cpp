#line 2 "CharacterBoard.cpp"
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
#define maxn 110
#define maxm 10010
#define maxd 400010
#define mo 1000000009
#define div divv
typedef long long ll;
using namespace std;
/*
   考虑一个长度为L的generator，它合法的条件是，任意两个距离能被L整除的给出字符是相同的。它对应的字符串个数 = 26 ^ 不确定的位置个数。不确定的位置个数 = L - 所有位置% L的不同余数个数.
   把所有出现过的距离找出来（200个以下），把它们的约数找出来。对于一个不能整除任意dis的L，它的合法性是可以保证的，同时，由于所有字符的pos % L的余数各不相同，不确定的位置个数就等于L - 字符个数。可以用快速幂把这些L对答案的贡献一并算出。
   对于找到的约数，再暴力验证合法性 + 计算不确定位置的个数，计入答案。
*/
ll pos[maxn], dis[maxm], div[maxd]; // pos[i]表示第i个给出的格子是大矩形中的第i个格子。dis[]记录所有出现过的格子之间的距离，div[]记录所有dis[i]的约数。
int n, m, tot, dtot, dvt, col[maxn]; // n, m是给出矩形的尺寸，tot是给出字符的个数，dtot是不同距离的个数，dvt是不同约数的个数.col[i]是第i个给出的字符。
int calc(int a, int b) { // 计算a ^ 0 + a ^ 1 + ... + a ^ b
	if (b < 0) return 0;
	int c = a, d = 0, e = 1;
	for (; b; b >>= 1, c = 1ll * c * (a + 1ll) % mo, a = 1ll * a * a % mo)
		if (b & 1) {
			d = (1ll * d * a % mo + c) % mo;
			e = 1ll * e * a % mo;
		}
	return d + 1;
}
int power(int a, int b) { // a ^ b
	int c = 1;
	for (; b; b >>= 1, a = 1ll * a * a % mo)
		if (b & 1) c = 1ll * c * a % mo;
	return c;
}
void add(int &a, int b) {
	a += b; a %= mo;
}
map<int, int> M;
class CharacterBoard {
	public:
		int countGenerators(vector <string> frag, int W, int i0, int j0) {
			n = frag.size(); m = frag[0].size();
			tot = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					pos[++tot] = 1ll * (i0 + i) * W + (j0 + j);
					col[tot] = frag[i][j] - 'a';
				}
			dtot = 0;
			for (int i = 1; i <= tot; ++i)
				for (int j = i + 1; j <= tot; ++j)
					dis[++dtot] = pos[j] - pos[i];
			sort(dis + 1, dis + dtot + 1);
			dtot = unique(dis + 1, dis + dtot + 1) - dis - 1; // get所有出现过的dis
			dvt = 0;
			for (int i = 1; i <= dtot; ++i) {
				for (int j = 1; 1ll * j * j <= dis[i]; ++j)
					if (dis[i] % j == 0)
						div[++dvt] = j, div[++dvt] = dis[i] / j;
			}
			sort(div + 1, div + dvt + 1);
			dvt = unique(div + 1, div + dvt + 1) - div - 1; // get所有出现过dis的约数
			int ans = calc(26, W - tot); // 计算普通数字对答案的贡献
			for (int i = 1; i <= dvt; ++i) {
				int L = div[i], cnt = L, now = 1; // L是当前generator的长度，cnt是目前不确定的字符的个数，now记录合法性
				if (L > W) break;
				if (L >= tot) add(ans, mo - power(26, L - tot)); // 扣除当做普通数字时的贡献
				M.clear();
				for (int j = 1; j <= tot; ++j) {
					if (M.count(pos[j] % L)) {
						if (M[pos[j] % L] != col[j]) { // 不合法
							now = 0; break;
						}
					} else {
						M[pos[j] % L] = col[j];
						--cnt; // 新确定了一个位置
					}
				}
				if (now) add(ans, power(26, cnt));
			}
			return ans;
		}
};
