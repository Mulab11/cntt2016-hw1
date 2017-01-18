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

class LittleElephantAndBalls
{
private:
	int cnt[256];//count R, G, B
public:
	int getNumber(string S)
	{
		cnt['R'] = cnt['G'] = cnt['B'] = 0;
		int ans = 0, now = 0;
		for(int i = 0; i < S.size(); i++)//greedy
		{
			ans += now;
			if(++cnt[S[i]] <= 2)
				now++;
		}
		return ans;
	}
};

