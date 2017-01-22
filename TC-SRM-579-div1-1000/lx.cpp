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

class RockPaperScissors {
private :
	double P[50][51][51][51];
public :
	double bestScore(vector<int> PR, vector<int> PP, vector<int> PS) {
		int n = PR.size();
		rep (i, 0, n - 1) {
			P[i][0][0][0] = 1.0;
			rep (t, 1, n) {
				down (m, t, 0) {
					rep (r, 0, m) rep (s, 0, m - r) {
						int p = m - s - r;
						double q = m / (double) t;
						double qr = PR[t - 1] / 300.0;
						double qs = PS[t - 1] / 300.0;
						double qp = PP[t - 1] / 300.0;
						double sum = 0;
						if (r > 0)  sum += qr * P[i][r - 1][s][p];
						if (s > 0)  sum += qs * P[i][r][s - 1][p];
						if (p > 0)  sum += qp * P[i][r][s][p - 1];
						if (i == t - 1) {
							P[i][r][s][p] = (1-q) * P[i][r][s][p];
						} else {
							P[i][r][s][p] = q * sum + (1-q) * P[i][r][s][p];
						}
					}
				}
			}
		}
		double ans = 0;
		down (m, n - 1, 0) {
			rep (r, 0, m) rep (s, 0, m - r) {
				int p = m - r - s;
				double pr = 0, ps = 0, pp = 0;
				rep (i, 0, n - 1) {
					double c = P[i][r][s][p] / (n - m);
					pr += c * PR[i] / 300.0;
					ps += c * PS[i] / 300.0;
					pp += c * PP[i] / 300.0;
				}
				ans += max(max(3*pr + pp, 3*pp + ps), 3*ps + pr);
			}
		}
		return ans;
	}
};
