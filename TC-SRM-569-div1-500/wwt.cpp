#include <bits/stdc++.h>

using namespace std;

class TheJediTest
{
public:
	int minimumSupervisors(vector <int> s, int K)
	{
		int ans = 0;
		for(int i = 0;i < s.size();i ++) //presume i cannot move people to i - 1
		{
			int rem = (K - s[i] % K) % K; //put another rem people with answer not changed
			ans += (s[i] + K - 1) / K;
			if (i + 1 < s.size()) // move people from i+1 -> i at most rem
			{
				int us = min(s[i + 1],rem);
				s[i + 1] -= us,rem -= us;
			} 
			//people can only move 1 floor
			if (i + 2 < s.size()) //if rem > 0,move all people from i->i+1,then we can move another rem people from i+2->i+1 to fix
			{
				int us = min(s[i + 2],rem);
				s[i + 2] -= us,rem -= us;
			}
		}
		return ans;
	}
};
