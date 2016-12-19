#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

double f[51][51][51][51], s[50];

class RockPaperScissors
{
public:
	double bestScore(vector<int> A, vector<int> B, vector<int> C)
	{
		const int N = A.size();
		// f(i,a,b,c)：已经取了 a、b、c，那么 i 没有被取概率
		for(int k = 0; k <= N; ++k)
		{
			double (*f)[51][51] = ::f[k];
			f[0][0][0] = 1;
			int n = 0;
			for(int i = 0; i != N; ++i) if(i != k)
			{
				double pa = A[i] / 300.0, pb = B[i] / 300.0, pc = C[i] / 300.0;
				// 这里要做一个 01 背包
				for(int a = n; a >= 0; --a)
				for(int b = n - a; b >= 0; --b)
				for(int c = n - a - b; c >= 0; --c)
				{
					double v = f[a][b][c];
					f[a + 1][b][c] += v * pa;
					f[a][b + 1][c] += v * pb;
					f[a][b][c + 1] += v * pc;
				}
				++n;
			}
		}
		for(int a = N - 1; a >= 0; --a)
		for(int b = N - 1 - a; b >= 0; --b)
		for(int c = N - 1 - a - b; c >= 0; --c)
			s[a + b + c] += f[N][a][b][c];
		// 枚举状态，对贡献进行计算
		double ret = 0;
		for(int a = N - 1; a >= 0; --a)
		for(int b = N - 1 - a; b >= 0; --b)
		for(int c = N - 1 - a - b; c >= 0; --c)
		{
			double ea = 0, eb = 0, ec = 0;
			for(int i = 0; i != N; ++i) // 枚举当前出现的棋子，计算概率
			{
				double p = f[i][a][b][c]; 
				// / (N - a - b - c) / s[a + b + c] 移动到下面去了
				ea += p * (A[i] + 3 * C[i]); // / 300 移动到下面去了
				eb += p * (B[i] + 3 * A[i]);
				ec += p * (C[i] + 3 * B[i]);
			}
			ret += max(max(ea, eb), ec) / s[a + b + c] / (N - a - b - c);
		}
		return ret / 300;
	}
}	user;