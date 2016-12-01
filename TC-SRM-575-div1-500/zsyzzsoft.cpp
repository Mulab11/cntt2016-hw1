#include <algorithm>
using namespace std;
int n, sum, x[2210];
class TheSwapsDivOne
{
public:
	double find(vector<string> seq, int k)
	{
		for(int i = 0; i < seq.size(); i++)
		{
			for(int j = 0; j < seq[i].length(); j++)
				sum += x[n++] = seq[i][j] - '0';
		}
		double t = 1.0; //经过k次后的加权平均系数 
		for(int i = 0; i < k; i++)
			t *= (double)(n - 3) / (n - 1);
		double ans = 0.0;
		for(int i = 0; i < n; i++)
			ans += (t * x[i] + (1.0 - t) / n * sum) * (i + 1) * (n - i);
		return ans / (n * (n + 1) / 2);
	}
};