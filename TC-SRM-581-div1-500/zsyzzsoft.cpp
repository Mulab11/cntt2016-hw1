#include <algorithm>
using namespace std;
int d1[300][300], d2[300][300], c1[8], c2[8];
class TreeUnion
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
	double expectedCycles(vector<string> tree1, vector<string> tree2, int k)
	{
		vector<int> edge1 = Parse(tree1), edge2 = Parse(tree2);
		int n = edge1.size() + 1;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				d1[i][j] = d2[i][j] = 1000000000;
			d1[i][i] = d2[i][i] = 0;
		}
		for(int i = 0; i + 1 < n; i++)
			d1[i + 1][edge1[i]] = d1[edge1[i]][i + 1] = d2[i + 1][edge2[i]] = d2[edge2[i]][i + 1] = 1;
		for(int k = 0; k < n; k++)
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
				{
					d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
					d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);
				}
			}
		}
		for(int i = 0; i < n; i++) //统计出每种长度的路径条数 
		{
			for(int j = 0; j < n; j++)
			{
				if(d1[i][j] < k)
					c1[d1[i][j]]++;
				if(d2[i][j] < k)
					c2[d2[i][j]]++;
			}
		}
		k -= 2;
		double ans = 0.0;
		for(int i = 1; i < k; i++) //每个环对期望的贡献独立 
			ans += (double)c1[i] * c2[k - i];
		return ans / 2.0 / n / (n - 1);
	}
};