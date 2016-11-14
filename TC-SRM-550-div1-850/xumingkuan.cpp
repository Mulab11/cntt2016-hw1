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
const int MOD = 1000000007;
class Matrix
{
	public:
		static const int MAXN = 80;
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
		Matrix operator *(const Matrix &b) const
		{
			Matrix c;
			for(int i = 0; i < n; i++)
			{
				int *tmp1 = c[i];
				const int *tmp2 = a[i];
				for(int j = 0; j < n; j++)
				{
					const long long tmp3 = tmp2[j];
					const int *tmp4 = b[j];
					for(int k = 0; k < n; k++)
						tmp1[k] = (tmp1[k] + tmp3 * tmp4[k]) % MOD;
				}
			}
			return c;
		}
		Matrix operator +(const Matrix &b) const
		{
			Matrix c;
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					c[i][j] = (a[i][j] + b[i][j]) % MOD;
			return c;
		}
		void print() const
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					printf("%d ", a[i][j]);
				printf("\n");
			}
		}
}u[40], u3, ans, I;
int Matrix::n = MAXN;//initialize
map <pair <int, int>, int> mp;
Matrix quickmul(int x)//u^x
{
	Matrix ret = I;
	for(int i = 0; (1 << i) <= x; i++)
		if((x >> i) & 1)
			ret = ret * u[i];
	return ret;
}
void solve(int x)//u^0 + u^3 + u^6 + ... + u^(3x)
{
	if(!x)
	{
		ans = I;
		return;
	}
	if(x == 1)
	{
		ans = I + u3;
		return;
	}
	solve((x - 1) / 2);
	ans = ans * quickmul((x / 2 + 1) * 3) + (x & 1 ? ans : ans * u3 + I);
}
class ConversionMachine
{
	public:
	int countAll(string word1, string word2, vector<int> costs, int maxCost)
	{
		const int n = word1.size();
		int cnt = 0;
		memset(u[0].a, 0, sizeof(u[0].a));
		for(int i = 0; i <= n; i++)
			for(int j = 0; i + j <= n; j++)
				mp[make_pair(i, j)] = cnt++;//i 'a', j 'b'
		u[0].n = cnt;//matrix size
		for(int i = 1; i <= n; i++)
			for(int j = 0; i + j <= n; j++)
				u[0][mp[make_pair(i, j)]][mp[make_pair(i - 1, j + 1)]] += i;//convert 'a' to 'b'
		for(int i = 0; i <= n; i++)
			for(int j = 1; i + j <= n; j++)
				u[0][mp[make_pair(i, j)]][mp[make_pair(i, j - 1)]] += j;//'b' to 'c'
		for(int i = 0; i < n; i++)
			for(int j = 0; i + j < n; j++)
				u[0][mp[make_pair(i, j)]][mp[make_pair(i + 1, j)]] += n - i - j;//'c' to 'a'
		for(int i = 1; i <= 30; i++)
			u[i] = u[i - 1] * u[i - 1];//initialize for quickmul
		u3 = u[1] * u[0];
		for(int i = 0; i < I.n; i++)
			I[i][i] = 1;
		int move = 0;
		pair <int, int> st(0, 0);
		for(int i = 0; i < n; i++)
		{
			int tmp = 0;
			while(word1[i] != word2[i])
			{
				if((maxCost -= costs[word1[i] - 'a']) < 0)//impossible to convert
					return 0;
				word1[i] = (word1[i] - 'a' + 1) % 3 + 'a';
				move++;
				tmp++;
			}
			//imagine word2 is "ccc...c", then what word1 will be?
			//(since we subtracted necessary costs, 'a' -> 'b' or 'b' -> 'c' won't matter)
			if(tmp == 1)
				st.second++;
			else if(tmp == 2)
				st.first++;
		}
		int extra = maxCost / ((long long)costs[0] + costs[1] + costs[2]);
		//now answer = (st ---move--> ed) + (st ---(move+3)--> ed) + (st ---(move+6)--> ed) + ... + (st ---(move+3*extra)--> ed).
		solve(extra);
		ans = ans * quickmul(move);
		return ans[mp[st]][0];
	}
};

