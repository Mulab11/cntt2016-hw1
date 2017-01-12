#include <bits/stdc++.h>

using namespace std;

class UndoHistory
{
public:
	int minPresses(vector<string> lines)
	{
		int ans = lines[0].length() + 1; //for string 0 we must type one by one
		for(int i = 1;i < lines.size();i ++)
		{
			int mincost = (1 << 30);
			for(int j = 0;j < i;j ++) //find a string to make use of 
			{
				int plen = 0;//the lcp
				for(;plen < lines[i].length() && plen < lines[j].length() && lines[i][plen] == lines[j][plen];++ plen);				
				int cur_cost = lines[i].length() - plen + 2 + 1;
				if (j == i - 1 && plen == lines[j].length()) //no need to copy
					cur_cost -= 2;
				mincost = min(mincost,cur_cost);
			}
			ans += mincost;
		}
		return ans;
	}
};
