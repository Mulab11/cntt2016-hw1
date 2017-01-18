#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class GUMIAndSongsDiv1
{
private:
	int n;//number of songs
	int f[60][60];//f[i][j]: sing j songs in first i songs(including j), min time
	pair<int, int> song[60];//<tone, duration> 
public:
	int maxSongs(vector<int> duration, vector<int> tone, int T)
	{
		n = tone.size();
		for(int i = 1; i <= n; i++)
			song[i] = make_pair(tone[i - 1], duration[i - 1]);
		sort(song + 1, song + n + 1);//tone ascend
		memset(f, 63, sizeof(f));
		for(int i = 1; i <= n; i++)
		{
			f[i][1] = song[i].second;//sing song #i first
			for(int j = 2; j <= i; j++)
				for(int k = 1; k < i; k++)//previous song
					f[i][j] = min(f[i][j], f[k][j - 1] + song[i].second + song[i].first - song[k].first);
		}
		for(int j = n; j >= 1; j--)
			for(int i = j; i <= n; i++)
				if(f[i][j] <= T)
					return j;
		return 0;
	}
};

