#include <algorithm>
#include <memory.h>
using namespace std;
const int maxn = 100005;
double pl[2][maxn * 10];
int cnt[maxn * 10], q[maxn * 10][2], ed;
class ConvexPolygonGame
{
public:
	double Abs(double a)
	{
		return a < 0 ? -a : a;
	}
	int Morethan(double a) 
	{
		return a >= 0 ? (int)(a + 1.0 + 1.0e-7) : (int)(a + 1.0e-7);
	}
	string winner(vector<int> x, vector<int> y)
	{
		memset(cnt, 0, sizeof(cnt));
		int n = x.size();
		for(int i = 0; i < n; i++)
		{
			int ax = x[i], bx = x[(i + 1) % n];
			ax += maxn, bx += maxn;
			if(ax == bx) //预处理所有横截线的起点终点 
				pl[0][ax] = max(y[i], y[(i + 1) % n]), pl[1][ax] = min(y[i], y[(i + 1) % n]), cnt[ax] = 2;
			else
			{
				double k = ((double)(y[(i + 1) % n] - y[i])) / (bx - ax), b = y[i] - ax * k;
				for(int j = min(ax, bx); j <= max(ax, bx); j++)
				{
					if(j == ax || j == bx)
					{
						if(cnt[j] == 1 && Abs(pl[0][j] - k * j - b) >= 1.0e-7) 
							pl[cnt[j]++][j] = k * j + b;
						if(!cnt[j])
							pl[cnt[j]++][j] = k * j + b;
						continue;
					}
					pl[cnt[j]++][j] = k * j + b;
					if(Abs(int(pl[cnt[j] - 1][j]) - pl[cnt[j] - 1][j]) <= 1.0e-7) 
					{
						q[ed][0] = j, q[ed][1] = (int)pl[cnt[j] - 1][j], ed++;
						if(ed > 2 * maxn)
							return "Masha";
					} 
				}
			}
		}
		for(int i = 0; i < maxn * 2; i++) //计算整点 
		{
			if(cnt[i] <= 1)
				continue;
			double minpl = min(pl[0][i], pl[1][i]);
			double maxpl = max(pl[0][i], pl[1][i]);
			for(int j = Morethan(minpl); maxpl - j >= 1.0e-7; j++)
			{
				q[ed][0] = i;
				q[ed][1] = j;
				ed++;
				if(ed > maxn * 2) 
					return "Masha";
			}
		}
		if(ed <= 2)
			return "Petya";
		if(q[0][0] == q[1][0]) //判断共线 
		{
			bool flag = true;
			for(int i = 0; i < ed; i++)
			{
				if(q[0][0] != q[i][0])
					flag = false;
			}
			return flag ? "Petya" : "Masha";
		}
		double k = ((double)(q[0][1] - q[1][1])) / (q[0][0] - q[1][0]), b = q[0][1] - q[0][0] * k;
		bool flag = true;
		for(int i = 0; i < ed; i++)
		{
			if(Abs(k * q[i][0] + b - q[i][1]) >= 1.0e-7)
				flag = false;
		}
		return flag ? "Petya" : "Masha";
	}
};