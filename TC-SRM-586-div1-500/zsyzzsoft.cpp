#include <algorithm>
using namespace std;
const int inf = 1000000000;
int u, v, a, b, dis[26][26];
class History
{
public:
	void Parse(string str)
	{
		u = str[0] - 'A';
		int x = 3;
		if(str[x] == '-')
			x++;
		v = str[x] - 'A';
		a = x == 3 ? str[1] - '0' : (str[1] - '0') * 10 + (str[2] - '0');
		b = str.length() - x == 2 ? str[x + 1] - '0' : (str[x + 1] - '0') * 10 + (str[x + 2] - '0');
	}
	vector<vector<int> > Parse(const vector<string> &vec)
	{
		vector<vector<int> > ret;
		for(int i = 0; i < vec.size(); i++)
		{
			vector<int> arr;
			string str = vec[i];
			arr.push_back(0);
			for(int i = 0, j = 0; i < str.length(); i++)
			{
				if(str[i] == ' ')
					arr.push_back(0), j++;
				else
					arr[j] = arr[j] * 10 + (str[i] - '0');
			}
			ret.push_back(arr);
		}
		return ret;
	}
	vector<string> Split(const vector<string> &vec)
	{
		string str;
		for(int i = 0; i < vec.size(); i++)
			str += vec[i];
		vector<string> ret;
		string cur;
		for(int i = 0; i < str.length(); i++)
		{
			if(str[i] == ' ')
				ret.push_back(cur), cur = "";
			else
				cur.push_back(str[i]);
		}
		ret.push_back(cur);
		return ret;
	}
	void Edge(int p, int q, int w)
	{
		dis[p][q] = max(dis[p][q], w);
	}
	string verifyClaims(vector<string> t_vec, vector<string> s_vec, vector<string> q)
	{
		vector<vector<int> > t = Parse(t_vec);
		vector<string> s = Split(s_vec);
		int n = t.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				dis[i][j] = -inf;
			dis[i][i] = 0;
		}
		for(int i = 0; i < s.size(); i++)
		{
			Parse(s[i]);
			Edge(u, v, t[u][a] - t[v][b + 1] + 1); //限制两个年代间的差值 
			Edge(v, u, t[v][b] - t[u][a + 1] + 1);
		}
		for(int k = 0; k < n; k++) //计算任意两个年代的最小差值 
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					dis[i][j] = max(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
		string ans;
		for(int i = 0; i < q.size(); i++)
		{
			Parse(q[i]);
			ans.push_back(t[u][a + 1] > t[v][b] + dis[u][v] && t[v][b + 1] > t[u][a] + dis[v][u] ? 'Y' : 'N'); //判断 
		}
		return ans;
	}
};