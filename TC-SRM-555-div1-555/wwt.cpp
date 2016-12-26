/*
我们只关心有多少行（列）被搞了奇数次。枚举R,C表示有多少行（列） 是奇数，
那么1的个数就是H * W - (X * Y + (H - X) * (W - Y))，方案数也很容易算。
*/
#include <bits/stdc++.h>

using namespace std;

const int mo = 555555555;

class XorBoard
{
public:
	int c[3000][3000];

	int count(int H, int W, int Rcount, int Ccount, int S)
	{
		for(int i = 0;i < 3000;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
		}
		int ans = 0;
		for(int x = 0;x <= H;x ++)
			for(int y = 0;y <= W;y ++)
			{
				if (H * W - (x * y + (H - x) * (W - y)) == S) //1的个数
				{
					int rc = Rcount - x,cc = Ccount - y;
					if ((rc & 1) || (cc & 1)) continue; //假如为奇数必然还有是奇数的行/列
					rc /= 2,cc /= 2;
					int w,co;
					w = c[rc + H - 1][H - 1] * 1ll * c[H][x] % mo; //把次数/2分配到H行
					co = c[cc + W - 1][W - 1] * 1ll * c[W][y] % mo; 
					ans = (ans + w * 1ll * co) % mo;
				}
			}
		return ans;
	}
};
