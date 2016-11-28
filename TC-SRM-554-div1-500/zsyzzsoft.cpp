#include <algorithm>
using namespace std;
class TheBrickTowerMediumDivOne
{
public:
	int n, h[50], a[50], ans[50];
	void Work()
	{
		bool used[50] = {0};
		bool cmp = false;
		for(int i = 0, j; i < n; i++)
		{
			for(j = 0; used[j] || a[i] != h[j]; j++);
			if(!cmp && j > ans[i]) //字典序不优 
				return;
			if(j < ans[i])
				cmp = true;
			used[ans[i] = j] = true;
		}
	}
	vector<int> find(vector<int> heights)
	{
		n = heights.size();
		if(n == 1)
		{
			vector<int> ret;
			ret.push_back(0);
			return ret;
		}
		for(int i = 0; i < n; i++)
			a[i] = h[i] = heights[i];
		for(int i = 0; i < n; i++)
			ans[i] = n;
		sort(a, a + n); //分4种情况 
		Work();
		swap(a[0], a[1]);
		Work();
		for(int i = 0; i < n / 2; i++)
			swap(a[i], a[n - i - 1]);
		Work();
		swap(a[n - 1], a[n - 2]);
		Work();
		vector<int> ret;
		for(int i = 0; i < n; i++)
			ret.push_back(ans[i]);
		return ret;
	}
};
