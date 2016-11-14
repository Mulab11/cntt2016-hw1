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

using namespace std;

class ColorfulChocolates
{
	private:
	int a[60];
	public:
	int maximumSpread(string chocolates, int maxSwaps)
	{
		int ans = 1;
		for(char ch = 'A'; ch <= 'Z'; ch++)//enumerate spread color
		{
			int num = 0;
			for(int j = 0; j < chocolates.size(); j++)
				if(chocolates[j] == ch)
					a[++num] = j;//get positions
			for(int st = 1; st <= num; st++)//get st-th ~ ed-th chocolate together
				for(int ed = st + ans; ed <= num; ed++)//ed - st + 1 > ans
				{
					int mi = (st + ed) / 2;//do not move mi-th
					int numSwaps = 0;
					for(int i = st; i < mi; i++)
						numSwaps += a[mi] - a[i] - mi + i;
					for(int i = mi + 1; i <= ed; i++)
						numSwaps += a[i] - a[mi] - i + mi;
					if(numSwaps <= maxSwaps)//ok
						ans++;
					else
						break;
				}
		}
		return ans;
	}
};

