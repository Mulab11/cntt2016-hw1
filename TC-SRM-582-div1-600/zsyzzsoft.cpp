#include <algorithm>
using namespace std;
const int p = 1000000009;
int col[2000], f[2000][2001], sum[2001], same[2001][3600], fac[2001], inv[2001];
class ColorfulBuilding
{
public:
	string Concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < vec.size(); i++)
			ret += vec[i];
		return ret;
	}
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
	int count(vector<string> color1, vector<string> color2, int l)
	{
		string str1 = Concatenate(color1), str2 = Concatenate(color2);
		int n = str1.size();
		for(int i = 0; i < n; i++)
			col[i] = (str1[i] - 'A') * 60 + (str2[i] - 'A');
		fac[0] = 1;
		for(int i = 1; i <= n; i++) //预处理阶乘及其逆元 
			fac[i] = (long long)fac[i - 1] * i % p;
		for(int i = 0; i <= n; i++)
			inv[i] = Pow(fac[i], p - 2);
		f[n - 1][l - 1] = 1;
		sum[l - 1] = same[l - 1][col[n - 1]] = 1;
		for(int i = n - 2; i >= 0; i--)
		{
			for(int j = 0; j < l; j++) //放完了1 to i的楼，得到了j个色块 
				f[i][j] = ((long long)sum[j + 1] - same[j + 1][col[i]] + same[j][col[i]] + p) * fac[n - i - 2] % p;
			for(int j = 0; j < l; j++) //前缀和 
				sum[j] = ((long long)f[i][j] * inv[n - i - 1] + sum[j]) % p;
			for(int j = 0; j < l; j++) //颜色相同的前缀和 
				same[j][col[i]] = ((long long)f[i][j] * inv[n - i - 1] + same[j][col[i]]) % p;
		}
		return (long long)sum[0] * fac[n - 1] % p;
	}
};