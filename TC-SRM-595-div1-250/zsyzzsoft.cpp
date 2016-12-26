#include <algorithm>
#include <memory.h>
using namespace std;
int lst[2505];
bool flag[2505];
class LittleElephantAndIntervalsDiv1
{
public:
	long long getNumber(int m, vector<int> l, vector<int> r)
	{
		int n = l.size();
		for(int i = 1; i <= n; i++) 
		{
			for(int j = l[i - 1]; j <= r[i - 1]; j++)
				lst[j] = i;
		}
		memset(flag, 0, sizeof(flag));
		for(int i = 1; i <= m; i++)
			flag[lst[i]] = true;
		long long ans = 1;
		for(int i = 1; i <= n; i++)
		{
			if(flag[i])
				ans *= 2;
		}
		return ans;
	}
};