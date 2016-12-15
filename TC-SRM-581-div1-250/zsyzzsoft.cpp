#include <algorithm>
using namespace std;
vector<int> seg[51];
int ans[50], tot[51];
class SurveillanceSystem
{
public:
	string getContainerInfo(string s, vector<int> reports, int l)
	{
		int n = s.length();
		for(int i = 0; i + l <= n; i++) //找出每种数量上的所有区间 
		{
			int cnt = 0;
			for(int j = i; j < i + l; j++)
				cnt += s[j] == 'X';
			seg[cnt].push_back(i);
		}
		for(int i = 0; i < reports.size(); i++) //统计每种数量上的所需区间数 
			tot[reports[i]]++;
		for(int i = 0; i <= 50; i++)
		{
			if(tot[i] > 0)
			{
				for(int j = 0; j < n; j++)
				{
					int cnt = 0;
					for(int k = 0; k < seg[i].size(); k++)
						cnt += j >= seg[i][k] && j < seg[i][k] + l;
					if(cnt) //可能被监测到 
						ans[j] = max(ans[j], 1);
					if(cnt + tot[i] > seg[i].size()) //超过了区间总数，一定被监测到 
						ans[j] = max(ans[j], 2);
				}
			}
		}
		string ret;
		for(int i = 0; i < n; i++)
		{
			if(ans[i] == 1)
				ret += '?';
			else if(ans[i] == 2)
				ret += '+';
			else
				ret += '-';
		}
		return ret;
	}
};