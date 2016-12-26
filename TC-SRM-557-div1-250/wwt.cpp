/*
枚举左端点在哪里。设左端点的数为x，可以解出左右两边合法时x的范围，判断是否有交即可。
*/
#include <bits/stdc++.h>

using namespace std;

class FoxAndMountainEasy
{
public:
	string possible(int n, int h0, int hn, string history)
	{
		int delta = 0,lim = 0;
		for(int i = 0;i < history.size();i ++)
		{
			if (history[i] == 'U') ++ delta; else
				-- delta;
			lim = max(lim, -delta);
		}
		for(int i = 0;i + history.length() <= n;i ++)
		{
			int l1 = i,r1 = n - (i + history.length());
			int sig = (h0 & 1) ^ (l1 & 1);
			int LIM = (lim - sig + 1) / 2,l,r;
			l = max(LIM,(h0 - l1 - sig + 1) / 2),r = (h0 + l1 - sig) / 2;//左边合法时x的范围
			if ((sig ^ (abs(delta) & 1)) != (hn & 1) ^ (r1 & 1)) continue; //奇偶性要相同才可能合法
			int nl = (hn - r1 - delta - sig + 1) / 2,nr = (hn + r1 - delta - sig) / 2;//右边合法时x的范围
			if (r < nl || l > nr || l > r || nl > nr) continue;
			return "YES";	
		}
		return "NO";
	}
};
