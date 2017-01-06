#include <algorithm>
using namespace std;
class TheTree
{
public:
	int maximumDiameter(vector<int> cnt)
	{
		int n = cnt.size();
		cnt.push_back(0);
		int ans = 0;
		for(int i = 0, j = 0; i <= n; i++) //把两条链都延伸到深度i 
		{
			ans = max(ans, (i - j) * 2 + (n - i)); //更新答案 
			if(cnt[i] == 1) //下移根节点 
				j = i + 1;
		}
		return ans;
	}
};