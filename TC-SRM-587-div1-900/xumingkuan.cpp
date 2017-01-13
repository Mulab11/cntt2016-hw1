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
class Edge
{
public:
	int to, v, next;
};
const int MAXN = 105, MAXM = 5050;
class ThreeColorability
{
private:
	int n, m;//n*m cells
	Edge e[MAXM];//adjacency list
	int head[MAXN], en;
	int label[MAXN];
	void clearedge()
	{
		memset(head, -1, sizeof(head));
		en = 1;
	}
	void insert(int u, int v, int w)
	{
		e[++en].to = v;
		e[en].v = w;
		e[en].next = head[u];
		head[u] = en;
		e[++en].to = u;
		e[en].v = w;
		e[en].next = head[v];
		head[v] = en;
	}
	bool setlabel(int p, int v)
	{
		if(label[p] == -1)
			label[p] = v;
		else
			return label[p] == v;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!setlabel(e[i].to, v ^ e[i].v))
				return false;
		return true;
	}
public:
	vector<string> lexSmallest(vector<string> cells)
	{
		n = cells.size(), m = cells[0].size();
		clearedge();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(cells[i][j] != '?')
					insert(i + m, j, cells[i][j] == 'Z');//Z = 1, N = 0
		memset(label, -1, sizeof(label));
		if(!setlabel(m, 0))//set 0 to the first row
			return vector<string>();
		for(int i = 0; i < n + m; i++)
			if(label[i] == -1 && !setlabel(i, i < m ? 0 : label[0]))//greedy: the value of column i is better to be same as the first row, the value of row i-m is better to be same as the first column
				return vector<string>();
		vector<string> ans(n, string(m, '?'));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				ans[i][j] = (label[i + m] ^ label[j]) ? 'Z' : 'N';
		return ans;
	}
};

