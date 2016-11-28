#include <algorithm>
using namespace std;
int pw[14], c[13], f[2000000];
class MagicalHats
{
	int n, m, x[13], y[13];
public:
	void Update(int &st, int a, int b)
	{
		st ^= 1 << a;
		st ^= 1 << (b + 13);
	}
	int findMaximumReward(vector<string> board, vector<int> w, int k)
	{
		m = w.size();
		sort(w.begin(), w.end());
		int state = 0;
		for(int i = 0; i < board.size(); i++)
		{
			for(int j = 0; j < board[i].length(); j++)
			{
				if(board[i][j] == 'H')
					Update(state, x[n] = i, y[n] = j), n++;
			}
		}
		pw[0] = 1;
		for(int i = 0; i < n; i++)
			pw[i + 1] = pw[i] * 3;
		for(int i = 0; i < pw[n]; i++)
			f[i] = 1000000000;
		for(int i = 0; i < 1 << n; i++) //枚举最终硬币状态 
		{
			int cnt = 0;
			for(int j = 0; j < n; j++)
				cnt += (i >> j) & 1;
			if(cnt != m)
				continue;
			int tmp = state;
			for(int j = 0; j < n; j++)
			{
				if((i >> j) & 1)
					Update(tmp, x[j], y[j]);
			}
			if(tmp)
				continue;
			tmp = 0; //状态合法 
			for(int j = 0; j < n; j++)
				tmp += pw[j] * (((i >> j) & 1) + 1);
			f[tmp] = 0;
		}
		for(int i = pw[n] - 1; i >= 0; i--)
		{
			int cnt = 0;
			for(int j = 0, t = i; j < n; j++, t /= 3)
				cnt += (c[j] = t % 3) > 0;
			if(cnt >= k) //第一部分：求出翻过若干个帽子之后是否仍能达到合法解 
			{
				for(int j = 0; j < n; j++)
				{
					if(!c[j])
					{
						f[i] = f[i + pw[j]] & f[i + pw[j] * 2];
						break;
					}
				}
			}
			else //第二部分：枚举翻哪个帽子 
			{
				f[i] = 0;
				for(int j = 0; j < n; j++)
				{
					if(!c[j])
						f[i] = max(f[i], min(f[i + pw[j]], f[i + pw[j] * 2] + 1));
				}
			}
		}
		if(f[0] > m)
			return -1;
		int ans = 0; //通过得到的最多硬币数计算答案，因为得到的肯定是价值最小的硬币 
		for(int i = 0; i < f[0]; i++)
			ans += w[i];
		return ans;
	}
};
