#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

class PastingPaitingDivOne
{
public : 
	vector<LL> countColors(vector <string> board, int T)
	{
		int w = board.size();
		int h = board[0].size();

		vector<LL> ans(3, 0);
		LL oR = 0, oG = 0, oB = 0;

		vector<string> canvas(w, string(h, '.') );        
		vector<string> previous;

		for (int iter = 0; iter < T; iter++)
		{
			if (canvas == previous)
			{
				LL ret = T - iter;
				ans[0] += ret * oR;
				ans[1] += ret * oG;
				ans[2] += ret * oB;
				break ;
			}
			else
			{
				previous = canvas;
				vector<string> nw(w + 1);
				for (int j = 0; j < w; ++j)
				{
					nw[j] = previous[j];
					nw[j] += '.';
				}
				nw[w] = string(h + 1, '.');
				canvas = vector<string> (w, string(h, '.'));
				oR = oG = oB = 0;
				for (int i = 0; i < w; ++i) 
				{
					for (int j = 0; j < h; ++j)
					{
						char pre = nw[i + 1][j + 1];
						char nxt = board[i][j];
						if (nxt == '.')
							nxt = pre;
						oR += (nxt == 'R') - (pre == 'R');
						oG += (nxt == 'G') - (pre == 'G');
						oB += (nxt == 'B') - (pre == 'B');
						canvas[i][j] = nxt;
					}
				}
				ans[0] += oR;
				ans[1] += oG;
				ans[2] += oB;
			}
		}
		return ans;
	}
};

