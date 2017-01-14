#include <bits/stdc++.h>

using namespace std;

const int maxn = 15;

class YetAnotherBoardGame
{
public:
	int baks[maxn],s[maxn],n,m;

	int calc(int cols)
	{
		int tmp = 0;
		int els = ((1 << m) - 1) ^ cols;
		for(int i = 1;i < n;i ++)
		{
			//we can infer the status of this row from last row
			s[i] ^= (s[i - 1] >> 1) ^ (s[i - 1] << 1) ^ (cols & s[i - 1]);
			if (i + 1 < n) s[i + 1] ^= s[i - 1];
			if (!((s[i - 1] & cols) == s[i - 1] || (s[i - 1] & els) == s[i - 1])) return (1 << 30);// the type of every cell in a row should be the same
			s[i] &= (1 << m) - 1;
			tmp += __builtin_popcount(s[i - 1]);
		}
		if (s[n - 1]) return (1 << 30); // the final row should be filled with 0
		return tmp;
	}

	int minimumMoves(vector<string> board)
	{
		n = board.size(),m = board[0].length();
		for(int i = 0;i < n;i ++)
		{
			baks[i] = 0;
			for(int j = 0;j < m;j ++)
				if (board[i][j] == 'W') baks[i] |= (1 << j); //B:0,W:1
		}
		int ans = (1 << 30);
		for(int cols = 0;cols < (1 << m);cols ++) //enumerate the type of every column
		{
			for(int mask = cols;mask >= 0;mask = (mask ? (cols & (mask - 1)) : -1)) //whether to apply a move on each cell at row 0
			{
				memcpy(s,baks,sizeof s);
				//apply type 1
				s[0] ^= (mask >> 1) ^ (mask << 1) ^ mask,s[1] ^= mask; 
				s[0] &= (1 << m) - 1;
				ans = min(ans,calc(cols) + __builtin_popcount(mask));
			}
			int els = ((1 << m) - 1) ^ cols;
			for(int mask = els;mask >= 0;mask = (mask ? (els & (mask - 1)) : -1)) //apply type 0
			{
				memcpy(s,baks,sizeof s);
				s[0] ^= (mask >> 1) ^ (mask << 1),s[1] ^= mask;
				s[0] &= (1 << m) - 1; 
				ans = min(ans,calc(cols) + __builtin_popcount(mask));
			}
		}
		return (ans == (1 << 30)) ? -1 : ans;
	}
};
