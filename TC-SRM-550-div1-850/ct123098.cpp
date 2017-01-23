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

const int MOD = 1000000007;
const int SIZE = 12 * 12 + 10;

class ConversionMachine
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
						tmp = (tmp + (long long)v[i][k] * a.v[k][j]) % MOD;
					ret.v[i][j] = tmp;
				}
			return ret;
		}
		
		Matrix mulPow(const Matrix &a, long long p) const
		{
			static Matrix M[32];
			M[0] = a;
			Matrix ret = *this;
			for(int i = 1; i < 32; i++)
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
	
	int n;
	long long cost[3][3], sum;
	long long type1, type2, cnt;
	Matrix F, A;
	
	int getId(int j, int k)
	{
		return j * (n + 1) + k + 1;
	}
	
	int countAll(string word1, string word2, vector<int> costs, int maxCost)
	{
		n = word1.size();
		
		cost[0][0] = cost[1][1] = cost[2][2] = 0;
		cost[0][1] = costs[0], cost[1][2] = costs[1], cost[2][0] = costs[2];
		cost[0][2] = costs[0] + costs[1], cost[1][0] = costs[1] + costs[2], cost[2][1] = costs[2] + costs[0];
		sum = costs[0] + costs[1] + costs[2];
		
		type1 = type2 = 0;
		for(int i = 0; i < n; i++)
		{
			if((word2[i] - word1[i] + 3) % 3 == 1)
				type1++;
			else if((word2[i] - word1[i] + 3) % 3 == 2)
				type2++;
			maxCost -= cost[word1[i] - 'a'][word2[i] - 'a'];
			if(maxCost < 0)
				return 0;
		}
		
		if(maxCost < 0)
			return 0;
		
		cnt = type1 + 2 * type2 + maxCost / sum * 3;
		
		F = Matrix(getId(n, n) + 1, getId(n, n) + 1);
		
		for(int j = 0; j <= n; j++)
			for(int k = 0; j + k <= n; k++)
			{
				if(j - 1 >= 0)
					F.v[getId(j - 1, k)][getId(j, k)] = j;
				if(j + 1 <= n && k - 1 >= 0)
					F.v[getId(j + 1, k - 1)][getId(j, k)] = k;
				if(j + k + 1 <= n)
					F.v[getId(j, k + 1)][getId(j, k)] = n - j - k;
			}
		F.v[getId(n, n) + 1][getId(0, 0)] = 1;
		F.v[getId(n, n) + 1][getId(n, n) + 1] = 1;
		
		A = Matrix(getId(n, n) + 1, 1);
		A.v[getId(type1, type2)][1] = 1;
		
		A = A.mulPow(F, cnt + 1);
		
		return A.v[getId(n, n) + 1][1];
	}
};

