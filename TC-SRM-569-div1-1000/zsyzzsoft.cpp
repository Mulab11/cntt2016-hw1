#include <algorithm>
#include <memory.h>
using namespace std;
int p = 1000000009;
struct Matrix
{
	int mat[17][17];
	Matrix()
	{
		memset(mat, 0, sizeof(mat));
	}
	Matrix operator * (const Matrix &_mat) const
	{
		Matrix ret;
		for(int k = 0; k <= 16; k++)
		{
			for(int i = 0; i <= 16; i++)
			{
				if(mat[i][k])
				{
					for(int j = 0; j <= 16; j++)
						ret.mat[i][j] = ((long long)mat[i][k] * _mat.mat[k][j] + ret.mat[i][j]) % p;
				}
			}
		}
		return ret;
	}
};
class MegaFactorial
{
public:
	int m, k;
	Matrix Solve(int n, int p, int cp) //B进制分解 
	{
		if(!n)
		{
			Matrix mat;
			for(int i = 0; i <= 16; i++)
				mat.mat[i][i] = 1;
			return mat;
		}
		int x = 0;
		for(int i = p; i > 1; i /= cp)
			x++;
		Matrix mat;
		for(int i = 0; i <= 16; i++)
		{
			for(int j = i; j <= 16; j++)
				mat.mat[i][j] = 1;
		}
		for(int i = 1; i <= 16; i++)
			mat.mat[0][i] = x;
		Matrix sub = Solve(p - 1, p / cp, cp);
		mat = sub * mat;
		Matrix ret;
		for(int i = 0; i <= 16; i++)
			ret.mat[i][i] = 1;
		for(int i = n / p; i; i >>= 1) //快速幂 
		{
			if(i & 1)
				ret = ret * mat;
			mat = mat * mat;
		}
		if(n % p == p - 1)
			return ret * sub;
		return ret * Solve(n % p, p / cp, cp);
	}
	int Work(int p)
	{
		int mp = 1;
		while((long long)mp * p <= m)
			mp *= p;
		Matrix mat = Solve(m, mp, p);
		return mat.mat[0][k];
		int ans = 0;
		for(int i = 0; i <= 16; i++)
			ans = (ans + mat.mat[i][k]) % p;
		return ans;
	}
	int Div(int u, int v) //B=u时除以v下取整的值 
	{
		int a = Work(u);
		swap(p, v);
		int b = Work(u);
		swap(p, v);
		if(v == 2)
			return (a + p - b) * 500000005LL % p;
		return (a + p - b) * 666666673LL % p;
	}
	int countTrailingZeros(int _m, int _k, int b)
	{
		m = _m, k = _k;
		if(b == 2)
			return Work(2);
		if(b == 3)
			return Work(3);
		if(b == 4)
			return Div(2, 2);
		if(b == 5)
			return Work(5);
		if(b == 6)
			return Work(3);
		if(b == 7)
			return Work(7);
		if(b == 8)
			return Div(2, 3);
		if(b == 9)
			return Div(3, 2);
		return Work(5);
	}
};
