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
#include <numeric>
using namespace std;

class ICPCBalloons
{
	private:
	int n;//number of problems
	vector <int> balloon[2];//medium, large
	int sum[2];//medium, large
	public:
	int minRepaintings(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted)
	{
		n = maxAccepted.size();
		balloon[0].clear();
		balloon[1].clear();
		for(int i = 0; i < balloonSize.size(); i++)
			balloon[balloonSize[i] == 'L'].push_back(balloonCount[i]);
		sort(balloon[0].begin(), balloon[0].end(), greater <int> ());
		sort(balloon[1].begin(), balloon[1].end(), greater <int> ());
		sort(maxAccepted.begin(), maxAccepted.end(), greater <int> ());//sort balloons and problems in descending order
		sum[0] = accumulate(balloon[0].begin(), balloon[0].end(), 0);
		sum[1] = accumulate(balloon[1].begin(), balloon[1].end(), 0);
		int ans = 10101010;
		for(int i = 0; i < (1 << n); i++)
		{
			int type, notpaint = 0, cnt[2] = {0, 0}, nowsum[2] = {0, 0};//medium, large
			for(int j = 0; j < n; j++)
			{
				nowsum[type = ((i >> j) & 1)] += maxAccepted[j];
				if(cnt[type] < balloon[type].size())
					notpaint += min(balloon[type][cnt[type]++], maxAccepted[j]);//greedy.
			}
			if(nowsum[0] <= sum[0] && nowsum[1] <= sum[1] && nowsum[0] + nowsum[1] - notpaint < ans)
				ans = nowsum[0] + nowsum[1] - notpaint;
		}
		return ans == 10101010 ? -1 : ans;
	}
};

