#include <algorithm>
using namespace std;
const int p = 1000000007;
int f[51][51][3][2], c[2501][51];
class KingdomAndCities
{
public:
	int Work(int j, int x, int y, int z)
	{
		int n = x + y * 2 + z * 3;
		if(n == 0)
			return 0;
		int ret = c[n * (n - 1) / 2][j];
		for(int k = 0; k <= j; k++) //枚举子连通块内部边数 
		{
			int tx = x, ty = y, tz = z;
			if(x)
				tx--;
			else if(y)
				ty--;
			else
				tz--;
			for(int _x = 0; _x <= tx; _x++) //枚举子集，容斥 
			{
				for(int _y = 0; _y <= ty; _y++)
				{
					for(int _z = 0; _x + _y + _z < tx + ty + tz; _z++)
					{
						int cx = _x + x - tx, cy = _y + y - ty, cz = _z + z - tz, cn = cx + cy * 2 + cz * 3;
						ret = (ret + p - (long long)f[k][cx][cy][cz] * c[tx][_x] % p * c[ty][_y] % p * c[tz][_z] % p *
							c[(n - cn) * (n - cn - 1) / 2][j - k] % p) % p; //连通块外任意连边 
					}
				}
			}
		}
		return ret;
	}
	int F(int x, int y, int z, int k)
	{
		if(x < 0 || y < 0 || z < 0 || k < 0)
			return 0;
		return f[k][x][y][z];
	}
	int howMany(int n, int m, int k)
	{
		n -= m;
		if(n <= 0)
			return 0;
		for(int i = 0; i <= n * n; i++)
		{
			c[i][0] = 1;
			if(i <= 50)
				c[i][i] = 1;
			for(int j = 1; j < i && j <= 50; j++)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
		}
		for(int j = 0; j <= k; j++) //总边数 
		{
			for(int x = 0; x <= n; x++) //连通块中包含单点的数量 
			{
				for(int y = 0; y <= 2 && x + y * 2 <= n; y++) //连通块中包含双点组的数量 
				{
					for(int z = 0; z <= 1 && x + y * 2 + z * 3 <= n; z++) //连通块中包含三点组的数量 
						f[j][x][y][z] = Work(j, x, y, z);
				}
			}
		}
		if(m == 0)
			return F(n, 0, 0, k);
		if(m == 1)
			return (long long)F(n - 2, 1, 0, k - 2) * c[n][2] % p;
		return ((long long)F(n, 0, 0, k - 3) * c[n][1] % p +
			(long long)F(n - 2, 1, 0, k - 3) * c[n][2] * 2 % p +
			(long long)F(n - 2, 1, 0, k - 4) * c[n][2] % p +
			(long long)F(n - 4, 2, 0, k - 4) * c[n][4] * 6 % p + 
			(long long)F(n - 3, 0, 1, k - 4) * c[n][3] * 6 % p) % p;
	}
};