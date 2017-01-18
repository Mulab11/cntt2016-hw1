#line 2 "FlippingBitsDiv1.cpp"
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
typedef long long ll;
using namespace std;
int f[maxn], val[maxn], len[maxn];
int a[maxn];
int cnt[maxn][2];
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class FlippingBitsDiv1 {
	public:
		int getmin(vector <string> Ss, int m) {
			string S = "";
			for (int i = 0; i < Ss.size(); ++i) S = S + Ss[i];
			int n = S.length();
			if (2 * m > n) {
				int ans = oo;
				for (int s = 0; s < 2; ++s) {
					if (s)
						for (int j = 0; j < m; ++j) S[j] = '0' + '1' - S[j];
					int now = s;
					for (int i = 0; i < n - m; ++i) 
						if (S[i] != S[i + m]) ++now;
					gmin(ans, now);
				}
				return ans;
			}
			int k = (n + m - 1) / m, d = m;
			if (d <= 17) {
				int ans = oo;
				for (int s = 0; s < (1 << d); ++s) {
					for (int i = 1; i <= k; ++i) {
						len[i] = min(i * m, n) - (i - 1) * m;
						val[i] = 0;
						for (int j = (i - 1) * m; j < (i - 1) * m + len[i]; ++j) {
							int now = S[j] - '0', dest = bool(s & (1 << (j % d)));
							if (now != dest) ++val[i];
						}
					}
					memset(f, 0x3f, sizeof(f));
					f[0] = 0;
					for (int i = 0; i < k; ++i) {
						gmin(f[i + 1], f[i] + val[i + 1]);
						int sum = 0;
						for (int j = i + 1; j <= k; ++j) {
							sum += len[j] - val[j];
							gmin(f[j], f[i] + sum + 1 + (i != 0));
						}
					}
					gmin(ans, f[k]);
				}
				return ans;
			} else {
				int ans = oo;
				for (int s = 0; s < (1 << k); ++s) {
					for (int i = 0; i < n; ++i) a[i] = S[i] - '0';
					int now = 0;
					for (int i = 0; i < k; ++i)
						if (s & (1 << i)) {
							for (int j = 0; j < min((i + 1) * m, n); ++j)
								a[j] ^= 1;
							++now;
						}
					cl(cnt);
					for (int i = 0; i < n; ++i)
						++cnt[i % d][a[i]];
					for (int i = 0; i < d; ++i)
						now += min(cnt[i][0], cnt[i][1]);
					gmin(ans, now);
				}
				return ans;
			}
		}
};
