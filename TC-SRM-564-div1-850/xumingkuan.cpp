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
long long quickmul(int a, int b)
{
	if(b <= 1)
		return b ? a : 1;
	long long tmp = quickmul(a, b >> 1);
	tmp = tmp * tmp % MOD;
	return b & 1 ? tmp * a % MOD : tmp;
}
class DefectiveAddition
{
	private:
	int f[60];//f(j)(i)[k]: choose k cards of the first i cards of (1 << j)
	public:
	int count(vector<int> cards, int n)
	{
		int ans = 0;
		for(int i = 0; i < cards.size(); i++)
			ans ^= cards[i];
		ans = (ans == n);//if(xorsum(cards) == n) ans++;
		for(int j = 29; j >= 0; j--)
		{
			int now = 1;
			memset(f, 0, sizeof(f));
			f[0] = 1;
			int cntj = 0;
			for(int i = 0; i < cards.size(); i++)
				if(cards[i] >= (1 << j))
				{
					cards[i] ^= (1 << j);
					for(int k = ++cntj; k >= 0; k--)
						f[k] = ((long long)f[k] * (1 << j) + (k ? (long long)f[k - 1] * (cards[i] + 1) : 0)) % MOD;
				}
				else
					now = (long long)now * (cards[i] + 1) % MOD;
			long long now2 = 0;
			for(int i = ((n >> j) & 1); i < cntj; i += 2)
				now2 += f[i];
			ans = (ans + now2 % MOD * now % MOD * quickmul(1 << j, MOD - 2)) % MOD;
			if((cntj & 1) != ((n >> j) & 1))
				break;
		}
		return ans;
	}
};

