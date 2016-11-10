#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

class TheTree
{
public:
	int maximumDiameter(vector<int> inp)
	{
		int ans = 0;
		for(int i = 0; i != (int) inp.size(); ++i)
		{
			int cur = inp.size() - i;
			for(int j = i; j != (int) inp.size() && inp[j] != 1; ++j)
				++cur;
			if(cur > ans) ans = cur;
		}
		return ans;
	}
}	user;
