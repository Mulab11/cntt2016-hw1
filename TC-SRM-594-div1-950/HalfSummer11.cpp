#line 2 "FoxAndAvatar.cpp"
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
int ans, w;
bool one(int n, int x) {
	if (n <= w && (x == 1 || x == n)) return 1;
	if (w == 1 && (x == 1 || x == n)) return 1;
	if (x == w && n < 2 * w) return 1;
	if (x == n && n % w == 1) return 1;
	return 0;
}
int get(int n, int x) {
	return (n / w) * x + min(x, n % w);
}
void dfs(int step, int n, int x) {
	if (n == 1) {
		ans = min(ans, step); return;
	}
	if (one(n, x)) {
		ans = min(ans, step + 1); 
		return;
	}
	if (step + 2 >= ans) return;
	int c = x % w, r = (x - 1) / w;
	if (c == 0) c = w;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= w; ++j)
			dfs(step + 1, n - i * j, x - i * j);
	dfs(step + 1, min(n, (r + 1) * w), x);
	for (int i = 1; i <= r + 1; ++i)
		for (int j = 1; j <= c - 1; ++j)
			dfs(step + 1, n - i * j - get(n - (r + 1) * w, j), x - i * j);
	for (int i = 0; i <= r; ++i)
		for (int j = 1; j <= w - c; ++j)
			dfs(step + 1, n - i * j - (get(n - r * w, c + j) - get(n - r * w, c)), x - i * j);
}
class FoxAndAvatar {
	public:
		int minimalSteps(int n, int width, int x) {
			w = width; ans = 4;
			dfs(0, n, x);
			return ans;
		}
};
