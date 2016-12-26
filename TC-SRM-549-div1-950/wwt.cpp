/*
暴力枚举不同的立方体的样子，具体而言，就是暴力枚举每一层由哪些颜色组成，每种颜色覆盖了下一层的哪些颜色，
判断合法可以用网络流来判（相当于对于>1层的颜色都有一条到第1层的路），求方案就枚举排列暴力求。
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50;

vector<int> All[MAXN],Lk[MAXN];
int A[MAXN],Bel[MAXN],Cnt[MAXN],N,Minway,Maxway,M,ans;

namespace Flow
{
	const int MAXN = 55;

	struct Node
	{
		int To,Next,Flow;

		Node(void){}
		Node(int a,int b,int c) : To(a),Next(b),Flow(c){}
	}E[MAXN * MAXN * 10];

	int D[MAXN],Final[MAXN],Count[MAXN],S,T,tot;

	void Link(int u,int v,int f)
	{
		E[++ tot] = Node(v,Final[u],f),Final[u] = tot;
		E[++ tot] = Node(u,Final[v],0),Final[v] = tot;
	}

	int Dfs(int Now,int Flow)
	{
		if (Now == T) return Flow;
		int Use = 0;
		for(int i = Final[Now];i;i = E[i].Next)
			if (E[i].Flow > 0 && D[E[i].To] + 1 == D[Now])
			{
				int tmp = Dfs(E[i].To,min(Flow - Use,E[i].Flow));
				Use += tmp,E[i].Flow -= tmp,E[i ^ 1].Flow += tmp;
				if (Flow == Use) return Use;
			}
		if (!(-- Count[D[Now]])) D[S] = T + 1;
		++ Count[++ D[Now]];
		return Use;
	}

	int In[MAXN],Out[MAXN];

	bool Ok() //判断一种方法是否合法，相当于每种颜色在他上面的块数等于在下面的块数（除了第一层）
	{
		tot = 1;
		memset(D,0,sizeof D),memset(Final,0,sizeof Final),memset(Count,0,sizeof Count);memset(In,0,sizeof In),memset(Out,0,sizeof Out);
		S = 0,T = 2 * N + 1;
		int all = 0;
		for(int i = 1;i <= N;i ++)
			for(int j = 0;j < Lk[i].size();j ++) 
				Link(Lk[i][j],i + N,1 << 30),In[i] ++,Out[Lk[i][j]] ++;
		for(int i = 1;i <= N;i ++) {if (A[i] - Out[i] < 0) return 0;Link(S,i,A[i] - Out[i]);}
		for(int i = 1;i <= N;i ++) {if (A[i] - In[i] < 0) return 0;Link(i + N,T,A[i] - In[i]);}
		Count[0] = T + 1;
		while (D[S] < T + 1) all -= Dfs(S,1 << 30);
		for(int i = 1;i <= N;i ++)
			if (Bel[i] > 1)
				for(int j = Final[i + N];j;j = E[j].Next)
					if (E[j].To == T && E[j].Flow > 0) return 0;
		return 1;
	}
}

int cnt,Use[MAXN];

void Perm(int Now) //暴力求方案数
{
	if (Now > N) 
	{
		for(int j = 1;j <= N;j ++) if (!Use[j]) return;
		cnt ++;
	} else
	{
		for(int i = 1;i <= N;i ++)
			if (!Use[i])
			{
				bool f = 1;
				for(int j = 0;j < Lk[i].size();j ++) if (Use[Lk[i][j]]) {f = 0;break;}
				if (!f) return;
				Use[i] = 1;
				Perm(Now + 1);
				Use[i] = 0;
			}
	}
}

int Get()
{
	cnt = 0;
	Perm(1);
	return cnt;
}

void Check()
{
	if (Flow::Ok())
	{
		int v = Get();
		if (v >= Minway && v <= Maxway) ans ++;
	}
}

void Search(int Now) //枚举层与层之间哪些颜色盖住哪些颜色
{
	if (Now > N) Check(); else
	{
		Lk[Now].clear();
		if (Bel[Now] == 1) {Search(Now + 1);return;}
		for(int i = 1;i < (1 << Cnt[Bel[Now] - 1]);i ++)
		{
			Lk[Now].clear();
			for(int j = 0;j < Cnt[Bel[Now] - 1];j ++) if (i & (1 << j)) 
				Lk[Now].push_back(All[Bel[Now] - 1][j]);
			Search(Now + 1);
		}
	}
}

void Test(int sta) 
{
	M = sta;
	for(int i = 1;i <= sta;i ++) All[i].clear(),Cnt[i] = 0;
	for(int i = 1;i <= N;i ++) 
		All[Bel[i]].push_back(i);
	for(int i = 1;i <= sta;i ++) Cnt[i] = All[i].size();
	Search(1);
}

void Dfs(int Now,int Cur) //枚举每一层放了哪些颜色
{
	if (Cur == (1 << N) - 1) Test(Now - 1); else
	{
		for(int s = 1;s < (1 << N);s ++)
			if (Cur & s) continue; else
			{
				for(int i = 0;i < N;i ++) if (s & (1 << i)) Bel[i + 1] = Now;
				Dfs(Now + 1,Cur | s);
				for(int i = 0;i < N;i ++) if (s & (1 << i)) Bel[i + 1] = 0;
			}
	}
}

class CosmicBlocks
{
public:
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
	{
		N = blockTypes.size();
		Minway = minWays,Maxway = maxWays;
		for(int i = 1;i <= N;i ++)
			A[i] = blockTypes[i - 1];
		Dfs(1,0);
		return ans;
	}
};
