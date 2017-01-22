#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

int cnt[35][2];

class TheDevice
{
public:
	int minimumAdditional(vector<string> plates)
	{
		int n = plates.size();
		int m = plates[0].size();
		rep (i, 0, n - 1)
		{
			rep (j, 0, m - 1)
				++cnt[j][plates[i][j] - '0'];
		}
		int ans = 0;
		rep (i, 0, m - 1)
		{
			int tmp = 0;
			tmp += 1 - min(cnt[i][0], 1);
			tmp += 2 - min(cnt[i][1], 2);
			upmax(ans, tmp);
		}
		return ans;
	}
};

int main()
{
#ifdef LX_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	return 0;
}
