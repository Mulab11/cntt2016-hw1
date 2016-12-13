#include <algorithm>
using namespace std;
struct Prob
{
	double a, b, c;
	Prob() {a = b = c = 0; }
	Prob(double _a, double _b, double _c) {a = _a, b = _b, c = _c; }
	Prob operator * (double x) const
	{
		return Prob(a * x, b * x, c * x);
	}
	Prob operator / (double x) const
	{
		return Prob(a / x, b / x, c / x);
	}
	Prob &operator += (const Prob &_p)
	{
		return a += _p.a, b += _p.b, c += _p.c, *this;
	}
};
double f[51][51][51], h[51][51][51];
Prob g[51][51][51];
class RockPaperScissors
{
public:
	double Calc(Prob p)
	{
		return max(p.a + p.c * 3.0, max(p.b + p.a * 3.0, p.c + p.b * 3.0));
	}
	double bestScore(vector<int> a, vector<int> b, vector<int> c)
	{
		int n = a.size();
		h[0][0][0] = 1.0;
		for(int i = 0; i < n; i++) 
		{
			for(int x = i + 1; x >= 0; x--)
			{
				for(int y = i + 1 - x; y >= 0; y--)
				{
					for(int z = i + 1 - x - y; z >= 0; z--) //g[x][y][z]: 已经掷出了x个石头y个布z个剪刀，在其余骰子中掷出石头、剪刀、布的概率 
					{
						g[x][y][z] += Prob(a[i], b[i], c[i]) / (a[i] + b[i] + c[i]) * h[x][y][z];
						if(x)
							g[x][y][z] += g[x - 1][y][z] * ((double)a[i] / (a[i] + b[i] + c[i]));
						if(y)
							g[x][y][z] += g[x][y - 1][z] * ((double)b[i] / (a[i] + b[i] + c[i]));
						if(z)
							g[x][y][z] += g[x][y][z - 1] * ((double)c[i] / (a[i] + b[i] + c[i]));
						if(x)
							h[x][y][z] += h[x - 1][y][z] * ((double)a[i] / (a[i] + b[i] + c[i]));
						if(y)
							h[x][y][z] += h[x][y - 1][z] * ((double)b[i] / (a[i] + b[i] + c[i]));
						if(z)
							h[x][y][z] += h[x][y][z - 1] * ((double)c[i] / (a[i] + b[i] + c[i]));
					}
				}
			}
		}
		f[0][0][0] = 1.0;
		double ans = 0.0;
		for(int x = 0; x < n; x++)
		{
			for(int y = 0; x + y < n; y++)
			{
				for(int z = 0; x + y + z < n; z++) //f[x][y][z]: 已经掷出了x个石头y个布z个剪刀的概率 
				{
					if(!f[x][y][z])
						continue;
					g[x][y][z] = g[x][y][z] / h[x][y][z] / (n - x - y - z); //标准化概率 
					f[x + 1][y][z] += f[x][y][z] * g[x][y][z].a;
					f[x][y + 1][z] += f[x][y][z] * g[x][y][z].b;
					f[x][y][z + 1] += f[x][y][z] * g[x][y][z].c;
					ans += Calc(g[x][y][z]) * f[x][y][z]; //计算本轮期望 
				}
			}
		}
		return ans;
	}
};