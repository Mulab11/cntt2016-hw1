#include <algorithm>
using namespace std;
const int p = 1000000009;
long long f[8][8][1 << 8][1 << 8];
class StringPath
{
public:
	int n, m;
	bool Valid(int i, int j, int s)
	{
		if(!i)
			return s & 1;
		if(!j)
			return s >> (m - 1);
		return (s & 1) || (s >> (m - 1));
	}
	int Y(int s)
	{
		return ((s << 1) + 1) & ((1 << m) - 1);
	}
	int N(int s)
	{
		return (s << 1) & ((1 << m) - 1);
	}
	int countBoards(int _n, int _m, string a, string b)
	{
		n = _n, m = _m;
		if(a[0] != b[0])
			return 0;
		f[0][0][1][1] = 1;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++) //逐格转移 
			{
				if(i == n - 1 && j == m - 1)
					break;
				int ti = i, tj = j + 1;
				if(tj == m)
					ti++, tj = 0;
				for(int u = 0; u < 1 << m; u++)
				{
					for(int v = 0; v < 1 << m; v++) //到达轮廓线上的每个格子的状态 
					{
						f[i][j][u][v] %= p;
						if(a[ti + tj] == b[ti + tj] && Valid(ti, tj, u) && Valid(ti, tj, v)) //与某个串匹配 
							f[ti][tj][Y(u)][Y(v)] += f[i][j][u][v];
						if(Valid(ti, tj, u) && (!Valid(ti, tj, v) || a[ti + tj] != b[ti + tj]))
							f[ti][tj][Y(u)][N(v)] += f[i][j][u][v];
						if(Valid(ti, tj, v) && (!Valid(ti, tj, u) || a[ti + tj] != b[ti + tj]))
							f[ti][tj][N(u)][Y(v)] += f[i][j][u][v];
						if(!Valid(ti, tj, v) && !Valid(ti, tj, u)) //不匹配
							f[ti][tj][N(u)][N(v)] += f[i][j][u][v] * 26;
						else if(Valid(ti, tj, v) ^ Valid(ti, tj, u))
							f[ti][tj][N(u)][N(v)] += f[i][j][u][v] * 25;
						else if(a[ti + tj] == b[ti + tj])
							f[ti][tj][N(u)][N(v)] += f[i][j][u][v] * 25;
						else
							f[ti][tj][N(u)][N(v)] += f[i][j][u][v] * 24;
					}
				}
			}
		}
		long long ans = 0;
		for(int i = 0; i < 1 << m; i++) //计算答案 
		{
			for(int j = 0; j < 1 << m; j++)
			{
				if(i & 1 && j & 1)
					ans += f[n - 1][m - 1][i][j];
			}
		}
		return ans % p;
	}
};