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
				int t = 0;
				if((i >> j) & 1)
				{
					if(!a[j])
						flag = false;
					t = b[j] - (a[j] - 1) / k * k;
					cnt++;
				}
				cnt -= (b[j] + k - 1) / k - (a[j] + k - 1) / k;
				if(!t)
					continue;
				if(t > a[j]) //剩下的人不足 
					flag = false;
				else
				{
					if(j) //往前放 
					{
						int p = min(t, (b[j - 1] + k - 1) / k * k - b[j - 1]);
						b[j] -= p;
						t -= p;
					}
					if(t && j == n - 1)
						flag = false;
					else //往后放 
						b[j + 1] += t;
					b[j] -= t;
				}
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
