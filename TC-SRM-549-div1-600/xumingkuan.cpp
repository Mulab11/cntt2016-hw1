#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>

using namespace std;
const int MAXN = 13;
const int MAXM = 1594323;//3^13
class MagicalHats
{
	private:
	//0: empty; 1: coin; 2: unknown
	bool f[MAXM + 5];//f[S]: coin set S, legal
	int g[MAXM + 5];//g[S]: guessed set S, max(min coins)
	pair <int, int> place[MAXN + 2];
	int n;
	bool row[MAXN + 2], col[MAXN + 2];
	int pow3[MAXN + 2];
	void searchf(int i, int numodd, int S, int lastunknown, int remaincoin)
	{
		if(i == n)
		{
			if(lastunknown == -1)
				f[S] = remaincoin ? false : !numodd;
			else
				f[S] = f[S - pow3[n - lastunknown - 1]] || f[S - pow3[n - lastunknown - 1] * 2];
			return;
		}
		searchf(i + 1, numodd, S * 3, lastunknown, remaincoin);//empty
		if(remaincoin)
		{
			if(row[place[i].first] = !row[place[i].first])
				numodd++;
			else
				numodd--;
			if(col[place[i].second] = !col[place[i].second])
				numodd++;
			else
				numodd--;
			searchf(i + 1, numodd, S * 3 + 1, lastunknown, remaincoin - 1);//coin
			if(row[place[i].first] = !row[place[i].first])
				numodd++;
			else
				numodd--;
			if(col[place[i].second] = !col[place[i].second])
				numodd++;
			else
				numodd--;
		}
		searchf(i + 1, numodd, S * 3 + 2, i, remaincoin);
	}
	int searchg(int S, int num)
	{
		if(g[S] != -1)//memorization
			return g[S];
		if(!f[S])
			return MAXN;
		if(!num)
			return 0;
		int &ret = g[S];
		ret = 0;
		for(int i = 0; i < n; i++)
			if(S % pow3[i + 1] / pow3[i] == 2)
				ret = max(ret, min(searchg(S - pow3[i], num - 1) + 1/*coin*/, searchg(S - pow3[i] * 2, num - 1)/*empty*/));
		return ret;
	}
	public:
	int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses)
	{
		n = 0;
		memset(row, false, sizeof(row));
		memset(col, false, sizeof(col));
		for(int i = 0; i < board.size(); i++)
			for(int j = 0; j < board[i].size(); j++)
				if(board[i][j] == 'H')
				{
					place[n++] = make_pair(i, j);
					row[i] = !row[i];
					col[j] = !col[j];
				}
		pow3[0] = 1;
		for(int i = 1; i <= n; i++)
			pow3[i] = pow3[i - 1] * 3;
		int numodd = 0;
		for(int i = 0; i < MAXN; i++)
		{
			if(row[i])
				numodd++;
			if(col[i])
				numodd++;
		}
		memset(f, false, sizeof(f));
		searchf(0, numodd, 0, -1, coins.size());
		if(!f[pow3[n] - 1])//illegal
			return -1;
		memset(g, -1, sizeof(g));
		int numCoin = searchg(pow3[n] - 1, numGuesses);//max number of coins to get
		sort(coins.begin(), coins.end());
		int ret = 0;
		for(int i = 0; i < numCoin; i++)//minimize value
			ret += coins[i];
		return ret;
	}
};

