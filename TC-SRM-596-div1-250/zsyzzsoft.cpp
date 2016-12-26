#include <algorithm>
using namespace std;
class IncrementAndDoubling
{
public:
	int getMin(vector<int> a)
	{
		int n = a.size(), ans = 0;
		while(true)
		{
			bool flag1 = false, flag2 = true;
			for(int j = 0; j < n; j++)
			{
				if(a[j])
					flag1 = true;
			}
			if(!flag1)
				return ans;
			for(int j = 0; j < n; j++)
			{
				if(a[j] % 2) 
					flag2 = false, ans++, a[j]--;
			}
			if(flag2)
			{
				for(int j = 0; j < n; j++)
					a[j] /= 2;
				ans++;
			}
		}
	}
};