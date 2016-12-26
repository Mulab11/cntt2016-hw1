#include <algorithm>
using namespace std;
int a[55];
class BinPacking
{
public:
	int minBins(vector<int> item)
	{
		int n = item.size();
		for(int i = 0; i < n; i++)
			a[i] = item[i];
		sort(a, a + n); //将物品体积排序 
		int ans = n;
		for(int i = n - 1; i > 0; i--) //从大到小贪心 
		{
			int lpl = -1;
			for(int j = 0; j < i; j++)
			{
				if(a[j] + a[i] <= 300) 
					lpl = j;
			}
			if(lpl != -1) 
			{
				a[lpl] += a[i];
				ans--;
				sort(a, a + i);
			}
		}
		return ans;
	}
};