#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int N = 2511;

class ShoutterDiv1 {
private :
	int a[N], b[N], n;
public :
	int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, 
			vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) {
		n = 0;
		rep (i, 0, s1000.size() - 1) rep (j, 0, s1000[i].size() - 1) {
			a[n] = ((((s1000[i][j] - '0') * 10 + s100[i][j] - '0') * 10 + s10[i][j] - '0') * 10 + s1[i][j] - '0');
			b[n] = ((((t1000[i][j] - '0') * 10 + t100[i][j] - '0') * 10 + t10[i][j] - '0') * 10 + t1[i][j] - '0');
			n++;
		}
		int start = b[0];
		rep (i, 0, n - 1) {
			rep (j, i + 1, n - 1) {
				if (a[j] < a[i] || (a[j] == a[i] && b[j] < b[i])) {
					swap(a[j], a[i]);
					swap(b[j], b[i]);
				}
			}
			upmin(start, b[i]);
		}
		int res = 0;
		rep (i, 0, n - 1) {
			int now = start, j = 0;
			while (j < n) {
				if (a[i] <= now) {
					upmax(now, b[i]);
				}
				int best = -1;
				while (j < n && a[j] <= now) {
					upmax(best, b[j]);
					++j;
				}
				if (best == -1)  return -1;
				if (j == n)  break ;
				now = best;
				res++;
			}
		}
		return res;
	}
};
