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
using namespace std;
const int MOD = 100007;
const double PI = acos(-1.0);
const int MAXN = 233, MAXM = 55;
class Point
{
	public:
		double x, y;
		Point(){}
		Point(double x, double y): x(x), y(y) {}
		Point operator -(const Point &b) const
		{
			return Point(x - b.x, y - b.y);
		}
};
double det(const Point &a, const Point &b)
{
	return a.x * b.y - a.y * b.x;
}
class FencingPenguins
{
	private:
	int n, m;//number of posts, number of penguins
	Point post[MAXN], penguin[MAXM];
	long long leftof[MAXN][MAXN];//penguins on the left of fence i--->j
	bool ok[MAXN][MAXN];//ok[i][j]: fence i---j
	bool check[MAXM][2];
	int f[MAXN][MAXN][4];//f[i][j]: interval [j, j + i]
	//f[i][j][0]: answer in interval
	//f[i][j][1]: answer in interval with fence (j)---(j+i)
	//f[i][j][2]: the enclosed area with fence (j)---(j+i) contains no penguins
	inline int color_to_int(char col) const
	{
		return isupper(col) ? col - 'A' : col - 'a' + 26;
	}
	bool existpenguin(int i, int j, int k) const//triangle (i, j, k), in counter-clockwise order
	{
		i %= n;
		j %= n;
		k %= n;
		return leftof[i][j] & leftof[j][k] & leftof[k][i];
	}
	bool existpenguin(int i, int j, int k, int l) const//quadrangle (i, j, k, l), in counter-clockwise order
	{
		i %= n;
		j %= n;
		k %= n;
		l %= n;
		return leftof[i][j] & leftof[j][k] & leftof[k][l] & leftof[l][i];
	}
	bool check_invalid_penguin() const
	{
		for(int i = 0; i < n; i++)
			if(leftof[i][(i + 1) % n] != (1ll << m) - 1)
				return true;
		return false;
	}
	public:
	int countWays(int numPosts, int radius, vector<int> x, vector<int> y, string color)
	{
		n = numPosts;
		m = x.size();
		for(int i = 0; i < m; i++)
			penguin[i] = Point(x[i], y[i]);
		for(int i = 0; i < n; i++)
			post[i] = Point(radius * cos(2 * PI * i / n), radius * sin(2 * PI * i / n));
		for(int i = 0; i < n; i++)
		{
			ok[i][i] = false;
			leftof[i][i] = (1ll << m) - 1;//for convenience
			for(int j = i + 1; j < n; j++)
			{
				memset(check, false, sizeof(check));
				ok[i][j] = true;
				for(int k = 0; k < m; k++)
				{
					if(det(penguin[k] - post[j], post[i] - post[j]) > 0)
						leftof[i][j] |= (1ll << k), check[color_to_int(color[k])][0] = true;
					else
						leftof[j][i] |= (1ll << k), check[color_to_int(color[k])][1] = true;
					if(check[color_to_int(color[k])][0] && check[color_to_int(color[k])][1])//fence i---j will divide color[k] into 2 groups
						ok[i][j] = false;
				}
				ok[j][i] = ok[i][j];
			}
		}
		if(check_invalid_penguin())
			return 0;
		memset(f, 0, sizeof(f));
		for(int j = 0; j < n; j++)
			f[0][j][0] = f[1][j][0] = 1;
		for(int i = 2; i < n; i++)//enumerate length
			for(int j = 0; j < n; j++)//enumerate position
			{
				for(int k = j + 1; k < j + i; k++)
				{
					const int nowleft = (k - j == 1 ? 1 : existpenguin(j, j + 1, k - 1, k) ? 0 : f[k - j - 2][(j + 1) % n][0]), nowright = (j + i - k == 1 ? 1 : existpenguin(k, k + 1, j + i - 1, j + i) ? 0 : f[j + i - k - 2][(k + 1) % n][0]);
					int &tmp = existpenguin(j, k, j + i) ? f[i][j][1] : f[i][j][2];//for convenience
					if(ok[j][k % n] && ok[k % n][(j + i) % n])//new enclosure, link j---k, link k---(j+i), transfer from f[k - j - 2][j + 1][0] and f[j + i - k - 2][k + 1][0]
						tmp = (tmp + (long long)nowleft * nowright) % MOD;
					if(ok[j][k % n])//link j---k, transfer from f[k - j - 2][j + 1][0] and f[j + i - k][k][1/2]
					{
						f[i][j][1] = (f[i][j][1] + (long long)nowleft * f[j + i - k][k % n][1]) % MOD;
						tmp = (tmp + (long long)nowleft * f[j + i - k][k % n][2]) % MOD;
					}
					/* //repeat...
					if(ok[k % n][(j + i) % n])//link k---(j+i), transfer from f[k - j][j][1/2] and f[j + i - k - 2][k + 1][0]
					{
						f[i][j][1] = (f[i][j][1] + (long long)f[k - j][j][1] * nowright) % MOD;
						tmp = (tmp + (long long)f[k - j][j][2] * nowright) % MOD;
					}
					*/
					if(!existpenguin(j, k - 1, k, j + i) && ok[k % n][(j + i) % n])//the smaller k where there is fence k---(j+i)
						f[i][j][0] = (f[i][j][0] + (long long)f[k - 1 - j][j][0] * f[j + i - k][k % n][1]) % MOD;
				}
				/* //can't handle situations like j == 1 && i == 5 && there are triangles (1,2,3) and (4,5,6)
				f[i][j][0] = ((existpenguin(j, j + i - 1, j + i) ? 0 : f[i - 1][j][0]) + (existpenguin(j, j + 1, j + i) ? 0 : f[i - 1][(j + 1) % n][0]) - (existpenguin(j, j + 1, j + i - 1, j + i) ? 0 : f[i - 2][(j + 1) % n][0]) + MOD) % MOD;//like 2-d prefix sum
				*/
				if(ok[j][(j + i) % n])//link j---(j+i)
					f[i][j][0] = (f[i][j][0] + f[i][j][1]) % MOD;
				if(!existpenguin(j, j + i - 1, j + i))//when there isn't fence k---(j+i)
					f[i][j][0] = (f[i][j][0] + f[i - 1][j][0]) % MOD;
				//printf("f[%d][%d] = {%d, %d, %d}\n", i, j, f[i][j][0], f[i][j][1], f[i][j][2], existpenguin(j, j + i - 1, j + i));
			}
		return f[n - 1][0][0];
	}
};

