#include <algorithm>
#include <memory.h> 
using namespace std;
const int maxn = 55, maxm = 8;
const int mod = 1000000007;
struct Edge
{
	int v;
	Edge *next;
};
bool broot[maxn];
long long ch[maxn * 2][2], dp[maxn * 2][7000][2];
bool bdp[maxn * 2][7000][2], can[7000];
long long size[7000], ins[maxn], bdcnt;
int mc;
Edge memory[maxn * 10], *edge[maxn];
vector<long long> nx[7000], change[7000];
long long set(long long a, long long b)
{
	if(ins[a] == -1) 
		return ins[a] = b;
	if(ins[a] == b)
		return 0;
	return -1;
}
void AddEdge(int u, int v)
{
	Edge *p = &memory[mc++];
	p->v = v, p->next = edge[u];
	edge[u] = p;
	broot[v] = false;
}
class SimilarNames
{
public:
	long long n, m, power[maxm + 1], root;
	void Build(long long a)
	{
		long long son[100];
		memset(son, -1, sizeof(son));
		long long size = 0;
		for(Edge *next = edge[a]; next; next = next->next)
			son[size++] = next->v;
		for(long long i = 0; i < size; i++) 
        	Build(son[i]);
        long long now = a;
        for(long long i = 0; i < size; i++)
        	ch[now][0] = son[i], ch[now][1] = bdcnt, now = bdcnt, bdcnt++;
	}
	long long Work(long long a, long long b, long long c) //c = 0不能放，c = 1可以放 
	{
		if(bdp[a][b][c])
			return dp[a][b][c];
		bdp[a][b][c] = true;
		if(ch[a][0] == -1) //特判终止情形 
		{
			if(size[b] > 1)
				return dp[a][b][c] = 0;
			if(size[b] == 0)
				return dp[a][b][c] = 1;
			if(b == bdcnt - 1 || c == 0)
				return dp[a][b][c] = 0;
			return dp[a][b][c] = 1;
		}
		dp[a][b][c] = 0;
		for(long long i = 0; i < nx[b].size(); i++)
			dp[a][b][c] += Work(ch[a][0], nx[b][i], 1) * Work(ch[a][1], b - nx[b][i], 0), //不放置的状态转移 
				dp[a][b][c] %= mod;
		if(c == 1)
			for(long long i = 0; i < change[b].size(); i++)
				dp[a][b][c]+= Work(a, change[b][i], 0), //放置时的状态转移 
					dp[a][b][c] %= mod;
		return dp[a][b][c];
	}
	void Dfs(int a, int b, int ws) //预处理可能子状态 
	{
		if(ws == m) 
		{
			if(can[a] && can[b]) 
				nx[a].push_back(b);
			return;
		}
		for(int i = 0; i < 3; i++)
		{
			Dfs(a * 3 + i, b * 3 + i, ws + 1);
			if(i)
				Dfs(a * 3 + i, b * 3, ws + 1);
		}
	}
	int count(vector<string> names, vector<int> info1, vector<int> info2)
	{
		sort(names.begin(), names.end());
		n = names.size(), m = info1.size(), root = n, bdcnt = n + 1;
		for(long long i = 0; i < maxn; i++) 
			broot[i] = true;
		for(long long j = 1; j < n; j++) //预处理前缀 
		{
			for(long long i = j - 1; i >= 0; i--)
			{
				bool flag = true;
				if(names[i].length() >= names[j].length())
					continue;
				for(long long k = 0; k < names[i].size(); k++)
				{
					if(names[i][k] != names[j][k]) 
						flag = false;
				}
				if(flag)
				{
					AddEdge(i,j);
					break;
				}
			}
		}
		for(long long i = 0; i < n; i++) //完成建树 
		{
			if(broot[i])
				AddEdge(root,i);
		}
		power[0] = 1;
		for(long long i = 1; i <= maxm; i++) 
			power[i] = 3 * power[i - 1];
		for(long long i = 0; i < power[m]; i++) //预处理可能状态 
		{
			can[i] = true;
			memset(ins, -1, sizeof(ins));
			long long a, b;
			size[i] = 0;
			for(long long j = 0; j < m; j++)
			{
				if(i / power[j] % 3 == 0) 
					a = set(info1[j], 0), b = set(info2[j], 0);
				else if(i / power[j] % 3 == 1) 
					a = set(info1[j], 0), b = set(info2[j], 1);
				else
					a = set(info1[j], 1), b = set(info2[j], 1);
				size[i] += a + b;
				if(a == -1 || b == -1)
					can[i] = false;
			}		
		}
		Dfs(0, 0, 0);
		for(long long i = 0; i < power[m]; i++) // 预处理可以改变一位达到的情形 
		{
			if(!can[i])
				continue;
			memset(ins, -1, sizeof(ins));
			for(long long j = 0; j < m; j++)
			{
				if(i / power[j] % 3 == 0) 
					set(info1[j], 0), set(info2[j], 0);
				else if(i / power[j] % 3 == 1) 
					set(info1[j], 0), set(info2[j], 1);
				else
					set(info1[j], 1), set(info2[j], 1);	
			}
			long long a[maxm];
			for(long long j = 0; j < n; j++)
			{
				if(ins[j] == 1)
				{
					ins[j] = 0;
					bool flag = true;
					for(long long k = 0; k < m; k++)
					{
						if(ins[info1[k]] == 1)
						{
							if(ins[info2[k]] == 1)
								a[k] = 2;
							else
								flag = false;
						}
						else
						{
							if(ins[info2[k]] == 1)
								a[k] = 1;
							else
								a[k] = 0;
						}
					}
					long long nowsum = 0;
					for(long long k = 0; k < m; k++) 
						nowsum += a[k] * power[k];
					ins[j] = 1;
					if(flag)
						change[i].push_back(nowsum);
				}
			}
		 } 
		memset(bdp, 0, sizeof(bdp));
		memset(ch, -1, sizeof(ch));
		Build(root); //建完全二叉树 
		long long ans = Work(root, power[m] - 1, 0);
		for(long long i = 1; i <= n - size[power[m] - 1]; i++) 
			ans = ans * i % mod; 
		return ans;
	}
};
