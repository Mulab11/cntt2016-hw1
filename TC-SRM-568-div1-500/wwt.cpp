#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 7;

class EqualSums
{
public:
	vector<string> s;
	bool vis[105];
	int n,fixed[105];

	bool test(int now) 
	{
		vis[now] = 1;
		if (now < n) // a row
		{
			bool ok = 1;
			for(int i = 0;i < n;i ++)
				if (s[now][i] != '-')
				{
					int ref = s[now][i] - '0' - fixed[now]; //fixed[i] = ref
					if (ref < 0) return 0;
					if (fixed[i + n] == -1) fixed[i + n] = ref,ok &= test(i + n); else
						if (fixed[i + n] != ref) return 0;
				}
			return ok;
		} else //a column
		{
			now -= n;
			bool ok = 1;
			for(int i = 0;i < n;i ++)
				if (s[i][now] != '-')
				{
					int ref = s[i][now] - '0' - fixed[now + n]; //fixed[i] = ref
					if (ref < 0) return 0;
					if (fixed[i] == -1) fixed[i] = ref,ok &= test(i); else
						if (fixed[i] != ref) return 0;
				}
			return ok;
		}
	}

	int count(vector<string> board)
	{
		s = board;
		n = board.size();
		int zero = 1,non = 1;
		memset(vis,0,sizeof vis);
		for(int i = 0;i < n;i ++) //try to fix the number of every row
			if (!vis[i]) //if it cant be fixed before
			{
				int exist_zero = 0,no_zero = 0;
				for(int ch = 0;ch < 10;ch ++)
				{
					memset(fixed,255,sizeof fixed);
					fixed[i] = ch;
					if (test(i)) 
					{
						if (std::count(fixed,fixed + n,0) > 0) exist_zero ++; else
							no_zero ++; 
					}
				}
				zero = zero * 1ll * (exist_zero + no_zero) % mo;
				non = non * 1ll * no_zero % mo;
			}
		return (zero - non + mo) % mo; //we must assume that there is at least one row which is fixed with zero.
	}
};
