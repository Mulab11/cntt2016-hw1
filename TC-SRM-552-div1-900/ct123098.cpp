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

const int MAXN = 1000000;

class HolyNumbers
{
	public:
	long long n;
	int maxP;
	int totp, pri[MAXN];
	void getPrime()
	{
		static bool isp[MAXN];
		memset(isp, true, sizeof(isp));
		isp[0] = isp[1] = false;
		for(int i = 2; i <= maxP; i++)
		{
			if(isp[i])
				pri[++totp] = i;
			for(int j = 1; j <= totp && (long long)i * pri[j] <= maxP; j++)
			{
				isp[i * pri[j]] = false;
				if(i % pri[j] == 0) break;
			}
		}
	}
	
	long long search(int x, long long y)
	{
		if(x > totp || pri[x] > y)
			return 1;
		if((long long)pri[x] * pri[x + 1] > y)
			return upper_bound(pri + x, pri + totp + 1, y) - pri - x + 1;
		long long ret = 0;
		ret += search(x + 1, y);
		for(long long i = pri[x]; i <= y; i *= (long long)pri[x] * pri[x])
			ret += search(x + 1, y / i);
		return ret;
	}
	
	long long count(long long upTo, int maximalPrime)
	{
		n = upTo;
		maxP = maximalPrime;
		
		getPrime();
		long long ans = search(1, n);
		
		return ans;
	}
};

