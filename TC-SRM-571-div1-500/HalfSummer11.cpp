#line 2 "MagicMolecule.cpp"
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
int n, ans, cnt, x[maxn * maxn], y[maxn * maxn];  // n是点数，ans是答案，cnt是补图中的边数，x[],y[]存储了补图中的边
vector<int> w;
bool del[maxn]; //  标记一个点是否被删除
void dfs(int m, int now, int tot) { // 考虑补图中的第m条边，目前未被删除的点有tot个，点权之和为now
	if (tot * 3 < n * 2) return; // 已经不满足题目条件
	if (m > cnt) { // 考虑完所有补图中的边。此时，未被删除的点在补图中一定是一个独立集
		ans = max(ans, now); // 更新答案
		return;
	}
	if (del[x[m]] || del[y[m]]) // 如果这条边的某一端已经被删除，那么不影响目前的情况
		dfs(m + 1, now, tot);
	else { // 否则，需要从两个点中删去一个
		del[x[m]] = 1; 
		dfs(m + 1, now - w[x[m]], tot - 1);
		del[x[m]] = 0;
		del[y[m]] = 1;
		dfs(m + 1, now - w[y[m]], tot - 1);
		del[y[m]] = 0;
	}
}
class MagicMolecule {
	public:
		int maxMagicPower(vector <int> W, vector <string> con) {
			n = W.size(); cnt = 0; cl(del); ans = -1; w = W;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < i; ++j)
					if (con[i][j] == 'N') // 记录补图中的边
						++cnt, x[cnt] = i, y[cnt] = j;
			int sum = 0;
			for (int i = 0; i < n; ++i) sum += w[i];
			dfs(1, sum, n);
			return ans;
		}
};
