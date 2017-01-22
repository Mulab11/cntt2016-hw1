#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int N = 2521;

class TheSwapsDivOne
{
public :
	int a[N], n;
	double f[2][2];
	double find(vector<string> sequence, int K) {
		rep (i, 0, sequence.size() - 1) {
			rep (j, 0, sequence[i].size() - 1) {
				a[n++] = sequence[i][j] - '0';
			}
		}
		LL tot = (LL) n * (n - 1) >> 1;
		double p1 = 1.0 * (n - 1) / tot, p2 = 1.0 - p1;
		double p3 = 1.0 / tot, p4 = 1.0 - p3;
		int t = 0;
		f[t][0] = 1.0;
		rep (i, 1, K) { 
			f[t ^ 1][0] = f[t][0] * p2 + f[t][1] * p3;
			f[t ^ 1][1] = f[t][0] * p1 + f[t][1] * p4;
			t ^= 1;
		}
		p1 = f[t][0];
		p2 = f[t][1];
		int sum = 0;
		rep (i, 0, n - 1) {
			sum += a[i];
		}
		double ans = 0.0;
		rep (i, 0, n - 1) { 
			double t = p1 * a[i] + p2 * (sum - a[i]) / (n - 1);
			ans += t * (i + 1) * (n - i);
		}
		return ans / (LL) (n * (n + 1) >> 1);
	}
};
