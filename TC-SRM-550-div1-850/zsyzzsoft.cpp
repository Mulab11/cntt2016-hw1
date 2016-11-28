#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1000000007;
struct Matrix
{
	int mat[145][145];
	Matrix()
	{
		memset(mat, 0, sizeof(mat));
	}
	Matrix operator * (const Matrix &_mat) const
	{
		Matrix ret;
		for(int k = 0; k <= 144; k++)
		{
			for(int i = 0; i <= 144; i++)
			{
				if(mat[i][k])
				{
					for(int j = 0; j <= 144; j++)
						ret.mat[i][j] = ((long long)mat[i][k] * _mat.mat[k][j] + ret.mat[i][j]) % p;
				}
			}
		}
		return ret;
	}
};
class ConversionMachine
{
public:
	int n;
	Matrix Pow(Matrix mat, int m) //矩阵快速幂 
	{
		Matrix ans;
		for(int i = 0; i <= 144; i++)
			ans.mat[i][i] = 1;
		while(m)
		{
			if(m & 1)
				ans = ans * mat;
			mat = mat * mat;
			m >>= 1;
		}
		return ans;
	}
	int countAll(string word1, string word2, vector<int> costs, int max_cost)
	{
		n = word1.length();
		int cnt[3] = {0};
		for(int i = 0; i < n; i++) //计算最小代价 
		{
			char a = word1[i] - 'a', b = word2[i] - 'a';
			cnt[(3 + b - a) % 3]++;
			while(a != b)
				max_cost -= costs[a], a = (a + 1) % 3;
			if(max_cost < 0)
				return 0;
		}
		int m = max_cost / ((long long)costs[0] + costs[1] + costs[2]); //余下的轮换数 
		int p = cnt[2] * 12 + cnt[1]; //初始状态 
		Matrix mat;
		for(int i = 0; i <= n; i++) //转移矩阵 
		{
			for(int j = 0; i + j <= n; j++)
			{
				if(i)
					mat.mat[i * 12 + j][(i - 1) * 12 + j + 1] += i;
				if(j)
					mat.mat[i * 12 + j][i * 12 + j - 1] += j;
				if(i + j < n)
					mat.mat[i * 12 + j][(i + 1) * 12 + j] += n - i - j;
			}
		}
		mat.mat[144][p] = mat.mat[144][144] = 1; //记录和的一项 
		return Pow(mat, m * 3 + cnt[2] * 2 + cnt[1] + 1).mat[144][0];
	}
};
