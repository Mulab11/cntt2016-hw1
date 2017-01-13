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
const int MOD = 1000000007;

class GooseInZooDivOne
{
private:
	bool visit[55][55];
	queue<pair<int, int> > q;
	pair<int, int> f;//dp: number of possible sets of geese in the cage where the number of geese is odd/even(>0)
public:
	int count(vector<string> field, int dist)
	{
		f = make_pair(0, 0);
		memset(visit, false, sizeof(visit));
		int n = field.size(), m = field[0].size();
		#define isv(i, j) ((i) >= 0 && (i) < n && (j) >= 0 && (j) < m && field[i][j] == 'v' && !visit[i][j])
		#define search1(i, j) if(isv((i), (j)))\
		{\
			visit[i][j] = true;\
			q.push(make_pair((i), (j)));
		#define search(i, j) search1((i), (j))}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				search1(i, j)
					int cnt = 0;
					while(!q.empty())//bfs
					{
						cnt++;
						int x = q.front().first, y = q.front().second;
						q.pop();
						for(int ii = -dist; ii <= dist; ii++)
							for(int jj = -dist + abs(ii); jj <= dist - abs(ii); jj++)
								search(x + ii, y + jj)
					}
					if(cnt & 1)//odd
						f = make_pair((f.first + f.second + 1) % MOD, (f.first + f.second) % MOD);
					else//even
						f = make_pair(f.first * 2 % MOD, (f.second * 2 + 1) % MOD);
				}
		return f.second;
	}
};

