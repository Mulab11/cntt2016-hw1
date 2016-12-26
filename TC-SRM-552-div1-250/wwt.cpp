/*
一个三角形假如确定了顶端的颜色，每种颜色需要的个数就确定了。分类讨论，二分一下就好了。
*/
#include <bits/stdc++.h>

using namespace std;

class FoxPaintingBalls
{
public:
	long long theMax(long long R,long long G,long long B,long long N)
	{
		if (N == 1) return R + G + B; //除0的要特判
		long long mi = N * (N + 1) / 2 / 3;
		if (N % 3 != 1) return min(R,min(G,B)) / mi;  //红球数=绿球数=蓝球数
		long long l = 1,r = (1ll << 60),tmp = 0;//只有N%3=1需要二分数量
		for(long long mid;l <= r;)
		{
			mid = l + r >> 1;
			//每个三角形有个球可以多涂一个
			if (min(R,min(G,B)) / mi >= mid && (R + G + B) / mid >= 3 * mi + 1) tmp = mid,l = mid + 1; else	
				r = mid - 1;
		}
		return tmp;
	}
};
