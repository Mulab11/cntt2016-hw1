#line 2 "WolfInZooDivOne.cpp"
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
#define mo 1000000007
#define maxn 310
typedef long long ll;
using namespace std;
int n, m; // n是路的个数，m是限制个数
pii con[maxn]; // con[]存储限制
string s; 
int len;
int mx[maxn][maxn]; // mx[l][r]表示左端点在[l, r]之间的限制的右端点的最大值
int f[maxn][maxn]; // f[i][j]表示已经填完前i条路，上一个有狼的是第j条路，的方案数
int read(int &pos) { // 从s的pos开始读一个数
	while (pos < len && (s[pos] < '0' || s[pos] > '9')) ++pos;
	int x = 0;
	while (pos < len && s[pos] >= '0' && s[pos] <= '9')
		x = x * 10 + s[pos] - '0', ++pos;
	return x;
}
void add(int &a, int b) {
	a += b; a %= mo;
}
class WolfInZooDivOne {
	public:
		int count(int N, vector <string> L, vector <string> R) {
			n = N;
			s = ""; m = 0;
			for (int i = 0; i < L.size(); ++i) s = s + L[i];
			len = s.length();
			int pos = 0;
			while (pos < len) con[++m].fr = 1 + read(pos);
			s = ""; m = 0;
			for (int i = 0; i < R.size(); ++i) s = s + R[i];
			len = s.length();
			pos = 0;
			while (pos < len) con[++m].sc = 1 + read(pos);
			sort(con + 1, con + m + 1); // 以上：读入限制并按左端点排序
			for (int i = 1, j = 1; i <= n; ++i) { // 计算mx[][]
				mx[i][i] = 0;
				while (j <= m && con[j].fr == i) {
					mx[i][i] = max(mx[i][i], con[j].sc);
					++j;
				}
				for (int k = 1; k < i; ++k)
					mx[k][i] = max(mx[k][i - 1], mx[i][i]);
			}
			cl(f);
			f[0][0] = 1;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					if (f[i][j]) {
						add(f[i + 1][j], f[i][j]); // i + 1的位置什么都不放
						add(f[max(i + 1, mx[1][j])][i + 1], f[i][j]); // i + 1的位置放一只狼，对于左端点在[1, j]的限制，它们已经包含了两只狼，所以直到mx[1][j]都不能再放狼了
					}
			int ans = 0;
			for (int i = 0; i <= n; ++i)
				add(ans, f[n][i]);
			return ans;
		}
};
