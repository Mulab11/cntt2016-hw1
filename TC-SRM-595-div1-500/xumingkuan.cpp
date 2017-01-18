#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int MAXN = 2525;
class LittleElephantAndRGB
{
private:
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < (int)vec.size(); i++)
			ret += vec[i];
		return ret;
	}
	int n;
	string a;//list
	int prev[MAXN], next[MAXN];//length of max consecutive green
	int f[MAXN];//f(i)[j]: first i letters, string has j last consecutive 'G' and doesn't have >=minGreen consecutive 'G', number of pairs (a, b)
	int sum[MAXN];//suffix sum of f(i)
	int g;//g(i): first i letters, >=minGreen consecutive 'G', number of pairs (a, b)
public:
	long long getNumber(vector<string> list, int minGreen)
	{
		n = (a = concatenate(list)).size();
		prev[0] = 0;
		for(int i = 1; i <= n; i++)
			prev[i] = a[i - 1] == 'G' ? prev[i - 1] + 1 : 0;
		next[n + 1] = 0;
		for(int i = n; i >= 1; i--)
			next[i] = a[i - 1] == 'G' ? next[i + 1] + 1 : 0;
		memset(f, 0, sizeof(f));
		memset(sum, 0, sizeof(sum));
		long long ans = 0;
		g = 0;
		for(int i = 1; i <= n; i++)//enum c-1
		{
			for(int j = i - 1; j >= 0; j--)//enum a-1 (b == i)
			{
				if(min(next[j + 1], i - j) >= minGreen)
				{
					g += j + 1;
					break;
				}
				else
					f[min(prev[i], i - j)]++;
			}
			int mxf = min(i, minGreen - 1);
			sum[mxf] = f[mxf];
			for(int j = mxf - 1; j >= 0; j--)
				sum[j] = sum[j + 1] + f[j];
			for(int j = i + 1; j <= n; j++)//enum d
			{
				if(min(prev[j], j - i) >= minGreen)
				{
					ans += (long long)(n - j + 1) * (i * (i + 1) / 2);
					break;
				}
				else
					ans += sum[minGreen - min(next[i + 1], j - i)] + g;
			}
			//printf("%d %I64d %d\n", i, ans, g);
		}
		return ans;
	}
};

