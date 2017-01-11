#include <algorithm>
using namespace std;
bool f[1000001];
class MayTheBestPetWin
{
public:
	int calc(vector<int> a, vector<int> b)
	{
		int n = a.size(), suma = 0, sumb = 0;
		for(int i = 0; i < n; i++)
			suma += a[i], sumb += b[i];
		f[0] = 1;
		for(int i = 0; i < n; i++) //求出a+b的子集和的所有可能取值 
		{
			int x = a[i] + b[i];
			for(int j = 1000000 - x; j >= 0; j--)
				f[j + x] |= f[j];
		}
		int ans = 2147483647;
		for(int i = 0; i <= 1000000; i++)
		{
			if(f[i])
				ans = min(ans, max(sumb - i, i - suma)); //计算答案 
		}
		return ans;
	}
};