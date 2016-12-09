#include <algorithm>
using namespace std;
const int p = 1000000007;
class WolfInZooDivOne
{
public:
	vector<int> Parse(const vector<string> &vec)
	{
		string str;
		for(int i = 0; i < vec.size(); i++)
			str += vec[i];
		vector<int> ret;
		ret.push_back(0);
		for(int i = 0, j = 0; i < str.length(); i++)
		{
			if(str[i] == ' ')
				ret.push_back(0), j++;
			else
				ret[j] = ret[j] * 10 + (str[i] - '0');
		}
		return ret;
	}
	int count(int n, vector<string> _l, vector<string> _r)
	{
		vector<int> l = Parse(_l), r = Parse(_r);
		int m = l.size();
		for(int i = 0; i < m; i++)
			l[i]++, r[i]++;
		int ans = 0, f[301][301] = {0};
		f[0][0] = 1;
		for(int i = 0; i <= n; i++)
		{
			for(int j = i; j <= n; j++)
			{
				ans = (ans + f[i][j]) % p;
				int x = j;
				for(int k = 0; k < m; k++) //已经放满的区间不能再放 
				{
					if(l[k] <= i)
						x = max(x, r[k]);
				}
				for(int k = x + 1; k <= n; k++) //从下一个能放的位置开始放 
					f[j][k] = (f[j][k] + f[i][j]) % p;
			}
		}
		return ans;
	}
};