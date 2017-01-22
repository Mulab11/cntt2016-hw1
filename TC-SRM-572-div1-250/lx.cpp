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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class NewArenaPassword
{
public : 
	int minChange(string str, int K)
	{
		static int cnt[26];
		int n = str.size(), ans = 0;
		K = n - K;
		rep (i, 0, min(K, n - K) - 1)
		{
			int t = 0;
			memset(cnt, 0, sizeof(cnt));
			for (int j = i; j < n; j += K)
			{
				cnt[str[j] - 'a']++;
				++t;
			}
			int mx = 0;
			rep (i, 0, 25)
				upmax(mx, cnt[i]);
			ans += t - mx;
		}
		return ans;
	}
};

