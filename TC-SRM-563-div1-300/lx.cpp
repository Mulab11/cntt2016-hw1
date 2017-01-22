#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)

using namespace std;
typedef long long LL;

class FoxAndHandle
{
public : 
	string lexSmallestName(string S)
	{
		static int need[26];
		memset(need, 0, sizeof(need));

		int len = S.length();

		rep (i, 0, len - 1)
			need[S[i] - 'a']++;
		rep (i, 0, 25)
			need[i] >>= 1;

		string ans = "";

		int cur = 0;
		int now = len >> 1;

		while (now > 0)
		{
			int best = len;
			rep (i, cur, len - 1) 
			{
				int x = S[i] - 'a';
				if (!need[x] || (best < len && x >= S[best] - 'a'))
					continue ;

				static int num[26];
				memset(num, 0, sizeof(num));

				rep (j, i, len - 1)
					++num[S[j] - 'a'];

				int j = 0;
				while (j < 26 && num[j] >= need[j])
					++j;

				if (j == 26)
					best = i;
			}
			cur = best + 1;
			ans += S[best];
			need[S[best] - 'a']--;
			now--;
		}
		return ans;
	}
};
