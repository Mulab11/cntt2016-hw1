#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
unsigned long long MOD;
const int MAXN = 20;
class Matrix
{
public:
	unsigned long long a[MAXN][MAXN];
	static int n;
	Matrix()
	{
		memset(a, 0, sizeof(a));
	}
	Matrix(int)
	{
		memset(a, 0, sizeof(a));
		for(int i = 0; i < n; i++)
			a[i][i] = 1;
	}
	Matrix operator *(const Matrix &b) const
	{
		Matrix c;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					c.a[i][k] = (c.a[i][k] + a[i][j] * b.a[j][k]) % MOD;
		return c;
	}
};
int Matrix::n = 0;
Matrix quickmul(const Matrix &a, int b)
{
	if(b <= 1)
		return b ? a : Matrix(1);
	Matrix tmp = quickmul(a, b >> 1);
	tmp = tmp * tmp;
	return b & 1 ? tmp * a : tmp;
}
class MegaFactorial
{
private:
	int b, cntb;
	Matrix u, ans;
public:
	int countTrailingZeros(int N, int K, int B)
	{
		if(B == 7)//7
			b = 7, cntb = 1;
		else if(B % 5 == 0)//5, 10
			b = 5, cntb = 1;
		else if(B % 3 == 0)//3, 6, 9
			b = 3, cntb = (B == 9 ? 2 : 1);
		else//2, 4, 8
			b = 2, cntb = (B == 8 ? 3 : B == 4 ? 2 : 1);
		//answer = \sum_p \sum_{b^p | i} C(N - i + K, K) / cntb
		MOD = 1000000009ll * cntb;
		memset(u.a, 0, sizeof(u.a));
		u.n = K + 1;
		for(int i = 1; i < u.n; i++)
			for(int j = i; j < u.n; j++)
				u.a[i][j] = 1;
		u.a[0][0] = 1;//constant
		ans = Matrix(1);
		while(N)
		{
			ans = quickmul(u, N % b) * ans;
			u = quickmul(u, b);
			for(int i = 1; i < u.n; i++)
				u.a[0][i]++;
			N /= b;
			//printf("%d %I64u\n", N, ans.a[0][ans.n - 1]);
		}
		return ans.a[0][ans.n - 1] / cntb;// % (MOD / cntb);
	}
};

