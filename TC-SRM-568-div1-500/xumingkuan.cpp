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
#include <stack>
using namespace std;
const int MOD = 1000000007;
const int MAXNUM = 18;
class Edge
{
	public:
		int to, v, next;
};
class EqualSums
{
	private:
	int n;//n * n board
	int stx, sty, stv;//board[stx][sty] is stv(not '-').
	Edge e[6060];
	int head[105], en;
	//consider only board[stx][...] and board[...][sty].
	int num[105];//certain value
	pair <int, int> num2[105];// <a, b>: ax + b
	int mnv[2];//min value of board[stx][...] and board[...][sty].
	queue <int> q;//for bfs
	bool visit[105];
	int getpoint(int x, int y) const//board[x][y]
	{
		if(x == stx)
			return y - (y > sty);
		else
			return x - (x > stx) + n - 1;
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
	int calc(int mnv0, int mnv1)//mnv[0] >= mnv0, mnv[1] >= mnv1
	{
		if(mnv1 > mnv[1])//invalid
			return 0;
		const int nowmnv[2] = {mnv0, mnv1};
		//printf("calc %d %d:\n", mnv0, mnv1);
		int ret = 1;
		for(int i = 0; i < 2 * n - 2; i++)
			visit[i] = (num[i] != -1);
		for(int i = 0; i < 2 * n - 2; i++)
			if(!visit[i])//bfs the connected block
			{
				q.push(i);
				num2[i] = make_pair(1, 0);
				visit[i] = true;
				int nowmin = nowmnv[i / (n - 1)], nowmax = MAXNUM;
				while(!q.empty())
				{
					const int now = q.front();
					q.pop();
					for(int j = head[now]; j > 0; j = e[j].next)
						if(!visit[e[j].to])
						{
							visit[e[j].to] = true;
							num2[e[j].to] = make_pair(-num2[now].first, e[j].v - num2[now].second);
							q.push(e[j].to);
							if(num2[e[j].to].first == 1 && nowmnv[e[j].to / (n - 1)] - num2[e[j].to].second > nowmin)//update the interval
								nowmin = nowmnv[e[j].to / (n - 1)] - num2[e[j].to].second;
							if(num2[e[j].to].first == -1 && num2[e[j].to].second - nowmnv[e[j].to / (n - 1)] < nowmax)
								nowmax = num2[e[j].to].second - nowmnv[e[j].to / (n - 1)];
						}
						else if(num2[now].first + num2[e[j].to].first != 0 || num2[now].second + num2[e[j].to].second != e[j].v)//paradox
							return 0;
				}
				if(nowmin > nowmax)//invalid
					return 0;
				ret = (long long)ret * (nowmax - nowmin + 1) % MOD;
			}
		//printf("return %d\n", ret);
		return ret;
	}
	public:
	int count(vector<string> board)
	{
		//init
		n = board.size();
		stx = sty = -1;
		en = 0;
		memset(num, -1, sizeof(num));
		memset(head, -1, sizeof(head));
		mnv[0] = mnv[1] = MAXNUM;
		while(!q.empty())
			q.pop();
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(board[i][j] != '-')
				{
					if(stx == -1)
						stx = i, sty = j, stv = board[i][j] - '0';
					else if(i == stx || j == sty)
						num[getpoint(i, j)] = board[i][j] - '0', q.push(getpoint(i, j));
					else
						insert(getpoint(stx, j), getpoint(i, sty), board[i][j] - '0' + stv);
				}
		while(!q.empty())//bfs
		{
			const int now = q.front();
			q.pop();
			for(int i = head[now]; i > 0; i = e[i].next)
				if(num[e[i].to] == -1)
				{
					if((num[e[i].to] = e[i].v - num[now]) < 0)//invalid
						return 0;
					q.push(e[i].to);
				}
				else if(num[e[i].to] != e[i].v - num[now])//paradox
					return 0;
		}
		for(int i = 0; i < 2 * n - 2; i++)
			if(num[i] != -1 && num[i] < mnv[i / (n - 1)])
				mnv[i / (n - 1)] = num[i];
		long long ans = 0;
		for(int i = 0; i < min(mnv[0], stv); i++)//enumerate mnv[0]
			ans += calc(i, stv - i) - calc(i + 1, stv - i) + MOD;//inclusion-exclusion principle
		ans += calc(min(mnv[0], stv), stv - min(mnv[0], stv));
		return (int)(ans % MOD);
	}
};

