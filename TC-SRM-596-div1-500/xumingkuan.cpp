#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class BitwiseAnd
{
private:
	long long lowbit(long long x)
	{
		return x & (-x);
	}
public:
	vector<long long> lexSmallest(vector<long long> subset, int N)
	{
		if(N > 11)//N*(N-1)/2 should <= 60
			return vector<long long>();
		int m = subset.size();
		long long mask = 0, remain = (1ll << 60) - 1;
		for(int i = 0; i < m; i++)
		{
			remain = ~(~remain | subset[i]);
			for(int j = i + 1; j < m; j++)
			{
				long long now = subset[i] & subset[j];
				if(!now || (bool)(now & mask))
					return vector<long long>();
				mask |= now;
			}
		}
		while(subset.size() < N)
		{
			long long now = 0;
			for(int j = 0; j < subset.size(); j++)
			{
				if((subset[j] & mask) == subset[j])
					return vector<long long>();
				now |= lowbit(~(~subset[j] | mask));//greedy
			}
			mask |= now;
			for(int j = subset.size() + 1; j < N; j++)
			{
				if(!remain)
					return vector<long long>();
				now |= lowbit(remain);
				remain ^= lowbit(remain);
			}
			subset.push_back(now);
		}
		vector<long long> ans;
		merge(subset.begin(), subset.begin() + m, subset.begin() + m, subset.end(), back_inserter(ans));
		return ans;
	}
};

