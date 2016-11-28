#include <algorithm>
using namespace std;
class TomekPhone
{
public:
	int n, sum[50];
	int minKeystrokes(vector<int> w, vector<int> a)
	{
		n = w.size();
		sort(w.begin(), w.end());
		for(int i = 0; i < a.size(); i++)
		{
			for(int j = 0; j < a[i]; j++)
				sum[j]++; //统计每个权重的位置数 
		}
		int ans = 0;
		for(int i = 0; i < 50 && n; i++) //按位置的权重从小到大贪心放置 
		{
			for(int j = 0; j < sum[i] && n; j++)
				ans += w[--n] * (i + 1);
		}
		return n ? -1 : ans;
	}
};
