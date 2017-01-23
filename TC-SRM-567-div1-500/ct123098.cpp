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

const int MAXN = 50 + 10;

class StringGame
{
	public:
	int n;
	int s[MAXN][26];
	bool used[26], ok[MAXN];
	vector<int> ans;
	
	bool search(int x, int h)
	{
		if(h >= 26)
		{
			for(int i = 1; i <= n; i++)
				if(!ok[i])
					return false;
			return true;
		}
		for(int i = 0; i < 26; i++)
			if(!used[i])
			{
				bool flag = true;
				for(int j = 1; j <= n; j++)
					if(!ok[j] && s[x][i] < s[j][i])
						flag = false;
						
				if(!flag) continue;
//				cout << x << ' ' << i << endl;
				
				for(int j = 1; j <= n; j++)
					if(!ok[j] && s[x][i] > s[j][i])
						ok[j] = true;
				used[i] = true;
				
				return search(x, h + 1);
			}
		return false;
	}
	
	vector<int> getWinningStrings(vector<string> S)
	{
		n = S.size();
		for(int i = 1; i <= n; i++)
			for(int j = 0; j < S[i - 1].size(); j++)
				s[i][S[i - 1][j] - 'a']++;
		
		for(int i = 1; i <= n; i++)
		{
			memset(used, 0, sizeof(used));
			memset(ok, 0, sizeof(ok));
			ok[i] = true;
			if(search(i, 0))
				ans.push_back(i - 1);
		}
		
		return ans;
	}
};

