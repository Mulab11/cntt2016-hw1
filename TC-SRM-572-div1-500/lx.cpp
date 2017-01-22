#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class EllysBulls
{
public : 
	void nextStr(string & a)
	{
		int x = 0;
		while (x < a.size() && a[x] == '9')
		{
			a[x] = '0';
			x++;
		}
		if (x == a.size())
			a = "";
		else
			a[x]++;
	}

	int match(const string & a, const string & b)
	{
		int ans = 0;
		rep (i, 0, a.size() - 1)
			ans += a[i] == b[i];
		return ans;
	}

	string getNumber(vector<string> word, vector<int> num)
	{
		map<string, string> Q;
		int m = word.size();
		int n = word[0].size();
		int half = n >> 1, Rhalf = n - half;
		string s(half, '0');
		while (s.size())
		{
			int i = 0;
			string v = "";
			for ( ; i < m; ++i)
			{
				int x = match(s, word[i].substr(0, half));
				if (x > num[i] || x + Rhalf < num[i])
					break ;
				v += to_string(num[i] - x);
			}
			if (i == m)
			{
				string & to = Q[v];
				if (to.size())
					to = "Ambiguity";
				else
					to = s;
			}
			nextStr(s);
		}
		string ans = "";
		s = string(Rhalf, '0');
		while (s.size())
		{
			int i = 0;
			string v = "";
			for ( ; i < m; ++i)
			{
				int x = match(s, word[i].substr(half, Rhalf));
				if (x > num[i])
					break ;
				v += to_string(x);
			}
			if (i == m)
			{
				string & to = Q[v];
				if (to.size())
				{
					if (to == "Ambiguity" || ans.size())
						return "Ambiguity";
					ans = to + s;
				}
			}
			nextStr(s);
		}
		return ans.size() ? ans : "Liar";
	}
};
