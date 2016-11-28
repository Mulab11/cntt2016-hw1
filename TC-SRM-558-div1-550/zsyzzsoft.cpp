#include <algorithm>
using namespace std;
int sum[10001];
class Ear
{
public:
	int n, m, r[300], b[300], h[300];
	void Parse(const vector<string> &vec, int *a, int &cnt)
	{
		string str;
		for(int i = 0; i < vec.size(); i++)
			str += vec[i];
		for(int i = 0; i < str.length(); i++)
		{
			if(str[i] == ' ')
				cnt++;
			else
				a[cnt] = a[cnt] * 10 + (str[i] - '0');
		}
		cnt++;
	}
	long long Calc(int p, int q) //等差数列求和 
	{
		return (p - q + p - 1) * q / 2;
	}
	int Sum(int a = 10000)
	{
		return a < 0 ? 0 : sum[min(a, 10000)];
	}
	long long getCount(vector<string> r_vec, vector<string> b_vec, vector<string> h_vec)
	{
		Parse(r_vec, r, n);
		Parse(b_vec, b, m);
		Parse(h_vec, h, m = 0);
		for(int i = 0; i < n; i++)
			sum[r[i]]++;
		for(int i = 1; i <= 10000; i++)
			sum[i] += sum[i - 1];
		long long ans = 0;
		for(int i = 0; i < m; i++) //枚举两个顶点 
		{
			for(int j = 0; j < m; j++)
			{
				if(h[i] <= h[j])
					continue;
				ans += Calc(Sum(b[j] - 1), Sum(min(((b[j] - b[i]) * h[i] + b[i] * (h[i] - h[j]) - 1) / (h[i] - h[j]), b[i] - 1))) *
					Calc(Sum() - Sum(b[j]), Sum() - Sum(max(((b[j] - b[i]) * h[i] + b[i] * (h[i] - h[j])) / (h[i] - h[j]), b[i])));
			}
		}
		return ans;
	}
};
