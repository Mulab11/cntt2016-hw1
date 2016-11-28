#include <algorithm>
using namespace std;
class NewArenaPassword
{
public:
	int minChange(string s, int k)
	{
		int n = s.length(), ans = 0;
		for(int i = 0; i < n - k; i++)
		{
			int cnt[26] = {0}, sum = 0, rep = 0;
			for(int j = i; j < n; j += n - k) //这些字符必须相同 
				rep = max(rep, ++cnt[(int)s[j] - 'a']), sum++;
			ans += sum - rep;
		}
		return ans;
	}
};
