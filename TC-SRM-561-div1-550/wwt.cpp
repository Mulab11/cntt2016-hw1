/*
按圆的覆盖关系建树。设f[u]表示以u为根的子树的sg，那么枚举一个v \in sub(u)，
操作v，相当于把v->u这些点全删掉，令{p_i}为剩下的子图的根的集合，那么这种操作对应的sg值就是xor{f[p_i]}。各种暴力即可。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int apear[maxn * maxn],mark[maxn];

class CirclesGame
{
public:
	vector<int> ch[maxn];
	int final[maxn],nex[maxn],fa[maxn],f[maxn],n,vistag,mktag;

	void link(int u,int v)
	{
		nex[v] = final[u],final[u] = v;
	}

	void dfs(int now)
	{
		ch[now].clear();
		ch[now].push_back(now);
		for(int i = final[now];i;i = nex[i])
		{
			dfs(i);
			for(int j = 0;j < ch[i].size();j ++)
				ch[now].push_back(ch[i][j]);
		}
		++ vistag;
		for(int i = 0;i < ch[now].size();i ++) //枚举选哪个后代把后代到now的点全删掉
		{
			++ mktag;
			int v = ch[now][i],ss = 0;
			for(int j = v;j;j = fa[j]) mark[j] = mktag;
			for(int j = 0;j < ch[now].size();j ++)
			{
				int u = ch[now][j];
				if (mark[u] != mktag && mark[fa[u]] == mktag) ss ^= f[u]; //u就是分裂后的树的某个部分的根
			}
			apear[ss] = vistag;
		}
		for(f[now] = 0;apear[f[now]] == vistag;++ f[now]); //求sg值
	}

	int sqr(int a) {return a * a;}

	string whoCanWin(vector <int> x, vector <int> y, vector <int> r)
	{
		vistag = mktag = 0;
		n = x.size();
		//建树
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (i != j && r[i] > r[j])
				{
					if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= r[i] * r[i]) 
					{
						if (!fa[j + 1]) fa[j + 1] = i + 1; else
							if (r[i] < r[fa[j + 1] - 1]) fa[j + 1] = i + 1; //半径最小的能覆盖j的i就是他的父亲
					}
				}
		int ans = 0;
		for(int i = 1;i <= n;i ++)
			if (fa[i]) link(fa[i],i);
		for(int i = 1;i <= n;i ++)
			if (!fa[i])
			{
				dfs(i);
				ans ^= f[i];
			}
		return (ans) ? "Alice" : "Bob";
	}
};
