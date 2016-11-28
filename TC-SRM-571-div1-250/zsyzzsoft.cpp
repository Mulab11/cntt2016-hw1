#include <algorithm>
using namespace std;
class FoxAndMp3
{
public:
	vector<string> ans;
	void Dfs(int x, int n)
	{
		if(ans.size() == 50 || x > n)
			return;
		char s[20];
		sprintf(s, "%d.mp3", x);
		ans.push_back(s);
		for(int i = 0; i <= 9; i++)
			Dfs(x * 10 + i, n);
	}
	vector<string> playList(int n)
	{
		for(int i = 1; i <= 9; i++) //首位 
			Dfs(i, n);
		return ans;
	}
};
