#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class TeamContest
{
public : 
	int worstRank(vector<int> level)
	{
		int w = min(min(level[0], level[1]), level[2]) + max(max(level[0], level[1]), level[2]);
		vector<int> my(level.begin() + 3, level.end());
		sort(my.begin(), my.end(), greater<int>());
		int cnt = 0;
		int cur = 0, last = my.size() - 1;
		while (1)
		{
			while (cur < last && my[cur] + my[last] <= w)
			{
				my.pop_back();
				last--;
			}
			if (cur < last - 1)
			{
				my.pop_back();
				my.pop_back();
				last -= 2;
				++cur;
				++cnt;
			}
			else
				break ;
		}
		return cnt + 1;
	}
};
