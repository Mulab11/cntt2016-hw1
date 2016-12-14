#include <algorithm>
using namespace std;
class EelAndRabbit
{
public:
	int getmax(vector<int> l, vector<int> t)
	{
		int n = l.size();
		vector<int> pt;
		for(int i = 0; i < n; i++) //一定可以只考虑每个区间的左右端点 
		{
			pt.push_back(t[i]);
			pt.push_back(t[i] + l[i]);
		}
		int ans = 0;
		for(int i = 0; i < n * 2; i++)
		{
			for(int j = 0; j < n * 2; j++) //枚举两次的时间点 
			{
				int cnt = 0;
				for(int k = 0; k < n; k++) //计算答案 
					cnt += (pt[i] >= t[k] && pt[i] <= t[k] + l[k]) || (pt[j] >= t[k] && pt[j] <= t[k] + l[k]);
				ans = max(ans, cnt);
			}
		}
		return ans;
	}
};