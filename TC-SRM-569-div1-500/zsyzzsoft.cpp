#include <algorithm>
using namespace std;
class TheJediTest
{
public:
	int minimumSupervisors(vector<int> a, int k)
	{
		int n = a.size(), ans = 0;
		for(int i = 0; i < 1 << n; i++) //枚举在那些层上减少答案 
		{
			bool flag = true;
			int cnt = 0;
			int b[20];
			for(int j = 0; j < n; j++)
				b[j] = a[j];
			for(int j = 0; j < n && flag; j++)
			{
				cnt -= (b[j] + k - 1) / k - (a[j] + k - 1) / k;
				if((i >> j) & 1)
				{
					if(!b[j])
						flag = false;
					int t = b[j] - (b[j] - 1) / k * k;
					if(j + 1 == n || t > a[j])
						flag = false;
					else
						b[j + 1] += t; //往后放 
					cnt++;
				}
				else if(j + 1 < n)
					b[j + 1] -= min(b[j + 1], (b[j] + k - 1) / k * k - b[j]); //尽量把当前层填满 
			}
			if(flag)
				ans = max(ans, cnt);
		}
		ans = -ans;
		for(int j = 0; j < n; j++)
			ans += (a[j] + k - 1) / k;
		return ans;
	}
};