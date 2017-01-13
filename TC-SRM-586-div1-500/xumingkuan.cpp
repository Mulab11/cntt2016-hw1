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
class History
{
private:
	vector<int> string_to_int(const string &s)
	{
		vector<int> ret;
		for(int i = 0; i < (int)s.size(); i++)
		{
			while(s[i] < '0' || s[i] > '9')
				i++;
			int tmp = 0;
			while(i < (int)s.size() && s[i] >= '0' && s[i] <= '9')
				tmp = tmp * 10 + s[i++] - '0';
			ret.push_back(tmp);
		}
		return ret;
	}
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < (int)vec.size(); i++)
			ret += vec[i];
		return ret;
	}
	vector<int> dynasty[30];
	int n;//number of points (dynasties)
	int dist[30][30];//adjacency matrix
	void clearedge()
	{
		memset(dist, 63, sizeof(dist));
		for(int i = 0; i < n; i++)
			dist[i][i] = 0;
	}
	void insert(int u, int v, int w)
	{
		if(dist[u][v] > w)
			dist[u][v] = w;
	}
public:
	string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries)
	{
		n = dynasties.size();
		for(int i = 0; i < n; i++)
			dynasty[i] = string_to_int(dynasties[i]);
		string battle = concatenate(battles);
		clearedge();
		for(int i = 0; i < battle.size(); i += 6)//build graph, cha fen yue shu xi tong
		{
			int d1 = battle[i] - 'A', m1 = battle[i + 1] - '0', d2 = battle[i + 3] - 'A', m2 = battle[i + 4] - '0';//d = dynasty, m = monarch
			insert(d1, d2, dynasty[d1][m1 + 1] - dynasty[d2][m2] - 1);
			insert(d2, d1, dynasty[d2][m2 + 1] - dynasty[d1][m1] - 1);
		}
		for(int k = 0; k < n; k++)//floyd
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(dist[i][j] > dist[i][k] + dist[k][j])
						dist[i][j] = dist[i][k] + dist[k][j];
		string ans(queries.size(), 'N');
		for(int i = 0; i < queries.size(); i++)
		{
			int d1 = queries[i][0] - 'A', m1 = queries[i][1] - '0', d2 = queries[i][3] - 'A', m2 = queries[i][4] - '0';//d = dynasty, m = monarch
			if(dist[d1][d2] >= dynasty[d1][m1] - dynasty[d2][m2 + 1] + 1 && dist[d2][d1] >= dynasty[d2][m2] - dynasty[d1][m1 + 1] + 1)
				ans[i] = 'Y';
		}
		return ans;
	}
};

