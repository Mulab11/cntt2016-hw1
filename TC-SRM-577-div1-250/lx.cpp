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

class EllysRoomAssignmentsDiv1 {
public :
	double getAverage(vector<string>rates) {
		stringstream ss;
		rep (i, 0, rates.size() - 1)  ss << rates[i];
		vector<int> A;
		int my, x;
		while (ss >> x)  A.pb(x);
		my = A[0];
		sort(A.begin(), A.end(), greater<int>());
		int num = (A.size() + 19) / 20;
		int per = (A.size() + num - 1) / num;
		int cur = 0;
		while (cur < A.size() && my <= A[cur])  cur += num;
		cur -= num;
		if (cur + num > A.size())
			A.erase(A.begin() + cur, A.end());
		else
			A.erase(A.begin() + cur, A.begin() + cur + num);
		double ans = 0.0;
		int rest = A.size() % num;
		if (!rest) {
			rep (i, 0, A.size() - 1)  ans += A[i];
			ans = (ans / num + my) / per;
		} else {
			double p = (double) rest / num, q = 1.0 - p;
			double sum = 0.0, sum2 = 0.0;
			rep (i, 0, A.size() - rest - 1)  sum += A[i];
			rep (i, A.size() - rest, A.size() - 1)  sum2 += A[i];
			ans = p * (sum / num + sum2 / rest + my) / per + q * (sum / num + my) / (per - 1);
		}
		return ans;
	}
};
