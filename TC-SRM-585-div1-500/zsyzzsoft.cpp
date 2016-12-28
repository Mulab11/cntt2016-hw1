#include <algorithm>
using namespace std;
const int p = 1000000007;
int c[2501][2501];
class LISNumber
{
public:
	int count(vector<int> cnt, int k)
	{
		int n = 0, f[2501] = {0};
		for(int i = 0; i < cnt.size(); i++)
			n += cnt[i];
		for(int i = 0; i <= 2500; i++)
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; j++)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
		}
		for(int i = 1; i <= k; i++)
		{
			f[i] = 1;
			for(int j = 0; j < cnt.size(); j++) //按顺序把每种数放到递增序列的末尾 
				f[i] = (long long)f[i] * c[i][cnt[j]] % p;
			for(int j = 0; j < i; j++) //容斥 
				f[i] = (f[i] + p - (long long)f[j] * c[n + i - j][i - j] % p) % p;
		}
		return f[k];
	}
};