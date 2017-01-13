#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int MOD = 1000000007;

class TrafficCongestion
{
private:
	int f[1010101], sum[1010101];//f[i]: answer when treeHeight = i; sum[i] = sum(j=0~i)f[j]
public:
	int theMinCars(int treeHeight)
	{
		f[0] = sum[0] = f[1] = 1;
		sum[1] = 2;
		for(int i = 2; i <= treeHeight; i++)//greedy, dp
			sum[i] = (sum[i - 1] + (f[i] = ((sum[i - 2] << 1) + 1) % MOD)) % MOD;
		return f[treeHeight];
	}
};

