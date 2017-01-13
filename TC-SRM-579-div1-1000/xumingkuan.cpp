#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class RockPaperScissors
{
private:
	double f[55][55][55][3];//f(u)[i][j][k][l]: probability of: the first (i+j+k) results of first (u+1) dice are i rocks, j papers, and k scissors, and the (i+j+k+1)-th result is k(rock = 0, paper = 1, scissors = 2)
	double a[55][3];//rock, paper, scissors
public:
	double bestScore(vector<int> rockProb, vector<int> paperProb, vector<int> scissorsProb)
	{
		int n = rockProb.size();
		for(int i = 0; i < n; i++)
			a[i][0] = rockProb[i] / 300.0, a[i][1] = paperProb[i] / 300.0, a[i][2] = scissorsProb[i] / 300.0;
		memset(f, 0, sizeof(f));
		f[0][0][0][0] = 1;
		for(int u = 0; u < n; u++)
			for(int i = u + 1; i >= 0; i--)
				for(int j = u + 1 - i; j >= 0; j--)
					for(int k = u + 1 - i - j; k >= 0; k--)
					{
						double tmp[3] = {f[i][j][k][0], f[i][j][k][1], f[i][j][k][2]};
						for(int l = 0; l < 3; l++)
							f[i][j][k][l] = (tmp[l] * (u - i - j - k)/*the u-th die's place: > i+j+k+1*/ + (tmp[0] + tmp[1] + tmp[2]) * a[u][l]/*the u-th die's place: == i+j+k+1*/ + ((i ? f[i - 1][j][k][l] * a[u][0] : 0) + (j ? f[i][j - 1][k][l] * a[u][1] : 0) + (k ? f[i][j][k - 1][l] * a[u][2] : 0)) * (i + j + k)/*the u-th die's place: <= i+j+k*/) / (u + 1);
					}
		double ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; i + j < n; j++)
				for(int k = 0; i + j + k < n; k++)
					ans += max(3 * f[i][j][k][0] + f[i][j][k][1], max(3 * f[i][j][k][1] + f[i][j][k][2], 3 * f[i][j][k][2] + f[i][j][k][0]));//add the expectation directly, we don't need to divide or multiply anything
		return ans;
	}
};

