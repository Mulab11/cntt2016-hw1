#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int MAXN = 55, MAXM = 16, oo = 101010101;
class TravellingPurchasingMan
{
private:
	int M;
	int f[1 << MAXM][MAXM];//f[S][i]: purchase at store set S, the last purchase is at store i, min time
	int dist[MAXN][MAXN];
	vector<int> store[MAXN];//open, close, duration
	int to2[1 << MAXM];//to2[1 << i] = i
	vector<int> getnum(const string &s)
	{
		vector<int> ret;
		int i = 0;
		while(i < s.size())
		{
			while(i < s.size() && !isdigit(s[i]))
				i++;
			if(i == s.size())
				break;
			int tmp = 0;
			while(i < s.size() && isdigit(s[i]))
				tmp = tmp * 10 + s[i++] - '0';
			ret.push_back(tmp);
		}
		return ret;
	}
	inline int lowbit(int x)
	{
		return x & (-x);
	}
	int bitcnt(int x)
	{
		int ret = 0;
		while(x)
			ret++, x ^= lowbit(x);
		return ret;
	}
public:
	int maxStores(int N, vector<string> interestingStores, vector<string> roads)
	{
		memset(dist, 31, sizeof(dist));
		for(int i = 0; i < N; i++)
			dist[i][i] = 0;
		for(int i = 0; i < roads.size(); i++)
		{
			vector<int> tmp = getnum(roads[i]);
			dist[tmp[0]][tmp[1]] = dist[tmp[1]][tmp[0]] = min(tmp[2], dist[tmp[0]][tmp[1]]);
		}
		for(int k = 0; k < N; k++)//floyd
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					if(dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
		M = interestingStores.size();
		for(int i = 0; i < M; i++)
			store[i] = getnum(interestingStores[i]);
		for(int i = 0; i < M; i++)
			to2[1 << i] = i;
		memset(f, 31, sizeof(f));
		for(int i = 0; i < M; i++)//make the first purchase at store i
			if(dist[N - 1][i] <= store[i][1])//go to the store before it closes
				f[1 << i][i] = max(dist[N - 1][i], store[i][0]) + store[i][2];
		int ans = 0;
		for(int S = 1; S < (1 << M); S++)//enumerate the store set
		{
			int tmp1 = S;
			int cnt = bitcnt(S);
			while(tmp1)
			{
				int tmp2 = lowbit(tmp1);//enumerate the last store
				int tmp3 = to2[tmp2];
				int tmp4 = (S ^ tmp2);
				while(tmp4)
				{
					int tmp5 = lowbit(tmp4);//enumerate the second last store
					int tmp6 = to2[tmp5];
					if(f[S ^ tmp2][tmp6] + dist[tmp6][tmp3] <= store[tmp3][1])//go to the store before it closes
						f[S][tmp3] = min(f[S][tmp3], max(f[S ^ tmp2][tmp6] + dist[tmp6][tmp3], store[tmp3][0]) + store[tmp3][2]);
					tmp4 ^= tmp5;
				}
				if(cnt > ans && f[S][tmp3] < oo)//'< oo" means that it's possible
					ans = cnt;
				tmp1 ^= tmp2;
			}
		}
		return ans;
	}
};

