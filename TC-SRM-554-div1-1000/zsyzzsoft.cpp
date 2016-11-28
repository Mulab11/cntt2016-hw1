#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1234567891;
const int state[15][4] = {{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 0, 1}, {0, 1, 1, 0},
	{0, 0, 1, 2}, {0, 1, 0, 2}, {0, 1, 2, 0}, {1, 0, 0, 2}, {1, 0, 2, 0}, {1, 2, 0, 0}, {0, 1, 2, 3}};
const int cnt[15] = {1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4};
const int adj[15] = {4, 2, 2, 2, 2, 2, 2, 0, 1, 1, 0, 0, 1, 1, 0};
struct Matrix
{
	int mat[121][121];
	Matrix()
	{
		memset(mat, 0, sizeof(mat));
	}
	Matrix operator * (const Matrix &_mat) const
	{
		Matrix ret;
		for(int k = 0; k < 121; k++)
		{
			for(int i = 0; i < 121; i++)
			{
				if(mat[i][k])
				{
					for(int j = 0; j < 121; j++)
						ret.mat[i][j] = ((long long)mat[i][k] * _mat.mat[k][j] + ret.mat[i][j]) % p;
				}
			}
		}
		return ret;
	}
};
void Add(int &a, int b)
{
	a = ((long long)a + b) % p;
}
class TheBrickTowerHardDivOne
{
public:
	int A(int n, int m) //排列数 
	{
		if(n < m)
			return 0;
		int ret = 1;
		for(int i = 0; i < m; i++)
			ret = (long long)ret * (n - i) % p;
		return ret;
	}
	int find(int n, int q, long long h)
	{
		Matrix ans, mat;
		for(int i = 0; i < 15; i++) //构造矩阵 
		{
			if(cnt[i] > n)
				continue;
			for(int j = 0; j < 15; j++)
			{
				int col[4] = {0};
				for(col[0] = 0; col[0] <= cnt[i]; col[0]++) //枚举颜色的相对关系 
				{
					for(col[1] = 0; col[1] <= cnt[i]; col[1]++)
					{
						if(cnt[j] > 1 && col[1] < cnt[i] && col[0] == col[1])
							continue;
						for(col[2] = 0; col[2] <= cnt[i]; col[2]++)
						{
							if(cnt[j] > 2 && col[2] < cnt[i] && (col[0] == col[2] || col[1] == col[2]))
								continue;
							for(col[3] = 0; col[3] <= cnt[i]; col[3]++)
							{
								if(cnt[j] > 3 && col[3] < cnt[i] && (col[0] == col[3] || col[1] == col[3] || col[2] == col[3]))
									continue;
								int m = 0;
								for(int k = 0; k < cnt[j]; k++)
									m += col[k] == cnt[i];
								int sum = A(n - cnt[i], m), num = adj[j];
								for(int k = 0; k < 4; k++)
									num += state[i][k] == col[state[j][k]];
								for(int k = 0; k + num <= q; k++)
									Add(mat.mat[k * 15 + i][(k + num) * 15 + j], sum);
								if(cnt[j] <= 3)
									break;
							}
							if(cnt[j] <= 2)
								break;
						}
						if(cnt[j] <= 1)
							break;
					}
				}
			}
		}
		for(int i = 0; i < (q + 1) * 15; i++)
			mat.mat[i][120] = 1;
		mat.mat[120][120] = 1;
		for(int i = 0; i < 15; i++)
			ans.mat[0][adj[i] * 15 + i] = A(n, cnt[i]);
		while(h) //快速幂 
		{
			if(h & 1)
				ans = ans * mat;
			mat = mat * mat;
			h >>= 1;
		}
		return ans.mat[0][120];
	}
};
