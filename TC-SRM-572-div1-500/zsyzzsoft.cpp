#include <algorithm>
using namespace std;
class EllysBulls
{
public:
	int n, m, match[50];
	char cur[11], ans[11];
	vector<int> pos[10][10];
	void Dfs(int depth)
	{
		int rest = 0;
		for(int i = 0; i < m; i++) //不符合条件 
		{
			if(match[i] < 0 || match[i] > n - depth)
				return;
			rest += match[i];
		}
		if(depth == n)
		{
			if(ans[0])
				ans[0] = -1; //多组解 
			else
			{
				for(int i = 0; i < n; i++)
					ans[i] = cur[i];
			}
			return;
		}
		for(int i = 0, flag = 0; i < 10; i++) //枚举 
		{
			if(flag && !pos[depth][i].size()) //都不匹配的不用枚举第二次 
			{
				if(flag == 2) //但要注意多组解的情况 
					ans[0] = -1;
				continue;
			}
			cur[depth] = i + '0';
			for(auto it = pos[depth][i].begin(); it != pos[depth][i].end(); ++it)
				match[*it]--;
			if(!pos[depth][i].size())
				flag = ans[0] == 0 ? 2 : 1;
			Dfs(depth + 1);
			for(auto it = pos[depth][i].begin(); it != pos[depth][i].end(); ++it)
				match[*it]++;
			if(!pos[depth][i].size() && flag == 2 && ans[0] == 0)
				flag = 1;
		}
	}
	string getNumber(vector<string> guesses, vector<int> bulls)
	{
		m = bulls.size(), n = guesses[0].length();
		for(int i = 0; i < m; i++)
			match[i] = bulls[i];
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
				pos[j][guesses[i][j] - '0'].push_back(i);
		}
		Dfs(0);
		if(!ans[0])
			return "Liar";
		if(ans[0] == -1)
			return "Ambiguity";
		return ans;
	}
};