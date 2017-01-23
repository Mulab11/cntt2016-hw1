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

const int MAXN = 13 + 2;
const int MAXM = 1594323 + 100;
const int INF = 0x1f1f1f1f;

class MagicalHats
{
	public:
	
	int h, w, n, m, k;
	int f[MAXM];
	int row, col;
	pair<int, int> pos[MAXN];
	int pow3[MAXN];
	
	int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses)
	{
		h = board.size();
		w = board[0].size();
		n = 0;
		m = coins.size();
		k = numGuesses;
		row = col = 0;
		for(int i = 0; i < h; i++)
			for(int j = 0; j < w; j++)
				if(board[i][j] == 'H')
				{
					row ^= (1 << i), col ^= (1 << j);
					pos[n++] = make_pair(i, j);
				}
		pow3[0] = 1;
		for(int i = 1; i <= n; i++)
			pow3[i] = pow3[i - 1] * 3;
			
		memset(f, 31, sizeof(f));
		for(int i = 0; i < (1 << n); i++)
		{
			int tmp[MAXN], cnt = 0;
			for(int j = 0; j < n; j++)
				tmp[j] = i & (1 << j) ? 1 : 0, cnt += tmp[j];
			if(cnt != m)
				continue;
			int rtmp = 0, ctmp = 0;
			for(int j = 0; j < n; j++)
				rtmp ^= (tmp[j] << pos[j].first), ctmp ^= (tmp[j] << pos[j].second);
			if(rtmp != row || ctmp != col)
				continue;
			
			int sta = 0;
			for(int j = 0; j < n; j++)
				if(tmp[j])
					sta += pow3[j];
				else
					sta += 2 * pow3[j];
			f[sta] = 0;
//			cout << rtmp << ' ' << ctmp << ' ' << i << endl;
		}
		for(int i = pow3[n] - 1; i >= 0; i--)
		{
			int t = i, tmp[MAXN], cnt = 0;
			for(int j = 0; j < n; j++)
				tmp[j] = t % 3, cnt += tmp[j] > 0, t /= 3;
			if(cnt >= k)
			{
				for(int j = 0; j < n; j++)
					if(!tmp[j])
					{
						if(f[i + pow3[j]] == 0 || f[i + 2 * pow3[j]] == 0)
							f[i] = 0;
						break;
					}
			}
			else
			{
				f[i] = 0;
				for(int j = 0; j < n; j++)
					if(!tmp[j])
						f[i] = max(f[i], min(f[i + pow3[j]] + 1, f[i + 2 * pow3[j]]));
			}
		}
		int cnt = f[0], ans = 0;
		if(cnt >= INF)
			return -1;
		sort(coins.begin(), coins.end());
		for(int i = 0; i < cnt; i++)
			ans += coins[i];
		
		return ans;
	}
};

