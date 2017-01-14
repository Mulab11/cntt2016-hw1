#include <bits/stdc++.h>

using namespace std;

const int maxn = 105; //50 + 50

//对于任意格子，令g[i][j]为最后选择的方向，那么必有g[i][j]=row[i]^col[j]，也就是说，每一行，要么和第一行完全不同，要么完全相同
//那么我们可以知道row[i]是否等于col[j]，dfs一下判合法即可。

int lk[maxn][maxn],c[maxn],n,m;

bool dfs(int now,int co)
{
	c[now] = co;
	for(int i = 0;i < n + m;i ++)
		if (lk[now][i] != -1)
		{
			if (c[i] == -1)
				if (!dfs(i,co ^ lk[now][i])) return 0;
			if (c[i] != (co ^ lk[now][i])) return 0;
		}
	return 1;
}

bool test_ok()
{
	memset(c,255,sizeof c);
	for(int i = 0;i < n + m;i ++)
		if (c[i] == -1) 
			if (!dfs(i,c[i] = 0)) return 0;//fix c
	return 1;
}

class ThreeColorability
{
public:

	vector<string> lexSmallest(vector<string> cells)
	{
		memset(lk,255,sizeof lk);
		n = cells.size(),m = cells[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (cells[i][j] != '?') lk[i][j + n] = lk[j + n][i] = (cells[i][j] == 'N');
		vector<string> out,emp;
		out.clear();
		emp.clear();
		for(int i = 0;i < n;i ++)
		{
			string cur = "";
			for(int j = 0;j < m;j ++)
			{
				if (cells[i][j] == '?' || cells[i][j] == 'N')
				{
					lk[i][j + n] = lk[j + n][i] = 1;//if we put 'N'
					if (test_ok()) {cur = cur + 'N';continue;}
				}
				if (cells[i][j] == '?' || cells[i][j] == 'Z')
				{
					lk[i][j + n] = lk[j + n][i] = 0;
					if (test_ok()) {cur = cur + 'Z';continue;}
				}
				return emp;//illegal
			}
			out.push_back(cur);
		}
		return out;
	}
};
