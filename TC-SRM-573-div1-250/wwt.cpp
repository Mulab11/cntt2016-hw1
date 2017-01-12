#include <bits/stdc++.h>

using namespace std;

class TeamContest
{
public:
	int worstRank(vector <int> s)
	{
		int v = max(s[0],max(s[1],s[2])) + min(s[0],min(s[1],s[2])); //my team's value
		vector<int> strength;
		for(int i = 3;i < s.size();i ++) strength.push_back(s[i]);
		sort(strength.begin(),strength.end());
		reverse(strength.begin(),strength.end());
		int r = 1;
		static int use[1005];
		memset(use,0,sizeof use);
		for(int i = 0;i < strength.size();i ++) //greedy work from largest to smallest
			if (use[i]) continue; else
			{
				//greedy
				use[i] = 1;
				int j;
				for(j = i + 1;use[j];++ j);
				int nj = j + 1;
				for(;use[nj];++ nj);
				int cv = strength[i],bk;
				for(bk = strength.size() - 1;use[bk];-- bk);
				if (cv + strength[nj] <= v) //if the largest value that this team can chieve is smaller than my team's,we choose the smallest another two.
				{
					use[bk] = 1;
					for(bk = bk - 1;use[bk];-- bk);
					use[bk] = 1;
				} else //find the smallest that can help us achieve 
				{
					for(int k = nj;k < strength.size();k ++)
						if (!use[k] && cv + strength[k] > v) nj = k;
					for(j = nj - 1;use[j];-- j);
					use[j] = use[nj] = 1;
					++ r;
				}
			}
		return r;
	}
};
