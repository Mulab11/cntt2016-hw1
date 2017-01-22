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

class BinPacking
{
private:
	bool used[55];
public:
	int minBins(vector<int> item)
	{
		memset(used, false, item.size() * sizeof(bool));
		sort(item.begin(), item.end());
		int ans = 0;
		int ptr = 0, i;//greedy, two pointers
		for(i = item.size() - 1; i >= 0; i--)
		{
			if(used[i])
				continue;
			if(item[i] == 100)
				break;
			ans++;
			used[i] = true;
			while(ptr + 1 < i && item[ptr + 1] + item[i] <= 300)
				ptr++;
			while(ptr >= 0 && used[ptr])
				ptr--;
			if(ptr >= 0 && item[i] + item[ptr] <= 300)
				used[ptr] = true;
		}
		int cnt = 0;
		for(; i >= 0; i--)
			if(!used[i])
				cnt++;
		ans += (cnt + 2) / 3;
		return ans;
	}
};

