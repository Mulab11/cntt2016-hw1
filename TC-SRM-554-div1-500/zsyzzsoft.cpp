#include <algorithm>
using namespace std;
class TheBrickTowerMediumDivOne
{
public:
	int n, ans[50];
	vector<int> find(vector<int> h)
	{
		n = h.size();
		for(int i = 0, j = 0, k = 50; i < n; ans[i++] = j)
		{
			for(j = 0; j < n && h[j] > k; j++); //放一个更小的数 
			if(j == n) //已经到达了最小值，剩下的数只能从小往大放 
			{
				j = 0;
				for(int p = 0; p < n; p++)
					j = h[p] < h[j] ? p : j;
			}
			else
				k = h[j];
			h[j] = 50;
		}
		vector<int> ret;
		for(int i = 0; i < n; i++)
			ret.push_back(ans[i]);
		return ret;
	}
};