#include <bits/stdc++.h>

using namespace std;

class FoxAndMp3
{
public:
	int N;
	vector<string> ans;

	void dfs(long long now)
	{
		if (now > N || ans.size() == 50) return; //we get the string in lexicographic order
		if (now)
		{
			string tmp = "";
			static int ch[55];
			int co = 0;
			for(int c = now;c;c /= 10) ch[++ co] = c % 10;
			for(;co;co --) tmp = tmp + char(ch[co] + '0');
			ans.push_back(tmp + ".mp3");
		}
		for(int c = (now == 0);c < 10;c ++) //append a new char
			dfs(now * 10 + c);
	}

	vector<string> playList(int n)
	{
		N = n;
		ans.clear();
		dfs(0);
		return ans;
	}
};
