#include <algorithm>
#include <memory.h>
#include <math.h>
using namespace std;
int dp[2505][2505];
bool bdp[2505][2505];
int n, m, lst[2505], a[2505], sum[2505];
class LittleElephantAndRGB
{
public:
	int Getdp(int a, int b)
	{
		if(bdp[a][b]) 
			return dp[a][b];
		bdp[a][b] = true;
		if(a == n || (a + m - b - 1) >= n) 
			return dp[a][b] = 0;
		dp[a][b] = 0;
		if(sum[a + m - b - 1] - sum[a - 1] == m - b)
			dp[a][b] += n - max(a, a + m - b - 1);
		else
			dp[a][b] += n - lst[a];
		dp[a][b] += Getdp(a + 1, b);
		return dp[a][b];
	}
	long long getNumber(vector<string> list, int green)
	{
		m = green;
		long long ans = 0;
		int k = list.size(), a[2505];
		for(int i = 0; i < k; i++) //预处理字符串 
		{
			for(int j = 0; j < list[i].length(); j++)
			{
				a[n] = 0;
				if(list[i][j] == 'G') 
					a[n] = 1;
				n++;
			}
		}
		sum[0] = a[0];
		for(int i = 1; i < n; i++)
			sum[i] = sum[i - 1] + a[i];
		lst[n] = n;
		for(int i = n - 1; i >= 0; i--)
		{
			lst[i] = n;
			if(i + m - 1 < n)
			{
				if(sum[i + m - 1] - sum[i - 1] == m)
					lst[i] = i + m - 1;
				else
					lst[i] = lst[i + 1];
			}
		}
		memset(bdp, 0, sizeof(bdp));
		for(int i = 0; i < n - 1; i++) //计算答案 
		{
			int len = 0, flag = true;
			for(int j = i; j >= 0; j--)
			{
				if(a[j] && flag && len < m) 
					len++;
				else
					flag = false;
				if(lst[j] <= i)
					len = m;
				ans += Getdp(i + 1, len);
			}
		}
		return ans;
	}
};