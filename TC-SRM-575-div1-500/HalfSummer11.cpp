#line 2 "TheSwapsDivOne.cpp"
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
typedef long long ll;
using namespace std;
double g0, g1, f0, f1, p, q; // f0表示经过若干次swap后，一个数在其原位的概率，f1表示它在其它任意一个位置的概率。q是一次swap后留在原位的概率，p是到任意一个其它位置的概率
double a[maxn]; // a[i]表示第i个位置上的数最后被选中的概率
string s;
int n;
class TheSwapsDivOne {
	public:
		double find(vector <string> seq, int k) {
			s = "";
			for (int i = 0; i < seq.size(); ++i)
				s = s + seq[i];
			n = s.size();
			p = 2.0 / (n * (n - 1)); // 跑到别的位置上，概率为1 / C(n, 2)
			q = (double)(n - 2) / n; // 1 - (n - 1) / C(n, 2)
			f0 = 1; f1 = 0;
			while (k--) {
				g0 = f0; g1 = f1;
				f0 = g0 * q + g1 * (n - 1) * p; // 或者上一次原地不动(g0), 或者从别的位置转移来，别的n - 1个位置等价，贡献相同。
				f1 = g1 * q + (g1 * (n - 2) + g0) * p; // 原地不动(g1) / 别的(n - 2)个等价的位置(g1) + 选中位置(g0) 转移来
			}
			double ans = 0, sum = 0;
			for (int i = 0; i < n; ++i) {
				a[i] = 1.0 * (i + 1) * (n - i) / (n * (n + 1) / 2.0); // 包含它的子串个数 / 总子串个数
				sum += a[i];
			}
			for (int i = 0; i < n; ++i) 
				ans += (f0 * a[i] + f1 * (sum - a[i])) * (s[i] - '0'); // 有f0的概率待在原位，贡献就是a[i], 否则，到其它位置的概率相同，均为f1, 贡献之和为sum - a[i]
			return ans;
		}
};
