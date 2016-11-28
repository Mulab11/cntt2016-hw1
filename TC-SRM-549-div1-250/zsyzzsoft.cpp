#include <algorithm>
using namespace std;
class PointyWizardHats
{
public:
	int n, m;
	int getNumHats(vector<int> ah, vector<int> ar, vector<int> bh, vector<int> br)
	{
		n = ah.size(), m = bh.size();
		bool used[100] = {0};
		int ans = 0;
		for(int i = 0; i < n; i++) //将上方帽子按半径排序，贪心匹配 
		{
			for(int j = n - 1; j > i; j--)
			{
				if(ar[j - 1] < ar[j])
					swap(ar[j - 1], ar[j]), swap(ah[j - 1], ah[j]);
			}
		}
		for(int i = 0; i < n; i++)
		{
			int match = -1;
			for(int j = 0; j < m; j++) //选择一个能放上去的且斜率最接近的下方帽子 
			{
				if(!used[j] && ar[i] < br[j] && ah[i] * br[j] > bh[j] * ar[i] && (match == -1 || bh[j] * br[match] > bh[match] * br[j]))
					match = j;
			}
			if(match >= 0)
				ans += used[match] = true;
		}
		return ans;
	}
};