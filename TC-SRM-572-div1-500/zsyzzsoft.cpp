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
		for(int i = 0; i < m; i++) //不符合条件 
		{
			if(match[i] < 0 || match[i] > n - depth)
				return;
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
		for(int i = 0; i < 10; i++) //枚举 
		{
			cur[depth] = i + '0';
			for(auto it = pos[depth][i].begin(); it != pos[depth][i].end(); ++it)
				match[*it]--;
			Dfs(depth + 1);
			for(auto it = pos[depth][i].begin(); it != pos[depth][i].end(); ++it)
				match[*it]++;
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
