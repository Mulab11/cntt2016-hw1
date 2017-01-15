#include <bits/stdc++.h>

using namespace std;

class LittleElephantAndBalls
{
public:
	int p[55],tot;

	int calc(int pos)
	{
		int ap = 0,bp = 0,tmp = 0;
		for(int i = 0;i < pos;i ++)
			if (!(ap & (1 << p[i]))) tmp ++,ap |= (1 << p[i]);
		for(int i = pos;i < tot;i ++)
			if (!(bp & (1 << p[i]))) tmp ++,bp |= (1 << p[i]);
		return tmp;
	}

	int getNumber(string S)
	{
		tot = 0;
		int ans = 0;
		for(auto cur : S)
		{
			int mx = 0,w = 0;
			for(int i = 0;i <= tot;i ++) //just put the char greedily,everything is symmetric
			{
				int v = calc(i);
				if (v > mx) mx = v,w = i;
			}
			ans += mx;
			for(int i = tot;i > w;i --) p[i] = p[i - 1]; //insert the char this place,move the chars.
			p[w] = (cur == 'R') ? 0 : (cur == 'B') ? 1 : 2;
			++ tot; 
		}
		return ans;
	}
};
