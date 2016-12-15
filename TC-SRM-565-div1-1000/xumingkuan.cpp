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
class UnknownTree
{
	private:
	int n;
	int d[60][3];//d[i][j] = distance between i and ('A'+j)
	int calc(vector <int> dist)//calculate a single branch
	{
		sort(dist.begin(), dist.end());
		if(dist.empty() || dist[0] != 0 || (dist.size() >= 2 && dist[1] == 0))//no root or >= 2 roots
			return 0;
		int ret = 1, j = 1;
		for(int i = 1; i < dist.size(); i++)
		{
			while(dist[j] < dist[i])
				j++;
			ret = (long long)ret * j % MOD;
		}
		return ret;
	}
	int solve_center(int x)//center point x
	{
		map <int, vector <int> > mp[3];//mp[i][j]: branch ('A'+i), distance j from x
		vector <int> vec;//out of 3 branches
		for(int k = 0; k < 3; k++)
			mp[k][d[x][k]].push_back(0);//point 'A', 'B', 'C'
		for(int j = 0; j < n; j++)
		{
			int s[3];
			for(int k = 0; k < 3; k++)
				s[k] = d[j][k] - d[x][k];
			if(s[0] == s[1] && s[0] == s[2])//out of 3 branches
			{
				if(s[0] < 0)
					return 0;
				vec.push_back(s[0]);
				continue;
			}
			bool ok = false;
			for(int k = 0; k < 3; k++)//try branch ('A'+k)
				if(s[(k + 1) % 3] == s[(k + 2) % 3])
				{
					if(s[(k + 1) % 3] <= 0 || s[(k + 1) % 3] - s[k] < 0 || ((s[(k + 1) % 3] - s[k]) & 1))
						return 0;
					mp[k][(s[(k + 1) % 3] - s[k]) >> 1].push_back(s[(k + 1) % 3] - ((s[(k + 1) % 3] - s[k]) >> 1));
					ok = true;
					break;
				}
			if(!ok)
				return 0;
		}
		int ret = calc(vec);
		for(int k = 0; k < 3; k++)
			for(map <int, vector <int> > :: iterator it = mp[k].begin(); it != mp[k].end(); it++)
				ret = (long long)ret * calc(it->second) % MOD;
		return ret;
	}
	int solve_chain(int x)//center point ('A'+x)
	{
		set <pair <int, int> > len;//length of (x+1)-x and x-(x+2)
		for(int i = 0; i < n; i++)
		{
			int s[3];
			for(int k = 0; k < 3; k++)
				s[k] = d[i][(x + k) % 3];
			if(s[1] > s[0] && s[2] > s[0])//x-i
				len.insert(make_pair(s[1] - s[0], s[2] - s[0]));
			if(s[2] > s[0])//(x+1)-i-x
				len.insert(make_pair(s[1] + s[0], s[2] - s[0]));
			if(s[1] > s[0])//x-i-(x+2)
				len.insert(make_pair(s[1] - s[0], s[2] + s[0]));
			if(s[2] > s[0] && s[0] > s[1])//i-(x+1)
				len.insert(make_pair(s[0] - s[1], s[2] - s[0]));
			if(s[1] > s[0] && s[0] > s[2])//i-(x+2)
				len.insert(make_pair(s[1] - s[0], s[0] - s[2]));
		}
		int ans = 0;
		for(set <pair <int, int> > :: iterator i = len.begin(); i != len.end(); i++)
		{
			const int len1 = i->first, len2 = i->second;
			map <int, vector <int> > mp[2];//mp[i][j]: branch ('A'+i+1), distance j from ('A'+x)
			vector <int> vec(1, 0);//out of 2 branches; point 'A'
			mp[0][len1].push_back(0);//'B'
			mp[1][len2].push_back(0);//'C'
			bool ok = true;
			for(int j = 0; j < n; j++)
			{
				int s[3];
				for(int k = 0; k < 3; k++)
					s[k] = d[j][(x + k) % 3];
				if(s[1] - len1 == s[0] && s[2] - len2 == s[0])
					vec.push_back(s[0]);//out of 2 branches
				else if(s[1] - len1 == s[0])//try branch 'C'
				{
					if(s[0] + len2 - s[2] < 0 || ((s[0] + len2 - s[2]) & 1))
					{
						ok = false;
						break;
					}
					mp[1][(s[0] + len2 - s[2]) >> 1].push_back(s[0] - ((s[0] + len2 - s[2]) >> 1));
				}
				else if(s[2] - len2 == s[0])//try branch 'B'
				{
					if(s[0] + len1 - s[1] < 0 || ((s[0] + len1 - s[1]) & 1))
					{
						ok = false;
						break;
					}
					mp[0][(s[0] + len1 - s[1]) >> 1].push_back(s[0] - ((s[0] + len1 - s[1]) >> 1));
				}
				else
				{
					ok = false;
					break;
				}
			}
			if(!ok)
				continue;
			int ret = calc(vec);
			for(int k = 0; k < 2; k++)
				for(map <int, vector <int> > :: iterator it = mp[k].begin(); it != mp[k].end(); it++)
					ret = (long long)ret * calc(it->second) % MOD;
			ans = (ans + ret) % MOD;
		}
		return ans;
	}
	public:
	int getCount(vector<int> distancesA, vector<int> distancesB, vector<int> distancesC)
	{
		n = distancesA.size();
		for(int i = 0; i < n; i++)
		{
			d[i][0] = distancesA[i];
			d[i][1] = distancesB[i];
			d[i][2] = distancesC[i];
		}
		int ans = 0;
		for(int i = 0; i < n; i++)
			ans = (ans + solve_center(i)) % MOD;
		for(int k = 0; k < 3; k++)
			ans = (ans + solve_chain(k)) % MOD;
		return ans;
	}
};

