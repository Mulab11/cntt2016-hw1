#include <algorithm>
using namespace std;
int n, l[2500], r[2500], f[2500], g[2500];
class ShoutterDiv1
{
public:
	void Parse(const vector<string> &vec, int *arr, int inc)
	{
		string str;
		for(int i = 0; i < vec.size(); i++)
			str += vec[i];
		n = str.length();
		for(int i = 0; i < n; i++)
			arr[i] += inc * (str[i] - '0');
	}
	int CalF(int x)
	{
		if(f[x] >= 0)
			return f[x];
		for(int i = 0; i < n; i++)
		{
			if(r[i] < l[x])
				f[x] = 10000;
		}
		if(f[x] < 0) //不需要转发 
			return f[x] = 0;
		for(int i = 0; i < n; i++)
		{
			if(r[i] >= l[x] && l[i] < l[x]) //可以转发 
				f[x] = min(f[x], CalF(i) + 1); 
		}
		return f[x];
	}
	int CalG(int x)
	{
		if(g[x] >= 0)
			return g[x];
		for(int i = 0; i < n; i++)
		{
			if(l[i] > r[x])
				g[x] = 10000;
		}
		if(g[x] < 0)
			return g[x] = 0;
		for(int i = 0; i < n; i++)
		{
			if(l[i] <= r[x] && r[i] > r[x])
				g[x] = min(g[x], CalG(i) + 1);
		}
		return g[x];
	}
	int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1,
		vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1)
	{
		Parse(s1000, l, 1000);
		Parse(s100, l, 100);
		Parse(s10, l, 10);
		Parse(s1, l, 1);
		Parse(t1000, r, 1000);
		Parse(t100, r, 100);
		Parse(t10, r, 10);
		Parse(t1, r, 1);
		for(int i = 0; i < n; i++)
			f[i] = g[i] = -1;
		for(int i = 0; i < n; i++) //计算从每个区间开始向左需要转发几次 
			CalF(i);
		for(int i = 0; i < n; i++) //向右 
			CalG(i);
		for(int i = 0; i < n; i++)
		{
			if(f[i] == 10000) //无解 
				return -1;
		}
		int sum = 0;
		for(int i = 0; i < n; i++)
		{
			int ans = f[i] + g[i];
			for(int j = 0; j < n; j++)
			{
				if(r[j] >= l[i] && l[j] <= r[i]) //可以先向一个大区间转发 
					ans = min(ans, f[j] + g[j] + 1);
			}
			sum += ans;
		}
		return sum;
	}
};