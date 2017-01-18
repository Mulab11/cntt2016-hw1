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

class XorCards
{
private:
	int maxdigit;
	bool used[55];
public:
	long long numberOfWays(vector<long long> number, long long limit)
	{
		bool flag = false;
		for(maxdigit = -1; !flag; maxdigit++)
			for(int i = !(flag = true); i < number.size() && flag; i++)
				flag = (number[i] < (1ll << (maxdigit + 2)));
		if(++limit >= (1ll << (maxdigit + 1)))//++limit => xor sum < limit; if(...) => we can select any subset
			return 1ll << number.size();
		long long ans = 0, chosen = 0;
		memset(used, false, sizeof(used));
		int now = number.size();
		for(int i = maxdigit; i >= 0; i--)//enum the digit where xor sum < limit
		{
//			printf("%d %d\n", i, now);
			int place;
			for(place = 0; place < number.size(); place++)
				if(!used[place] && ((number[place] >> i) & 1))
					break;
			if(place == number.size())
			{
				if(((limit >> i) & 1) > ((chosen >> i) & 1))
				{
					ans += (1ll << now);
					break;
				}
				else if(((limit >> i) & 1) < ((chosen >> i) & 1))
					break;
				continue;
			}
			if(((limit >> i) & 1) != ((chosen >> i) & 1))
				chosen ^= number[place];
			used[place] = true;
			now--;
			for(int j = place + 1; j < number.size(); j++)
				if(!used[j] && ((number[j] >> i) & 1))
					number[j] ^= number[place];
			if((limit >> i) & 1)
				ans += (1ll << now);//digits (i, maxdigit] of xor sum are same as 'limit'; digit 'i' = 0; there's no restriction on digits [0, i)
//			printf("%d %d %I64d %I64d %I64d\n", i, now, ans, chosen, limit);
//			printf("number:");
//			for(int j = 0; j < number.size(); j++)
//				if(!used[j])
//					printf(" %I64d", number[j]);
//			printf("\n");
		}
		return ans;
	}
};

