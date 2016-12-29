#include <algorithm>
using namespace std;
class PiecewiseLinearFunction
{
public:
	int maximumSolutions(vector<int> y)
	{
		int n = y.size();
		for(int i = 1; i < n; i++)
		{
			if(y[i - 1] == y[i]) //无穷多组解 
				return -1;
		}
		vector<int> pt;
		for(int i = 0; i < n; i++)
			y[i] *= 2;
		for(int i = 0; i < n; i++) //枚举扫描线在每个点上以及每个点上方 
			pt.push_back(y[i]), pt.push_back(y[i] + 1);
		int ans = 0;
		for(int i = 0; i < pt.size(); i++)
		{
			int cnt = 0; //计算交点个数 
			for(int j = 1; j < n; j++)
				cnt += max(y[j - 1], y[j]) > pt[i] && min(y[j - 1], y[j]) < pt[i];
			for(int j = 0; j < n; j++)
				cnt += y[j] == pt[i];
			ans = max(ans, cnt);
		}
		return ans;
	}
};