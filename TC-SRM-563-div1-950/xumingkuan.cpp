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
#include <queue>
#include <map>
using namespace std;
const int MOD = 1000000009;

class CoinsGame
{
	private:
	int h, w;//h * w board
	vector <string> a;//board
	pair <int, int> place[2020];
	map <pair <int, int>, int> number;
	int n;//number of '.'
	int go[2020][4];//up, down, left, right
	int rank[2020], tmp1[2020], tmp2[2020], bucket[2020], maxrank;
	int p2[2020];//p2[i] = 2^i % MOD
	inline bool same(int i, int j) const
	{
		return rank[go[i][0]] == rank[go[j][0]] && rank[go[i][1]] == rank[go[j][1]] && 
			rank[go[i][2]] == rank[go[j][2]] && rank[go[i][3]] == rank[go[j][3]];
	}
	public:
	int ways(vector<string> board)
	{
		a = board;
		number.clear();
		h = board.size();
		w = board[0].size();
		n = 0;
		for(int i = 0; i < h; i++)
			for(int j = 0; j < w; j++)
				if(board[i][j] == '.')
				{
					place[++n] = make_pair(i, j);
					number[make_pair(i, j)] = n;
				}
		for(int i = 1; i <= n; i++)
		{
			const int x = place[i].first, y = place[i].second;
			go[i][0] = x == 0 ? 0 : number.find(make_pair(x - 1, y)) == number.end() ? i : number[make_pair(x - 1, y)];
			go[i][1] = x == h - 1 ? 0 : number.find(make_pair(x + 1, y)) == number.end() ? i : number[make_pair(x + 1, y)];
			go[i][2] = y == 0 ? 0 : number.find(make_pair(x, y - 1)) == number.end() ? i : number[make_pair(x, y - 1)];
			go[i][3] = y == w - 1 ? 0 : number.find(make_pair(x, y + 1)) == number.end() ? i : number[make_pair(x, y + 1)];
			rank[i] = 1;
		}
		rank[0] = 0;
		maxrank = 1;
		while(1)//radix sorting 
		{
			memset(bucket, 0, (maxrank + 1) * sizeof(int));
			for(int i = 1; i <= n; i++)
				bucket[rank[go[i][0]]]++;
			for(int i = 1; i <= maxrank; i++)
				bucket[i] += bucket[i - 1];
			for(int i = n; i >= 1; i--)
				tmp1[bucket[rank[go[i][0]]]--] = i;
			
			memset(bucket, 0, (maxrank + 1) * sizeof(int));
			for(int i = 1; i <= n; i++)
				bucket[rank[go[i][1]]]++;
			for(int i = 1; i <= maxrank; i++)
				bucket[i] += bucket[i - 1];
			for(int i = n; i >= 1; i--)
				tmp2[bucket[rank[go[tmp1[i]][1]]]--] = tmp1[i];
			
			memset(bucket, 0, (maxrank + 1) * sizeof(int));
			for(int i = 1; i <= n; i++)
				bucket[rank[go[i][2]]]++;
			for(int i = 1; i <= maxrank; i++)
				bucket[i] += bucket[i - 1];
			for(int i = n; i >= 1; i--)
				tmp1[bucket[rank[go[tmp2[i]][2]]]--] = tmp2[i];
			
			memset(bucket, 0, (maxrank + 1) * sizeof(int));
			for(int i = 1; i <= n; i++)
				bucket[rank[go[i][3]]]++;
			for(int i = 1; i <= maxrank; i++)
				bucket[i] += bucket[i - 1];
			for(int i = n; i >= 1; i--)
				tmp2[bucket[rank[go[tmp1[i]][3]]]--] = tmp1[i];
			
			const int prevmaxrank = maxrank;
			maxrank = tmp1[tmp2[1]] = 1;
			for(int i = 2; i <= n; i++)
				tmp1[tmp2[i]] = same(tmp2[i - 1], tmp2[i]) ? maxrank : ++maxrank;
			memcpy(rank, tmp1, (n + 1) * sizeof(int));
			if(prevmaxrank == maxrank)
				break;
		}
		p2[0] = 1;
		for(int i = 1; i <= n; i++)
			p2[i] = (p2[i - 1] << 1) % MOD;
		memset(bucket, 0, (maxrank + 1) * sizeof(int));
		for(int i = 1; i <= n; i++)
			bucket[rank[i]]++;
		int ans = p2[n] - n - 1;
		for(int i = 1; i <= maxrank; i++)
			ans = (ans - (p2[bucket[i]] - bucket[i] - 1) + MOD) % MOD;
		return ans;
	}
};

