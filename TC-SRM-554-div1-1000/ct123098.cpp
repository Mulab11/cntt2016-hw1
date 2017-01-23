#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MOD = 1234567891;
const long long MOD2 = (long long)MOD * MOD;
const int MAXS = 50;
const int SIZE = 150;

class TheBrickTowerHardDivOne
{
	public:

	struct Matrix
	{
		int n, m;
		int v[SIZE][SIZE];
		Matrix(int _n = 0, int _m = 0) : n(_n), m(_m)
		{
			memset(v, 0, sizeof(v));
		}
		
		Matrix operator * (const Matrix &a) const
		{
			Matrix ret(n, a.m);
			for(int i = 1; i <= ret.n; i++)
				for(int j = 1; j <= ret.m; j++)
				{
					long long tmp = 0;
					for(int k = 1; k <= m; k++)
					{
						tmp += (long long)v[i][k] * a.v[k][j];
						if(tmp >= MOD2) tmp -= MOD2;
					}
					ret.v[i][j] = tmp % MOD;
				}
			return ret;
		}
		
		Matrix mulPow(const Matrix &a, long long p) const
		{
			static Matrix M[64];
			M[0] = a;
			Matrix ret = *this;
			for(int i = 1; i < 64; i++)
				M[i] = M[i - 1] * M[i - 1];
			int t = 0;
			while(p)
			{
				if(p & 1) ret = M[t] * ret;
				p /= 2, t++;
			}
			return ret;
		}
		
		void print()
		{
			cout << n << ' ' << m << endl;
			for(int i = 1; i <= n; i++)
			{
				for(int j = 1; j <= m; j++)
					cout << v[i][j] << ' ';
				cout << endl;
			}
		}
	};

	int getA(int n, int m)
	{
		if(n < 0 || m < 0 || m > n) return 0;
		long long ret = 1;
		for(int i = 1; i <= m; i++)
			ret = ret * (n - i + 1) % MOD;
		return ret;
	}

	int tots, col[MAXS][4], cnum[MAXS], pairs[MAXS];
	int ccol[5], used[5];

	void check()
	{
		++tots;
		for(int i = 0; i < 4; i++)
			col[tots][i] = ccol[i];
	}

	void search(int h, int cmax)
	{
		if(h == 4)
			return check();
		ccol[h] = cmax + 1, search(h + 1, cmax + 1), ccol[h] = 0;
		for(int i = 1; i <= cmax; i++)
			ccol[h] = i, search(h + 1, cmax), ccol[h] = 0;
	}

	void init()
	{
		tots = 0;
		search(0, 0);
		for(int i = 1; i <= tots; i++)
		{
			cnum[i] = pairs[i] = 0;
			for(int j = 0; j < 4; j++)
				cnum[i] = max(cnum[i], col[i][j]), pairs[i] += (col[i][j] == col[i][(j + 1) % 4]);
		}
	}

	int C, K;
	long long H;
	Matrix I, T;

	int getId(int i, int j)
	{
		return (i - 1) * (K + 1) + j + 1;
	}

	int getSize()
	{
		return getId(tots, K) + 1;
	}

	void calc(int x, int y)
	{
		int cnt = pairs[y], cho = 0;
		long long tmp = 0;
		for(int i = 0; i < 4; i++)
			cnt += col[x][i] == ccol[col[y][i]];
		for(int i = 1; i <= cnum[y]; i++)
			cho += ccol[i] == 0;
		tmp = getA(C - cnum[x], cho);
		for(int i = 0; i <= K - cnt; i++)
			T.v[getId(y, i + cnt)][getId(x, i)] = (T.v[getId(y, i + cnt)][getId(x, i)] + tmp) % MOD;
	}

	void search2(int h, int x, int y)
	{
		if(h == cnum[y] + 1)
			return calc(x, y);
			
		search2(h + 1, x, y);
		for(int i = 1; i <= cnum[x]; i++)
			if(!used[i])
			{
				ccol[h] = i, used[i] = true;
				search2(h + 1, x, y);
				ccol[h] = 0, used[i] = false;
			}
	}


	int find(int C, int K, long long H)
	{
		init();
		this->C = C, this->K = K, this->H = H;
		
		T = Matrix(getSize(), getSize());
		for(int x = 1; x <= tots; x++)
			for(int y = 1; y <= tots; y++)
				search2(1, x, y);
		for(int i = 1; i <= getSize(); i++)
			T.v[getSize()][i] = 1;
	//  T.print();
		
		I = Matrix(getSize(), 1);
		for(int i = 1; i <= tots; i++)
			if(pairs[i] <= K)
				I.v[getId(i, pairs[i])][1] = getA(C, cnum[i]);
		
		return I.mulPow(T, H).v[getSize()][1];
	}
};

