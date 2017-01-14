#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class TeamContest
{
	public:
	deque<int> Q;
	int worstRank(vector<int> strength)
	{
		int yours=max(max(strength[0],strength[1]),strength[2])
						+min(min(strength[0],strength[1]),strength[2]);
		for(int i=3;i<strength.size();i++)
			Q.push_back(strength[i]);
		sort(Q.begin(),Q.end());//Sort the participator's strength in increasing order. 
		int ans=1;
		while(Q.size()>=3)
		{
			//The current strongest participator must be in a team.
			int mx=Q.back();
			Q.pop_back();
			while(Q.size()>=2&&Q.front()+mx<=yours)//Find the least strong participator valid.
				Q.pop_front();
			if(Q.size()>=2)//The medium team member does not influence the team's strength, so we pick the weakest one. 
			{
				Q.pop_front();
				Q.pop_front();
				ans++;
			}
			else break;
		}
		return ans;
	}
};

