#include <algorithm>
using namespace std;
const int p = 1000000007;
struct Value
{
	long long v;
	int num;
	bool half;
	Value() {v = 0, num = 0, half = false; }
	Value(long long _v, int _num, bool _half) {v = _v, num = _num, half = _half; }
	bool operator < (const Value &_v) const
	{
		return v < _v.v;
	}
};
class SweetFruits
{
public:
	int mat[41][41];
	vector<Value> val;
	int Pow(int x, int y)
	{
		int ret = 1;
		while(y)
		{
			if(y & 1)
				ret = (long long)ret * x % p;
			x = (long long)x * x % p;
			y >>= 1;
		}
		return ret;
	}
	int Det(int n) //求行列式 
	{
		for(int i = 0, j; i < n; i++) //消元 
		{
			for(j = i; j < n && !mat[j][i]; j++);
			if(j == n)
				return 0;
			for(int k = 0; k < n; k++)
				swap(mat[i][k], mat[j][k]);
			for(j = i + 1; j < n; j++)
			{
				int t = (long long)mat[j][i] * Pow(mat[i][i], p - 2) % p;
				for(int k = 0; k < n; k++)
					mat[j][k] = (mat[j][k] - (long long)t * mat[i][k] % p + p) % p;
			}
		}
		int ret = 1;
		for(int i = 0; i < n; i++)
			ret = (long long)ret * mat[i][i] % p;
		return ret;
	}
	int countTrees(vector<int> w, int _max_w)
	{
		long long max_w = -_max_w;
		int n = w.size(), q = 0;
		for(int i = 0; i < n; i++)
			max_w += max(w[i], 0), q += w[i] >= 0;
		int m = n / 2;
		int c[41][41] = {0}, cur[41] = {0}, cnt[41] = {0}, f[41] = {0};
		for(int i = 0; i <= n; i++)
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; j++)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
		}
		for(long long i = 0; i < 1 << m; i++) //双向搜索 
		{
			long long sum = 0;
			int num = 0;
			for(int k = 0; k < n; k++)
			{
				if((i >> k) & 1)
				{
					if(w[k] < 0)
						num = -1000000000;
					sum += w[k];
					num++;
				}
			}
			if(num >= 0)
				val.push_back(Value(sum, num, false));
		}
		for(int j = 0; j < 1 << (n - m); j++)
		{
			long long i = (long long)j << m;
			long long sum = 0;
			int num = 0;
			for(int k = 0; k < n; k++)
			{
				if((i >> k) & 1)
				{
					if(w[k] < 0)
						num = -1000000000;
					sum += w[k];
					num++;
				}
			}
			if(num >= 0)
				val.push_back(Value(sum, num, true));
		}
		sort(val.begin(), val.end());
		for(int i = 0, j = val.size(); i < val.size(); i++) //扫描 
		{
			while(j && val[i].v + val[j - 1].v >= max_w)
				cur[val[j - 1].num] += val[j - 1].half, j--;
			if(!val[i].half)
			{
				for(int k = val[i].num; k <= q; k++)
					cnt[k] = (cnt[k] + cur[k - val[i].num]) % p;
			}
		}
		for(int i = q; i >= 0; i--)
		{
			for(int j = 0; j < n; j++)
				mat[j][j] = 0;
			for(int u = 0; u < n; u++) //生成树计数 
			{
				for(int v = 0; v < n; v++)
				{
					if(u == v)
						continue;
					if(u < i || v < i)
						mat[u][v] = u >= q || v >= q;
					else
						mat[u][v] = 1;
					if(mat[u][v])
						mat[u][u]++, mat[u][v] = p - 1;
				}
			}
			f[i] = Det(n - 1);
			for(int j = i + 1; j <= q; j++) //容斥 
				f[i] = (f[i] - (long long)f[j] * c[q - i][j - i] % p + p) % p;
		}
		int ans = 0;
		for(int i = 0; i <= q; i++)
			ans = ((long long)f[i] * cnt[i] + ans) % p;
		return ans;
	}
};
