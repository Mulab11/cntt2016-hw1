#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1000000007;
int n;
struct Matrix
{
	int mat[350];
	Matrix()
	{
		memset(mat, 0, sizeof(mat));
	}
	Matrix operator * (const Matrix &_mat) const
	{
		Matrix ret;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				ret.mat[(i + j) % n] = ((long long)mat[i] * _mat.mat[j] + ret.mat[(i + j) % n]) % p;
		}
		return ret;
	}
};
int dp[351][350];
class PenguinEmperor
{
public:
	int countJourneys(int _n, long long m)
	{
		n = _n;
		dp[0][0] = 1;
		for(int i = 1; i <= n; i++) //动态规划一个周期 
		{
			for(int j = 0; j < n; j++)
				dp[i][j] = i == n || i * 2 == n ? dp[i - 1][(j + i) % n] : (dp[i - 1][(j + i) % n] + dp[i - 1][(j + n - i) % n]) % p;
		}
		Matrix ans, mat;
		for(int i = 0; i < n; i++)
			ans.mat[i] = dp[m % n][i];
		for(int i = 0; i < n; i++)
			mat.mat[i] = dp[n][i];
		m /= n;
		while(m) //快速幂 
		{
			if(m & 1)
				ans = ans * mat;
			mat = mat * mat;
			m >>= 1;
		}
		return ans.mat[0];
	}
};
