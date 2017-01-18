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
const int MINNUM = -101010;
class KeyDungeonDiv1
{
private:
	int n;//rooms
	int f[1 << 12][300];//f[S][i]: visited room set S, i red keys, max green keys (white keys can be considered either red or green)
public:
	int maxKeys(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys)
	{
		n = doorR.size();
		for(int i = 0; i < n; i++)
			roomR[i] -= doorR[i], roomG[i] -= doorG[i];
		for(int S = 0; S < (1 << n); S++)
			for(int i = 0; i <= (n + 1) * 20; i++)
				f[S][i] = MINNUM;
		for(int i = 0; i <= keys[2]; i++)//enum the number of white keys to be considered red
			f[0][keys[0] + i] = keys[1] + keys[2] - i;
		int ans = keys[0] + keys[1] + keys[2];
		for(int S = 1; S < (1 << n); S++)
		{
			for(int i = 0; i < n; i++)
				if(S & (1 << i))
					for(int j = doorR[i]; j <= (n + 1) * 20; j++)
						if(f[S ^ (1 << i)][j] >= doorG[i])
							for(int k = 0; k <= roomW[i]; k++)//enum the number of white keys to be considered red
								f[S][j + roomR[i] + k] = max(f[S][j + roomR[i] + k], f[S ^ (1 << i)][j] + roomG[i] + roomW[i] - k);
			for(int i = 0; i <= (n + 1) * 20; i++)
				if(i + f[S][i] > ans)
					ans = i + f[S][i];
		}
		return ans;
	}
};

