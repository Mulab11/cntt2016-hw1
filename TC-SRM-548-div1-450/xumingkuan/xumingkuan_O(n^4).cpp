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

using namespace std;
const int MAXN = 54;
class KingdomAndDice
{
private:
	int n, num, tot;
	int choice[MAXN];
	int f[MAXN][MAXN * MAXN];//f[i][j]: choice 1~i, total j, min numbers
public:
	double newFairness(vector<int> firstDie, vector<int> secondDie, int X)
	{
		n = firstDie.size();
		sort(firstDie.begin(), firstDie.end());
		sort(secondDie.begin(), secondDie.end());
		tot = 0;
		memset(choice, 0, sizeof(choice));
		int zz = 0, last = 0;
		while(zz < n && !firstDie[zz])
			zz++;
		num = zz;
		for(int i = 0; i < n; i++)
		{
			while(zz < n && firstDie[zz] < secondDie[i])
				zz++, last++;
			tot += n - zz;
			choice[i] = secondDie[i] - last - 1;
			last = secondDie[i];
		}
		last += n - zz;
		choice[n] = X - last;
		if(tot >= n * n / 2/*firstDie has too large numbers, fill zero*/ || !num/*nothing to fill*/)
			return (double)tot / (n * n);
		memset(f, 31, sizeof(f));
		f[0][tot] = 0;
		for(int i = 1; i <= n; i++)
			for(int j = tot; j <= n * n; j++)
				if(f[i - 1][j] <= num)
					for(int k = 0; k <= choice[i] && k + f[i - 1][j] <= num; k++)
						f[i][j + k * i] = min(f[i][j + k * i], f[i - 1][j] + k);
		for(int j = 0; true; j++)
		{
			if(f[n][(n * n) / 2 - j] <= num)
				return (double)((n * n) / 2 - j) / (n * n);
			if(f[n][(n * n + 1) / 2 + j] <= num)
				return (double)((n * n + 1) / 2 + j) / (n * n);
		}
	}
};

