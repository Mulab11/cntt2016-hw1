#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#include <sstream>

double f(double n, double k)
{
	double x = pow(((-3 + n)/(-1 + n)),k);
	return (1 - x + x*n)/n;
}

class TheSwapsDivOne
{
public:
	double find(vector<string> inp, int k)
	{
		stringstream ins;
		for(int i = 0; i != (int) inp.size(); ++i) ins << inp[i];
		string s = ins.str();
		// 猜想：除了保留在原位，每个数在其他位置的概率相同
		// 怎么求每个数保留在原位的概率？
		// 用一个 DP？
		const int N = s.size();
		// 第 1 种：之前已经在原来的位置，这一步继续保留，概率为 (N-1)(N-2) / N(N-1)
		// 第 2 种：原来在别的位置，这一步恰好换回来了
		// f[i] = f[i - 1] * (N - 2) / N + (1 - f[i - 1]) / (N * (N - 1) / 2); 递归式解出来在上面
		// 那么我们就可以枚举每一位移动到哪里
		double ans = 0, prob[2] = {(1 - f(N, k)) / (N - 1), f(N, k)};
		for(int i = 0; i != N; ++i)
		{
			const int v = s[i] - '0';
			if(!v) continue;
			for(int j = 0; j != N; ++j)
				ans += v * prob[i == j] * (j + 1) * (N - j);
		}
		return ans / (N * (N + 1) / 2);
	}
}	user;
