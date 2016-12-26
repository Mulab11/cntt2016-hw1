/*
经典二元关系。每个点拆成i,i'，然后对这个图黑白染色，假如一个点是黑的，那么s->i表示i选，
i->t表示i不选,s->i'表示i'不选,i'->t表示i'选（i'选表示第二个条件满足），那么假如一个j与i相邻，我们就让j与i'连边，
同时，我们让i与i'连一条profit[i]的边，初始ans=2*profit[i]，那么做最小割时，假如i和i'同时满足了，我们会减掉一个profit，
不会计多，其他的限制同理。
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 21005;
const int xy[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

struct Node
{
	int To,Next,Flow;
	Node(void){}
	Node(int a,int b,int c) : To(a),Next(b),Flow(c){}
}E[MAXN * 35];

int D[MAXN],Count[MAXN],Cur[MAXN],Final[MAXN],pri[105][105],W[105][105],N,M,S,T,tot;

void link(int u,int v,int f)
{
	E[++ tot] = Node(v,Final[u],f),Final[u] = tot;
	E[++ tot] = Node(u,Final[v],0),Final[v] = tot;
}

int Dfs(int Now,int Flow)
{
	if (Now == T) return Flow;
	int Use = 0;
	for(int i = Cur[Now];i;i = E[i].Next)
	if (E[i].Flow > 0 && D[E[i].To] + 1 == D[Now])
	{
		Cur[Now] = i;
		int Tmp = Dfs(E[i].To,min(E[i].Flow,Flow - Use));
		Use += Tmp,E[i].Flow -= Tmp,E[i ^ 1].Flow += Tmp;
		if (Use == Flow || D[S] == T + 1) return Use;
	}
	Cur[Now] = Final[Now];
	if (!(-- Count[D[Now]])) D[S] = T + 1;
	++ Count[++ D[Now]];
	return Use;
}

class SurroundingGame
{
public:
	int get_num(char c)
	{
		if (c >= '0' && c <= '9') return c - 48;
		if (c >= 'a' && c <= 'z') return c - 'a' + 10;
		if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
	}

	int maxScore(vector <string> cost, vector <string> benefit)
	{
		N = cost.size(),M = cost[0].length();
		int Ans = 0;
		tot = 1;S = 0,T = N * M * 2 + 1;
		for(int i = 1;i <= N;i ++)	
			for(int j = 1;j <= M;j ++) W[i][j] = get_num(cost[i - 1][j - 1]);
		for(int i = 1;i <= N;i ++)
			for(int j = 1;j <= M;j ++)
			{
				int op = (i - 1) * M + j;
				pri[i][j] = get_num(benefit[i - 1][j - 1]);
				//根据颜色分别连S/T
				if ((i + j) & 1) link(op,op + N * M,pri[i][j]),link(op,T,W[i][j]),link(S,op,pri[i][j]),link(op + N * M,T,pri[i][j]); 
					else
					link(S,op,W[i][j]),link(op + N * M,op,pri[i][j]),link(op,T,pri[i][j]),link(S,op + N * M,pri[i][j]);
				Ans += 2 * pri[i][j];
				if ((i + j) & 1)
				for(int k = 0;k < 4;k ++)//相邻点的限制
				{
					int nx = i + xy[k][0],ny = j + xy[k][1],ot = (nx - 1) * M + ny;
					if (!nx || !ny || nx > N || ny > M) continue;
					if ((i + j) & 1) link(ot,op + N * M,1 << 30),link(ot + N * M,op,1 << 30);
				}
			}
		memcpy(Cur,Final,sizeof Cur);
		Count[0] = T + 1;
		while (D[S] < T + 1) Ans -= Dfs(S,1 << 30);
		return Ans;
	}
};
