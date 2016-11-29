#include <algorithm>
using namespace std;
int n, s[50], l[25], r[25], col[51], e[51][51];
bool ans, flag, ok, type[25], apart[25][25];
class DisjointSemicircles
{
public:
	void Dfs(int node)
	{
		for(int i = 0; i <= n; i++)
		{
			if(e[node][i] >= 0)
			{
				if(col[i] == -1)
					col[i] = col[node] ^ e[node][i], Dfs(i);
				else if(col[i] != (col[node] ^ e[node][i]))
					flag = false; //不满足限制条件 
			}
		}
	}
	void Enum(int depth)
	{
		if(depth == 25)
		{
			for(int i = 0; i <= n; i++)
				col[i] = -1;
			flag = true;
			for(int i = 0; i <= n && flag; i++)
			{
				if(col[i] == -1)
					col[i] = 0, Dfs(i);
			}
			if(flag)
				ans = true;
		}
		else if(!r[depth])
			Enum(depth + 1);
		else
		{
			ok = true;
			for(int i = 0; i < depth && ok; i++)
				ok &= !r[i] || type[i] != 0 || !apart[i][depth];
			if(ok) //要求区间内0的个数为偶数 
			{
				type[depth] = 0;
				int u = s[l[depth]], v = s[r[depth]], w = (v - u) & 1;
				if(e[u][v] == w)
					Enum(depth + 1);
				else if(e[u][v] < 0)
				{
					e[u][v] = e[v][u] = w;
					Enum(depth + 1);
					e[u][v] = e[v][u] = -1;
				}
			}
			ok = true;
			for(int i = 0; i < depth && ok; i++)
				ok &= !r[i] || type[i] != 1 || !apart[i][depth];
			if(ok) //要求区间内1的个数为偶数 
			{
				type[depth] = 1;
				int u = s[l[depth]], v = s[r[depth]], w = 0;
				if(e[u][v] == w)
					Enum(depth + 1);
				else if(e[u][v] < 0)
				{
					e[u][v] = e[v][u] = w;
					Enum(depth + 1);
					e[u][v] = e[v][u] = -1;
				}
			}
		}
	}
	void Color(int node)
	{
		for(int i = 0; i < 25; i++)
		{
			if(r[i] && apart[node][i])
			{
				if(col[i] < 0)
					col[i] = !col[node], Color(i);
				else if(col[i] != !col[node])
					flag = true;
			}
		}
	}
	string getPossibility(vector<int> labels)
	{
		for(int i = 0; i < labels.size(); i++)
			s[i] = labels[i] < 0 ? ++n : n;
		for(int i = labels.size() - 1; i >= 0; i--)
		{
			if(labels[i] >= 0)
			{
				if(!r[labels[i]])
					r[labels[i]] = i;
				else
					l[labels[i]] = i;
			}
		}
		int cnt = 0;
		for(int i = 0; i < 25; i++)
			cnt += r[i] > 0;
		if(n <= 2) //特判所有配对均已确定的情况 
		{
			int label = 0;
			while(label < 25 && r[label])
				label++;
			for(int i = labels.size() - 1; i >= 0; i--)
			{
				if(labels[i] < 0)
				{
					if(!r[label])
						r[label] = i;
					else
						l[label] = i;
				}
			}
			for(int i = 0; i < 25; i++)
			{
				for(int j = 0; j < 25; j++)
					apart[i][j] = (r[j] > l[i] && r[j] < r[i]) ^ (l[j] > l[i] && l[j] < r[i]);
			}
			for(int i = 0; i < 25; i++)
				col[i] = -1;
			for(int i = 0; i < 25; i++)
			{
				if(r[i] && col[i] == -1)
				{
					flag = false;
					Color(i);
					if(flag)
						return "IMPOSSIBLE";
				}
			}
			return "POSSIBLE";
		}
		for(int i = 0; i < 25; i++) //判断交叉关系 
		{
			for(int j = 0; j < 25; j++)
				apart[i][j] = (r[j] > l[i] && r[j] < r[i]) ^ (l[j] > l[i] && l[j] < r[i]);
		}
		for(int i = 0; i <= n; i++)
		{
			for(int j = 0; j <= n; j++)
				e[i][j] = -1;
		}
		e[0][n] = e[n][0] = 0;
		Enum(0); //枚举已配对的方向 
		return ans ? "POSSIBLE" : "IMPOSSIBLE";
	}
};