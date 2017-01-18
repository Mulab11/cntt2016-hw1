#line 2 "TheBrickTowerHardDivOne.cpp"
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
#define maxn 150
#define maxs 5010
#define mo 1234567891ll
#define hash hashh
typedef long long ll;
using namespace std;
map <int, int> F; // F[sta]是四位四进制数sta对应的编号
int a[maxn], n; // n表示空格个数，a存dfs时空格中的颜色
int cnt4, cnt8, sta4[maxs], mx4[maxs], sta8[maxs], mx8[maxs]; // cnt4是给4个格子填色，用最小表示法表示填色情况，得到的本质不同的填色方案数，sta4存这些方案（压成四位四进制数），mx4表示对应方案用到颜色的种数
int tot;
void dfs(int num, int mx) { // 目前要填第num个格子，之前用过mx种颜色
	if (num == n + 1) { // 得到一个方案
		if (n == 4) ++cnt4; else ++cnt8;
		int sta = 0, digit = log2(n);
		for (int i = n; i >= 1; --i)
			sta = (sta << digit) + a[i] - 1; // 压成四位四进制数/八位八进制数
		if (n == 4) {
			F[sta] = cnt4; 
			sta4[cnt4] = sta; 
			mx4[cnt4] = mx;
		} else {
			sta8[cnt8] = sta;
			mx8[cnt8] = mx;
		}
		return;
	} else {
		for (int i = 1; i <= mx; ++i) {
			a[num] = i; dfs(num + 1, mx); // 使用某种已用颜色
		}
		a[num] = mx + 1; dfs(num + 1, mx + 1); // 使用新颜色
	}
}
void add(ll &a, ll b) {
	a += b; a %= mo;
}
struct mat {
	ll x[maxn][maxn];
}I, A;
mat operator + (const mat &a, const mat &b) { // 矩阵加法
	mat c; cl(c.x);
	for (int i = 1; i <= tot; ++i)
		for (int j = 1; j <= tot; ++j)
			c.x[i][j] = (a.x[i][j] + b.x[i][j]) % mo;
	return c;
}
mat operator * (const mat &a, const mat &b) { // 矩阵乘法
	mat c; cl(c.x);
	for (int k = 1; k <= tot; ++k)
		for (int i = 1; i <= tot; ++i)
			for (int j = 1; j <= tot; ++j)
				add(c.x[i][j], 1ll * a.x[i][k] * b.x[k][j] % mo);
	return c;
}
mat calc(mat a, ll b) { // calc(a, b) = a ^ 0 + a ^ 1 + ... + a ^ b
	mat c = a, d = I, e = I;
	for (; b; b >>= 1ll, c = c * a + c, a = a * a)
		if (b & 1ll)
			e = c * d + e, d = d * a;
	return e;
}
ll ori[maxn]; // ori[i]表示高度为1，状态为i(sta + k)的塔的个数
int code[maxn], hash[maxn];
int number(int sta, int k) { // 返回顶层状态为sta，已有k对同色相邻，这样的情况在矩阵中的对应标号
	return k * cnt4 + sta;
}
ll select(int n, int m) { // 从n个东西中依次选出m个的方案数
	if (n < m) return 0;
	ll ret = 1;
	while (m--) {
		ret = 1ll * ret * n % mo;
		--n;
	}
	return ret;
}
class TheBrickTowerHardDivOne {
	public:
		int find(int C, int K, long long H) {
			cnt4 = cnt8 = 0; F.clear();
			n = 4; dfs(1, 0); 
			n = 8; dfs(1, 0);
			tot = cnt4 * (K + 1);
			cl(I.x); for (int i = 1; i <= tot; ++i) I.x[i][i] = 1;
			cl(ori);
			for (int i = 1; i <= cnt4; ++i) { // 枚举第一层的情况
				int tmp = sta4[i], pr = 0; // pr表示该层相邻同色对数
				for (int j = 1; j <= 4; ++j) {
					code[j] = (tmp & 3); 
					tmp >>= 2;
				}
				if (code[1] == code[2]) ++pr;
				if (code[3] == code[4]) ++pr;
				if (code[1] == code[3]) ++pr;
				if (code[2] == code[4]) ++pr;
				if (pr <= K) 
					add(ori[number(i, pr)], select(C, mx4[i])); // 填色情况为i，有pr对同色相邻，高度为1的塔的个数，等于从所有颜色中依次选出该填色方案所用到颜色种数的方案数
			}
			cl(A.x);
			for (int i = 1; i <= cnt8; ++i) { // 枚举相邻两层8个格子的填色情况
				int pr = 0, tmp = sta8[i]; // pr记录加上上面一层后，新增的相邻同色对数
				for (int j = 1; j <= 8; ++j) {
					code[j] = (tmp & 7);
					tmp >>= 3;
				}
				if (code[5] == code[6]) ++pr;
				if (code[7] == code[8]) ++pr;
				if (code[5] == code[7]) ++pr;
				if (code[6] == code[8]) ++pr;
				if (code[1] == code[5]) ++pr;
				if (code[2] == code[6]) ++pr;
				if (code[3] == code[7]) ++pr;
				if (code[4] == code[8]) ++pr;
				int nsta = 0;
				for (int j = 4; j >= 1; --j)
					nsta = (nsta << 2) | code[j]; // nsta是下面一层的填色状态
				int d = F[nsta]; // d为下面一层的状态编号
				nsta = 0; tmp = 0;
				for (int j = 0; j < 8; ++j) hash[j] = -1;
				for (int j = 5; j <= 8; ++j)
					if (hash[code[j]] == -1) hash[code[j]] = tmp++;
				for (int j = 8; j >= 5; --j)
					nsta = (nsta << 2) | hash[code[j]];
				int u = F[nsta]; // u为上面一层的状态标号
				ll ways = select(C - mx4[d], mx8[i] - mx4[d]); // 在下面一层颜色确定的基础上，上面一层填成u的方案数，等于从下面一层未用过的C - mx4[d]种颜色中，选出上面一层新增的mx8[i] - mx4[d]种颜色的方案数。
				for (int k = 0; k + pr <= K; ++k) // 枚举下面这层及以下已有的相邻同色对数k
					add(A.x[number(d, k)][number(u, k + pr)], ways); // 造转移矩阵
			}
			A = calc(A, H - 1ll); // 在ori的基础上，再造 0 - H-1 层
			ll ret = 0;
			for (int i = 1; i <= tot; ++i) 
				for (int j = 1; j <= tot; ++j)
					add(ret, 1ll * ori[j] * A.x[j][i] % mo); // 将向量ori与矩阵相乘
			return ret;
		}
};

