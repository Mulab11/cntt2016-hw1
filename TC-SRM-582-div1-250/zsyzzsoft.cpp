#include <algorithm>
using namespace std;
class SpaceWarDiv1
{
public:
	long long minimalFatigue(vector<int> girl, vector<int> strength, vector<long long> count)
	{
		int n = girl.size(), m = strength.size();
		vector<pair<int, long long> > enemy;
		for(int i = 0; i < m; i++)
			enemy.push_back(make_pair(strength[i], count[i]));
		sort(enemy.begin(), enemy.end(), [] (pair<int, long long> a, pair<int, long long> b) {return a > b; });
		sort(girl.begin(), girl.end(), [] (int a, int b) {return a > b; });
		long long ans = 0, sum = 0;
		for(int i = 0, j = 0; i < m; i++) //从大到小考虑每个前缀的敌人 
		{
			sum += enemy[i].second;
			while(j < n && girl[j] >= enemy[i].first) //求出可以使用的女孩数 
				j++;
			if(!j)
				return -1;
			ans = max(ans, (sum + j - 1) / j); //将其平均分配 
		}
		return ans;
	}
};