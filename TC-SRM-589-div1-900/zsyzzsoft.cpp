#include <algorithm>
using namespace std;
int n, m, t, x[300], y[300];
class FlippingBitsDiv1
{
public:
	int Work1()
	{
		int ret = n;
		for(int s = 0; s < 1 << m; s++) //枚举最终的特征串 
		{
			int ans = 0;
			for(int i = t * m; i < n; i++)
				ans += (s >> (i - t * m) & 1) ^ x[i];
			bool rev = false, pay = true;
			for(int i = t - 1; i >= 0; i--) //贪心从后向前处理 
			{
				int cnt = 0;
				for(int j = 0; j < m; j++)
					cnt += (s >> j & 1) ^ x[i * m + j];
				if(rev)
					cnt = m - cnt;
				if(m - cnt + pay < cnt) //翻转严格更优 
				{
					ans += m - cnt + pay; //执行区间翻转后按位操作 
					rev ^= 1;
					pay = true;
				}
				else
				{
					ans += cnt; //直接按位操作 
					pay = m - cnt + pay != cnt; //若翻转与不翻转等价，先不做区间翻转，视为下次可以免费翻转 
				}
			}
			ret = min(ret, ans);
		}
		return ret;
	}
	int Work2()
	{
		int ret = n;
		for(int s = 0; s < 1 << t; s++) //枚举区间操作的情况 
		{
			int ans = 0;
			for(int i = t - 1, k = 0; i >= 0; i--)
			{
				if(s >> i & 1)
					k ^= 1, ans++;
				for(int j = 0; j < m; j++)
					y[i * m + j] = k;
			}
			for(int i = 0; i < m; i++)
			{
				int a = 0, b = 0;
				for(int j = i; j < n; j += m) //统计每组必须相同的字符中0与1的个数 
					x[j] ^ y[j] ? a++ : b++;
				ans += min(a, b);
			}
			ret = min(ret, ans);
		}
		return ret;
	}
	int getmin(vector<string> s, int _m)
	{
		string str;
		for(int i = 0; i < s.size(); i++)
			str += s[i];
		n = str.length(), m = _m, t = n / m;
		for(int i = 0; i < n; i++)
			x[i] = str[i] == '1';
		return m <= t ? Work1() : Work2(); //分两种情况处理 
	}
};