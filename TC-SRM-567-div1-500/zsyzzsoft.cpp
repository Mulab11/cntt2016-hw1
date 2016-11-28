#include <algorithm>
using namespace std;
int cnt[50][26];
class StringGame
{
public:
	int n, m;
	bool Check(int x)
	{
		bool win[50] = {0};
		win[x] = true;
		for(int t = 0; t < 26; t++) //进行足够的比较轮次 
		{
			for(int i = 0; i < 26; i++)
			{
				bool flag = true;
				for(int j = 0; j < n && flag; j++)
					flag &= win[j] || cnt[j][i] <= cnt[x][i];
				if(flag) //每次任意选择一个不败的字母进行比较即可 
				{
					for(int j = 0; j < n; j++)
					{
						if(!win[j] && cnt[j][i] < cnt[x][i])
							win[j] = true;
					}
				}
			}
		}
		for(int i = 0; i < n; i++)
		{
			if(!win[i])
				return false;
		}
		return true;
	}
	vector<int> getWinningStrings(vector<string> str)
	{
		n = str.size(), m = str[0].length();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				cnt[i][(int)str[i][j] - 'a']++;
		}
		vector<int> ans;
		for(int i = 0; i < n; i++)
		{
			if(Check(i))
				ans.push_back(i);
		}
		return ans;
	}
};
