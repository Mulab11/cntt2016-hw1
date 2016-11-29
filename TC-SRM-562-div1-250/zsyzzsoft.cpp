#include <algorithm>
using namespace std;
class PastingPaintingDivOne
{
public:
	int n, m, inc[4], ans[4], board[50][50], col[50][50];
	int Conv(char c)
	{
		if(c == 'R')
			return 1;
		if(c == 'G')
			return 2;
		if(c == 'B')
			return 3;
		return 0;
	}
	void Simulate()
	{
		for(int i = 0; i <= 3; i++)
			inc[i] = 0;
		for(int i = 0; i < n; i++) //染色 
		{
			for(int j = 0; j < m; j++)
			{
				if(board[i][j])
				{
					inc[col[i][j]]--;
					inc[col[i][j] = board[i][j]]++;
				}
			}
		}
		for(int i = 1; i <= 3; i++)
			ans[i] += inc[i];
		for(int i = 0; i < n; i++) //移动 
		{
			for(int j = 0; j < m; j++)
				col[i][j] = i + 1 < n && j + 1 < m ? col[i + 1][j + 1] : 0;
		}
	}
	vector<long long> countColors(vector<string> clipboard, int t)
	{
		for(int i = 0; i <= 3; i++)
			ans[i] = 0;
		n = clipboard.size();
		m = clipboard[0].length();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				board[i][j] = Conv(clipboard[i][j]), col[i][j] = 0;
		}
		for(int i = 0; i <= n && t; i++, t--)
			Simulate(); //模拟前面的操作 
		vector<long long> ret;
		for(int i = 1; i <= 3; i++)
			ret.push_back((long long)inc[i] * t + ans[i]); //后面的操作增量都是一样的 
		return ret;
	}
};