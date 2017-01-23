#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

class ColorfulChocolates
{
	public:

	int n, ans;
	string ch;
	int maximumSpread(string chocolates, int maxSwaps)
	{
		ch = chocolates;
		n = chocolates.size();
		ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
				for(char c = 'A'; c <= 'Z'; c++)
				{
					vector<int> v(0);
					for(int k = i; k <= j; k++)
						if(ch[k] == c)
							v.push_back(k);
					if(v.empty()) continue;
					int num = v.size(), mid = v[num / 2], cnt = 0;
					for(int k = 0; k < num; k++)
						cnt += abs(mid + k - num / 2 - v[k]);
					if(cnt <= maxSwaps)
						ans = max(ans, num);
				}

		return ans;
	}
};

