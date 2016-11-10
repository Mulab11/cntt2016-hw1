#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

int LCP(const string& s, const string& t)
{
	for(int i = 0; i != (int) min(s.size(), t.size()); ++i)
		if(s[i] != t[i]) return i;
	return min(s.size(), t.size());
}

class UndoHistory
{
public:
	int minPresses(vector<string> inp)
	{
		int ans = inp[0].size() + 1;
		for(int i = 1; i != (int) inp.size(); ++i)
		{
			int mn = 1000000;
			if(LCP(inp[i], inp[i - 1]) == (int) inp[i - 1].size())
				mn = inp[i].size() - inp[i - 1].size();
			for(int j = 0; j != i; ++j)
				mn = min(mn, 2 + (int) inp[i].size() - LCP(inp[i], inp[j]));
			ans += mn + 1;
		}
		return ans;
	}
}	user;
