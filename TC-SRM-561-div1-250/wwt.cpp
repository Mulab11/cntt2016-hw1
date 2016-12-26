/*
可以发现，假如只有一种size的气球，那么肯定是过的人多的题配数量多的气球，并且代价就是\sum_{i} max(0,accept(i)-count(i))
（当然，不合法的情况要判掉）。现在有两种size，那么我们可以dp。设f[i][j][k][s]表示枚举到第i道题，size 1用到第j种，
size 2用到第k种，s表示有s数量放到了size 1里（这是用来判不合法的）。转移就枚举放哪个size就好了。
*/
#include <bits/stdc++.h>

using namespace std;

class ICPCBalloons
{
public:
	void update(int &a,int b)
	{
		if (b < a) a = b;
	}

	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
	{
		vector<int> ta,tb;
		ta.clear(),tb.clear();
		for(int i = 0;i < balloonCount.size();i ++)
			if (balloonSize[i] == 'L') ta.push_back(balloonCount[i]); else
				tb.push_back(balloonCount[i]);
		for(;ta.size() < maxAccepted.size();) ta.push_back(0);
		for(;tb.size() < maxAccepted.size();) tb.push_back(0); //补0
		sort(ta.begin(),ta.end());
		sort(tb.begin(),tb.end());
		sort(maxAccepted.begin(),maxAccepted.end());
		reverse(ta.begin(),ta.end()),reverse(tb.begin(),tb.end()),reverse(maxAccepted.begin(),maxAccepted.end());//从大到小放
		static int f[2][52][52][1505];
		memset(f,60,sizeof f);
		int inf = f[0][0][0][0],sum = 0,cr = 0;
		f[0][0][0][0] = 0;
		for(int i = 0;i < maxAccepted.size();i ++)
		{
			cr ^= 1;
			int v = maxAccepted[i];
			memset(f[cr],60,sizeof f[cr]);
			for(int j = 0;j <= ta.size();j ++)
				for(int k = 0;k <= tb.size();k ++)
					for(int s = 0;s <= sum;s ++)
						if (f[cr ^ 1][j][k][s] != inf)
						{
							int val = f[cr ^ 1][j][k][s];
							if (j < ta.size()) //选择size 1
							{
								update(f[cr][j + 1][k][s + v],val + max(0,v - ta[j]));
							}
							if (k < tb.size()) //选择size 2
							{
								update(f[cr][j][k + 1][s],val + max(0,v - tb[k]));
							}
						}
			sum += v;
		}
		int ans = inf,sa = 0,sb = 0;
		for(int j = 0;j < ta.size();j ++) sa += ta[j];
		for(int j = 0;j < tb.size();j ++) sb += tb[j];
		for(int j = 0;j <= ta.size();j ++)
			for(int k = 0;k <= tb.size();k ++)
				for(int s = 0;s <= sum;s ++)
					if (s <= sa && sum - s <= sb) update(ans,f[cr][j][k][s]); //可以匹配
		if (ans == inf) return -1;
		return ans; 
	}
};
