#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <queue>
using namespace std;
class NewArenaPassword
{
private:
	int bucket[26];
public:
	int minChange(string oldPassword, int K)
	{
		int n = oldPassword.size();
		int ans = 0;
		for(int i = 0; i < K && i < n - K; i++)
		{
			memset(bucket, 0, sizeof(bucket));
			for(int j = i; j < n; j += n - K)
				if(j < K || j >= n - K)
					bucket[oldPassword[j] - 'a']++, ans++;
			int now = 0;
			for(int j = 0; j < 26; j++)//find the best letter to change to
				if(bucket[j] > now)
					now = bucket[j];
			ans -= now;//these don't need to change
		}
		return ans;
	}
};

