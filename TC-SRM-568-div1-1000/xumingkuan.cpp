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

class DisjointSemicircles
{
	private:
	int n, num1, num2;//number of pairs of "-1" / others
	pair<int, int> match[60];
	vector<int> labels;
	//possible = true, impossible = false
	bool intersect(int al, int ar, int bl, int br)
	{
		return (al < bl && bl < ar && ar < br) || (bl < al && al < br && br < ar);
	}
	int fa[110];//disjoint-set
	int getanc(int x)
	{
		return fa[x] == x ? x : fa[x] = getanc(fa[x]);
	}
	bool solve1()//many "-1"s; O(2^num2 * (num2^2 + nlog(num2)))
	{
		static int sum[60];//prefix sum of "-1", 1-based
		static int prev[60];//previous "-1", 1-based
		static bool up[60];
		sum[0] = 0;
		for(int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + (labels[i - 1] == -1);
		prev[0] = 0;
		for(int i = 1; i <= n; i++)
			prev[i] = labels[i - 1] == -1 ? i : prev[i - 1];
		for(int s = 0; s < (1 << num2); s++)
		{
			for(int i = 0; i < num2; i++)
				up[i] = ((s >> i) & 1);
			bool ok = true;
			for(int i = 0; i < num2 && ok; i++)
				for(int j = i + 1; j < num2 && ok; j++)
					if(up[i] == up[j] && intersect(match[i].first, match[i].second, match[j].first, match[j].second))
						ok = false;
			if(!ok)
				continue;
			for(int i = 0; i < (n + 1) * 2; i++)
				fa[i] = i;
			fa[getanc(0)] = getanc(prev[n]);//suppose there's a big circle covering all points
			fa[getanc(n + 1)] = getanc(prev[n] + n + 1);
			for(int i = 0; i < num2; i++)
			{
				if(up[i] || (sum[match[i].second + 1] - sum[match[i].first]) % 2 == 0)//merge(l, r), merge(~l, ~r)
				{
					fa[getanc(prev[match[i].first + 1])] = getanc(prev[match[i].second + 1]);
					fa[getanc(prev[match[i].first + 1] + n + 1)] = getanc(prev[match[i].second + 1] + n + 1);
				}
				else//merge(l, ~r), merge(~l, r)
				{
					fa[getanc(prev[match[i].first + 1])] = getanc(prev[match[i].second + 1] + n + 1);
					fa[getanc(prev[match[i].first + 1] + n + 1)] = getanc(prev[match[i].second + 1]);
				}
				if(getanc(prev[match[i].first + 1]) == getanc(prev[match[i].first + 1] + n + 1))//invalid
				{
					ok = false;
					break;
				}
			}
			if(ok)
				return true;
		}
		return false;
	}
	bool solve2_check()
	{
		for(int i = 0; i < n; i++)
			fa[i] = i;
		for(int i = 0; i < n / 2; i++)
			for(int j = i + 1; j < n / 2; j++)
				if(intersect(match[i].first, match[i].second, match[j].first, match[j].second))
				{
					fa[getanc(i + n / 2)] = getanc(j);//merge(~i, j)
					fa[getanc(j + n / 2)] = getanc(i);//merge(~j, i)
					if(getanc(i) == getanc(i + n / 2))//invalid
						return false;
				}
		return true;
	}
	bool solve2_search(int p, int cnt)//place: labels[p], match[cnt]
	{
		if(cnt == n / 2)
			return solve2_check();
		if(labels[p] != -1)
			return solve2_search(p + 1, cnt);
		for(int i = p + 1; i < n; i++)
			if(labels[i] == -1)
			{
				labels[p] = labels[i] = 0;
				match[cnt] = make_pair(p, i);
				if(solve2_search(p + 1, cnt + 1))
					return true;
				labels[p] = labels[i] = -1;
			}
		return false;
	}
	bool solve2()//few "-1"s; O((2 * num1 - 1)!! * n^2logn)
	{
		return solve2_search(0, num2);
	}
	public:
	string getPossibility(vector<int> labels)
	{
		n = labels.size();
		this->labels = labels;
		num1 = num2 = 0;
		memset(match, -1, sizeof(match));
		for(int i = 0; i < n; i++)
			if(labels[i] == -1)
				num1++;
			else if(match[labels[i]].first == -1)
				match[labels[i]].first = i;
			else
				match[labels[i]].second = i;
		for(int i = 0; i < n; i++)
			if(match[i].first != -1)
				match[num2++] = match[i];
		num1 >>= 1;
		bool ans;
		if(num1 > n / 6)
			ans = solve1();
		else
			ans = solve2();
		return ans ? "POSSIBLE" : "IMPOSSIBLE";
	}
};

