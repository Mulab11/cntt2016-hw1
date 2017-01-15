#include <bits/stdc++.h>

using namespace std;

const int maxn = 8,mo = int(1e9) + 9;

int f[maxn + 5][maxn + 5][1 << (maxn * 2)]; 
//一个状态sta，sta[i]=0..3，表示是否存在一条从0走到这个点的和A（B）匹配的路径，类似轮廓线一样存储。

class StringPath
{
public:
	int countBoards(int n, int m, string A, string B)
	{
		int ans = 0;
		f[0][0][3] = 1;
		for(int x = 0;x < n;x ++)
			for(int y = 0;y < m;y ++)
			{
				for(int sta = 0;sta < (1 << (2 * m));sta ++)
					if (f[x][y][sta])
					{
						int up_sta = ((sta >> (2 * y)) & 3),left_sta = 0;
						if (y) left_sta = ((sta >> (2 * (y - 1))) & 3);
						bool ok_a = (up_sta & 1) || (left_sta & 1),ok_b = bool(up_sta & 2) || bool(left_sta & 2);
						//左（上）是否存在一条A（B）的路径
						for(int i = 0;i < 26;i ++)
						{
							int nok_a = ok_a && (i == A[x + y] - 'A'),nok_b = ok_b && (i == B[x + y] - 'A');//这个点能否继续走
							int nsta = sta - (((sta >> (2 * y)) & 3) << (2 * y));
							nsta |= (nok_a + 2 * nok_b) << (2 * y);//更新状态
							(f[x][y + 1][nsta] += f[x][y][sta]) %= mo;
						}
					}
				memcpy(f[x + 1][0],f[x][m],sizeof f[x][m]);//行末直接转移到下一行开头
			}
		for(int sta = 0;sta < (1 << (2 * m));sta ++)
			if ((sta >> (2 * (m - 1))) == 3) ans = (ans + f[n][0][sta]) % mo; //(n-1,m-1)要存在两条路径
		return ans;
	}
};
