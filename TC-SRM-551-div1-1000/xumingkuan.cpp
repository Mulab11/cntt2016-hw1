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
const int MOD = 1000000007, MAXN = 42, MAXM = 1050505;
class SweetFruits
{
	private:
	int n, C[MAXN][MAXN], numSweet, sweet[MAXN], lenum, rinum, risum[MAXN];
	int f[MAXN];//i truly sweet fruit, number of trees
	int setsum[MAXN];//i truly sweet fruit, number of arrangements
	pair <int, int> le[MAXM], ri[MAXM];
	long long a[MAXN][MAXN];
	int x[MAXN];
	long long quickmul(long long a, int b)
	{
		if(b == 1)
			return b == 1 ? a : 1;
		long long tmp = quickmul(a, b / 2);
		tmp = tmp * tmp % MOD;
		return b & 1 ? tmp * a % MOD : tmp;
	}
	int solve(int n)
	{
		for(int i = 1; i <= n; i++)
			x[i] = i;
		for(int i = 1; i <= n; i++)
		{
			int now = i;
			while(now <= n && a[x[now]][i] == 0)
				now++;
			if(now > n)
				continue;
			swap(x[i], x[now]);
			long long tmp = quickmul(a[x[i]][i], MOD - 2);
			for(int j = i + 1; j <= n; j++)
				if(a[x[j]][i] != 0)
					for(int k = n; k >= i; k--)
						a[x[j]][k] = (a[x[j]][k] - a[x[i]][k] * tmp % MOD * a[x[j]][i] % MOD + MOD) % MOD;
		}
		int ans = 1;
		for(int i = 1; i <= n; i++)
			ans = ans * a[x[i]][i] % MOD;
		return ans;
	}
	void clear()
	{
		memset(a, 0, sizeof(a));
	}
	void insert(int u, int v)
	{
		a[u][v]--;
		a[v][u]--;
		a[u][u]++;
		a[v][v]++;
	}
	public:
	void init(int n)
	{
		memset(C, 0, sizeof(C));
		for(int i = 0; i <= n; i++)
		{
			C[i][0] = C[i][i] = 1;
			for(int j = 1; j < i; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
	int countTrees(vector<int> sweetness, int maxSweetness)
	{
		n = sweetness.size();
		init(n);
		numSweet = 0;
		for(int i = 0; i < n; i++)
			if(sweetness[i] != -1)
				sweet[numSweet++] = sweetness[i];
		for(int i = 0; i <= numSweet; i++)
		{
			clear();
			for(int j = 1; j <= i; j++)
				for(int k = j + 1; k <= i; k++)//truly sweet -- truly sweet
					insert(j, k);
			for(int j = 1; j <= n; j++)
				for(int k = max(numSweet + 1, j + 1); k <= n; k++)//sweet -- bitter, bitter -- bitter
					insert(j, k);
			f[i] = solve(n - 1);//matrix-tree theorem
			for(int j = 0; j < i; j++)//substract <i truly sweet trees
				f[i] = (f[i] - (long long)C[i][j] * f[j] % MOD + MOD) % MOD;
		}
		//meet-in-the-middle
		lenum = numSweet / 2;
		rinum = numSweet - lenum;
		memset(le, 0, sizeof(le));
		memset(ri, 0, sizeof(ri));
		for(int i = 0; i < (1 << lenum); i++)
			for(int j = 0; j < lenum; j++)
				if((i >> j) & 1)
					le[i].first += sweet[j], le[i].second++;
		for(int i = 0; i < (1 << rinum); i++)
			for(int j = 0; j < rinum; j++)
				if((i >> j) & 1)
					ri[i].first += sweet[j + lenum], ri[i].second++;
		sort(le, le + (1 << lenum));
		sort(ri, ri + (1 << rinum));
		memset(risum, 0, sizeof(risum));
		memset(setsum, 0, sizeof(setsum));
		for(int i = 0; i <= rinum; i++)
			risum[i] = C[rinum][i];
		int pos = (1 << rinum) - 1;
		for(int i = 0; i < (1 << lenum); i++)//two pointers
		{
			while(pos >= 0 && ri[pos].first + le[i].first > maxSweetness)
				risum[ri[pos--].second]--;
			if(pos == -1)
				break;
			for(int k = 0; k <= rinum; k++)
				setsum[le[i].second + k] = (setsum[le[i].second + k] + risum[k]) % MOD;
		}
		int ans = 0;
		for(int i = 0; i <= numSweet; i++)
			ans = (ans + (long long)setsum[i] * f[i]) % MOD;
		return ans;
	}
};

