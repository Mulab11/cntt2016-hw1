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

class ICPCBalloons
{
public:
	int n;
	int sum1, sum2;
	int ans;
	vector<int> col1, col2;
	vector<int> v1, v2;
	
	int minRepaintings(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted)
	{	
		for(int i = 0; i < balloonCount.size(); i++)
			if(balloonSize[i] == 'M')
				col1.push_back(balloonCount[i]);
			else
				col2.push_back(balloonCount[i]);
		sort(col1.begin(), col1.end(), greater<int>());
		sort(col2.begin(), col2.end(), greater<int>());
		sum1 = sum2 = 0;
		for(int i = 0; i < col1.size(); i++) sum1 += col1[i];
		for(int i = 0; i < col2.size(); i++) sum2 += col2[i];
		
		ans = 0x1f1f1f1f;
		n = maxAccepted.size();
		for(int i = 0; i < (1 << n); i++)
		{
			v1.clear(), v2.clear();
			for(int j = 0; j < n; j++)
				if(i & (1 << j))
					v1.push_back(maxAccepted[j]);
				else
					v2.push_back(maxAccepted[j]);
			sort(v1.begin(), v1.end(), greater<int>());
			sort(v2.begin(), v2.end(), greater<int>());
			int tmp1 = 0, tmp2 = 0;
			for(int j = 0; j < v1.size(); j++) tmp1 += v1[j];
			for(int j = 0; j < v2.size(); j++) tmp2 += v2[j];
			if(tmp1 > sum1 || tmp2 > sum2)
				continue;
//			cout << tmp1 << ' ' << tmp2 << endl;
			int cur = 0;
			for(int j = 0; j < v1.size(); j++)
			{
				int cnt = j < col1.size() ? col1[j] : 0;
				cur += max(0, v1[j] - cnt);
			}
			for(int j = 0; j < v2.size(); j++)
			{
				int cnt = j < col2.size() ? col2[j] : 0;
				cur += max(0, v2[j] - cnt);
			}
			ans = min(ans, cur);
		}
		if(ans == 0x1f1f1f1f) ans = -1;
		return ans;
	}
};

