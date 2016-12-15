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
#include <queue>
using namespace std;
class MonstersValley
{
	private:
	long long f[105];//f[i] = max total scariness reachable by <= i coins.
	public:
	int minimumPrice(vector<long long> dread, vector<int> price)
	{
		memset(f, 0, sizeof(f));
		f[price[0]] = dread[0];
		int minprice = price[0], maxprice = price[0];
		for(int i = 1; i < dread.size(); i++)
		{
			maxprice += price[i];
			for(int j = minprice + 1; j <= maxprice; j++)
				if(f[j] < f[j - 1])
					f[j] = f[j - 1];
			for(int j = maxprice; j >= minprice; j--)
				if(j - price[i] >= minprice && f[j] >= dread[i])//bribe / walk past
					f[j] = max(f[j - price[i]] + dread[i], f[j]);
				else if(j - price[i] >= minprice)//bribe
					f[j] = f[j - price[i]] + dread[i];
				else if(f[j] < dread[i])//can't bribe and can't walk past... must pay more coins
					minprice = j + 1;
		}
		return minprice;
	}
};

