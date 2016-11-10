#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int sum[60];
int vis[60];
bool rea[60];

class SurveillanceSystem
{
public:
	string getContainerInfo(string str, vector<int> res, int len)
	{
		int n = str.size();
		for(int i = n; i >= 1; --i)
			sum[i] = sum[i + 1] + (str[i - 1] == 'X');
		memset(vis + 1, 0, str.size());
		string ret(n, '?');
		sort(res.begin(), res.end());
		for(int _ = 0; _ != (int) res.size(); )
		{
			memset(vis + 1, 0, n << 2);
			int cnt = 0;
			for(int k = 1; k + len - 1 <= n; ++k)
				if(sum[k] - sum[k + len] == res[_])
				{
					for(int j = k; j != k + len; ++j) ++vis[j], rea[j] = 1;
					++cnt;
				}
			int same = 0, ri = res[_];
			for(; _ != (int) res.size() && res[_] == ri; ++_)
				++same;
			for(int i = 1; i <= n; ++i)
				if(vis[i] > cnt - same) ret[i - 1] = '+';
		}
		for(int i = 1; i <= n; ++i) if(!rea[i]) ret[i - 1] = '-';
		return ret;
	}
}	user;
