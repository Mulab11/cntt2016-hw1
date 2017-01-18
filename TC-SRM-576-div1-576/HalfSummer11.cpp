#line 2 "TheExperiment.cpp"
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
#define maxn 310
#define mo 1000000009
typedef long long ll;
using namespace std;
/*
	题意相当于要在n个数中取出m个互不重叠的子串，每个子串的和都在[A, B]之间，且每个子串长度不超过L，一段连续的子串中，至少一个的长度达到L（对应不被其他海绵遮住的海绵）
*/
int n, m, sum[maxn]; // n是水滴个数，m是海绵个数。sum[i]是每分钟水滴数的前缀和
int f[maxn][maxn][2]; // f[i][j][0]表示前i个水滴处共放了j块海绵，目前连续的一段海绵中，还没有长度为L的。f[i][j][1]表示目前连续的一段海绵中已有长度为L的。
string s;
void add(int &a, int b) {
	a += b; a %= mo;
}
class TheExperiment {
	public:
		int countPlacements(vector <string> str, int M, int L, int A, int B) {
			cl(sum); cl(f); 
			s = "";
			for (int i = 0; i < str.size(); ++i) s = s + str[i];
			n = s.size(); m = M;
			for (int i = 0; i < n; ++i) sum[i + 1] = s[i] - '0';
			for (int i = 1; i <= n; ++i) sum[i] += sum[i - 1]; // 水滴前缀和
			for (int lst = 0; lst <= n; ++lst) // 枚举第一个海绵的开始位置lst + 1
				f[lst][0][0] = 1;
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j <= m; ++j) 
					for (int k = 0; k <= 1; ++k) {
						for (int p = 1; p <= L && p + L <= n; ++p) // 枚举当前海绵露出的长度
							if (sum[i + p] - sum[i] >= A && sum[i + p] - sum[i] <= B) 
								add(f[i + p][j + 1][k | (p == L)], f[i][j][k]);
						if (k == 1) { // 这一段海绵就此结束。需要其中至少有一个长度为L的才是合法的，故k要=1
							for (int lst = i + 1; lst <= n; ++lst) // 枚举下一个海绵的开始位置lst + 1
								add(f[lst][j][0], f[i][j][k]);
						}
					}
			int ans = 0;
			for (int i = 0; i <= n; ++i) // 枚举最后一个海绵的结束位置
				add(ans, f[i][m][1]);
			return ans;
		}
};
