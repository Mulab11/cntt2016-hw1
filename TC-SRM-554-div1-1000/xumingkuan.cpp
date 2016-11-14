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
const int MOD = 1234567891;
const int MAXN = 64;
const long long MOD2 = (0x7fffffffffffffffll / MOD - MOD) * MOD;
class Matrix
{
	public:
		static int n;
		int a[MAXN][MAXN];
		Matrix()
		{
			memset(a, 0, sizeof(a));
		}
		int *operator [](int x)
		{
			return a[x];
		}
		const int *operator [](int x) const
		{
			return a[x];
		}
		Matrix operator *(const Matrix &b) const;
		void print() const
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					printf("%d ", a[i][j]);
				printf("\n");
			}
		}
};
int Matrix::n = 0;
long long buf[MAXN];
Matrix ret;
Matrix Matrix::operator *(const Matrix &b) const
{
	for(int i = 0; i < n; i++)
	{
		memset(buf, 0, n * sizeof(long long));
		const int *tmp1 = a[i];
		for(int j = 0; j < n; j++)
		{
			const long long tmp2 = tmp1[j];
			const int *tmp3 = b[j];
			for(int k = 0; k < n; k++)
			{
				buf[k] += tmp2 * tmp3[k];
				if(buf[k] >= MOD2)
					buf[k] -= MOD2;
			}
		}
		int *tmp4 = ret[i];
		for(int j = 0; j < n; j++)
			tmp4[j] = buf[j] % MOD;
	}
	return ret;
}
/*
2 * 2 bricks in the same height:

0	1	2	3	4	5	6
AA	AA	AA	AB	AA	AB	AB
AA	BA	BB	BA	CB	CA	DC
*/
const int STATUS[7][4] = {
	{0, 0, 0, 0}, 
	{0, 0, 0, 1}, 
	{0, 0, 1, 1}, 
	{0, 1, 0, 1}, 
	{0, 0, 1, 2}, 
	{0, 1, 0, 2}, 
	{0, 1, 2, 3}};
const int COLORS[7] = {1, 2, 2, 2, 3, 3, 4};//number of different colors
const int TYPES[7] = {1, 4, 2, 1, 4, 2, 1};//rotate types
const int SAME_COLOR[7] = {4, 2, 2, 0, 1, 0, 0};//neighboring bricks with the same color
class TheBrickTowerHardDivOne
{
	private:
	int c, k, col[4];
	Matrix u, ans;
	void transfer(int st, int ed, int num, int val)//status st -> ed, num pairs of neighboring bricks with the same color, val ways
	{
		for(int i = 0; i + num <= k; i++)
			u[st * (k + 1) + i + num][ed * (k + 1) + i] = ((long long)u[st * (k + 1) + i + num][ed * (k + 1) + i] + val) % MOD;
	}
	void work(int st, int ed, int val)//status st -> ed, val ways of color
	{
		for(int i = 0; i < TYPES[ed]; i++)
		{
			int tmp = 0;
			for(int j = 0; j < 4; j++)
				if(STATUS[st][j] == col[STATUS[ed][(i + j) % 4]])
					tmp++;//neighboring bricks with the same color with different height
			transfer(st, ed, SAME_COLOR[ed] + tmp, val);
		}
	}
	void search(int st, int ed, int pos, int val)//status st -> ed, search color #pos, val ways of color
	{
		if(pos == COLORS[ed])
		{
			work(st, ed, val);
			return;
		}
		for(col[pos] = 0; col[pos] <= COLORS[st]; col[pos]++)//== COLORS[st]: different from any color of status st
		{
			int nowval;
			if(col[pos] == COLORS[st])
			{
				nowval = c - COLORS[st];
				for(int i = 0; i < pos; i++)
					if(col[i] == COLORS[st])
						nowval--;
				if(nowval <= 0)
					continue;
			}
			else
			{
				nowval = 1;
				bool ok = true;
				for(int i = 0; i < pos; i++)
					if(col[pos] == col[i])
					{
						ok = false;
						break;
					}
				if(!ok)
					continue;
			}
			search(st, ed, pos + 1, (long long)val * nowval % MOD);
		}
	}
	long long arrange(int n, int m)
	{
		long long ret = 1;
		for(int i = 0; i < m; i++)
			ret = ret * (n - i) % MOD;
		return ret;
	}
	public:
	int find(int C, int K, long long H)
	{
		memset(u.a, 0, sizeof(u.a));
		c = C, k = K;
		Matrix::n = 7 * (k + 1) + 1;
		for(int i = 0; i < 7 && COLORS[i] <= c; i++)
			for(int j = 0; j < 7 && COLORS[i] <= c; j++)//status i -> j
				search(i, j, 0, 1);
		for(int i = 0; i < Matrix::n; i++)
			u[i][Matrix::n - 1] = 1;//status (Matrix::n - 1): end of tower
		//u.print();
		memset(ans.a, 0, sizeof(ans.a));
		for(int i = 0; i < Matrix::n; i++)
			ans[i][i] = 1;
		for(int i = 0; (1ll << i) <= H; i++)//quickmul
		{
			if(H & (1ll << i))
				ans = ans * u;
			u = u * u;
		}
		long long ret = 0;
		for(int i = 0; i < 7; i++)//enumerate the status of height 1
			if(SAME_COLOR[i] <= k && COLORS[i] <= c)
				ret += (long long)arrange(c, COLORS[i]) * TYPES[i] % MOD * ans[i * (k + 1) + k - SAME_COLOR[i]][Matrix::n - 1] % MOD;
		return (int)(ret % MOD);
	}
};

