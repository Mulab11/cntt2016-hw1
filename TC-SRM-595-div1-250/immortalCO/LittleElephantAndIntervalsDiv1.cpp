#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int arr[1010], cnt[60];
class LittleElephantAndIntervalsDiv1
{
public:
	ll getNumber(int n, vector<int> l, vector<int> r)
	{
		memset(arr + 1, -1, n << 2);
		int diff = 0;
		for(int i = 0; i != (int) l.size(); ++i)
		{
			cnt[i] = r[i] - l[i] + 1;
			++diff;
			for(int p = l[i]; p <= r[i]; ++p)
			{
				if(arr[p] != -1 && !--cnt[arr[p]])
					--diff;
				arr[p] = i;
			}
		}
		return 1ll << diff;
	}
}   user;
