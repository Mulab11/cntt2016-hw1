#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;

class SpaceWarDiv1
{
private:
	int n, m;
	vector<pair<int, long long> > enemy;//<strength, count>
public:
	long long minimalFatigue(vector<int> magicalGirlStrength, vector<int> enemyStrength, vector<long long> enemyCount)
	{
		n = magicalGirlStrength.size();
		sort(magicalGirlStrength.begin(), magicalGirlStrength.end());
		magicalGirlStrength.insert(magicalGirlStrength.begin(), 0);//adding a magical girl with strength 0 will not change the answer
		enemy.resize(m = enemyStrength.size());
		for(int i = 0; i < m; i++)
			enemy[i] = make_pair(enemyStrength[i], enemyCount[i]);
		sort(enemy.begin(), enemy.end());
		if(magicalGirlStrength[n] < enemy[m - 1].first)//None of the magical girls can defeat the enemy with max strength
			return -1;
		long long ans = 0, cnt = 0;//count the enemy which magical girl 0~i can't defeat
		int ptr = m - 1;
		for(int i = n - 1; i >= 0; i--)
		{
			while(ptr >= 0 && magicalGirlStrength[i] < enemy[ptr].first)//magical girl 0~i can't defeat enemy ptr (only n-i girls can defeat)
				cnt += enemy[ptr--].second;
			ans = max(ans, (cnt - 1) / (n - i) + 1);//ceil(cnt / (n - i))
		}
		return ans;
	}
};

