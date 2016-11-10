#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <map>
int n, m;
int H;
vector<string> que;
vector<int> res;
string cur, ans;
map<vector<int>, vector<string> > T;
int counter;
void dfs_l(int p)
{
	if(p == H) return T[res].push_back(cur);
	for(int d = 0; d != 10; ++d)
	{
		for(int i = 0; i != m; ++i) if(que[i][p] - '0' == d) ++res[i];
		cur.push_back('0' + d);
		dfs_l(p + 1);
		cur.pop_back();
		for(int i = 0; i != m; ++i) if(que[i][p] - '0' == d) --res[i];
	}
}
void dfs_r(int p)
{
	if(p == n)
	{
		map<vector<int>, vector<string> >::iterator k = T.find(res);
		if(k != T.end())
		{
			counter += k->second.size();
			ans = k->second[0] + cur;
		}
		return;
	}
	for(int d = 0; d != 10; ++d)
	{
		for(int i = 0; i != m; ++i) if(que[i][p] - '0' == d) --res[i];
		cur.push_back('0' + d);
		dfs_r(p + 1);
		cur.pop_back();
		for(int i = 0; i != m; ++i) if(que[i][p] - '0' == d) ++res[i];
	}
}

class EllysBulls
{
public:
	string getNumber(vector<string> query, vector<int> result)
	{
		m = query.size();
		n = query[0].size();
		que = query;
		H = (n + 1) >> 1;
		res.resize(m);
		dfs_l(0);
		res = result;
		dfs_r(H);
		if(!counter) return "Liar";
		if(counter > 1) return "Ambiguity";
		return ans;
	}
}	user;
