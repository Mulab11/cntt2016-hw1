/*
暴力枚举区间以及这个区间的字母，枚举在哪里开始分界，预处理一个前缀和就好了。
*/
#include <bits/stdc++.h>

using namespace std;

class ColorfulChocolates
{
public:
	int maximumSpread(string chocolates, int maxSwaps)
	{
		int n = chocolates.size();
		for(int len = n;len;len --)
			for(int r = len - 1;r < n;r ++)
			{
				 
				int l = r - len + 1;
				for(char ch = 'A';ch <= 'Z';ch ++)
				{
					int cl = 0,cr = 0;
					static int ps[105],ps1[105];
					for(int i = l - 1;i >= 0;i --)
						if (chocolates[i] == ch) ps[++ cl] = ps[cl - 1] + i; //维护同色的后缀和
					for(int i = r + 1;i < n;i ++)
						if (chocolates[i] == ch) ps1[++ cr] = ps1[cr - 1] + i; //前缀和
					int mc = (1 << 30),sum = 0,co = 0,cur_c = 0,cur_s = 0;
					for(int p = l;p <= r;p ++)
						if (chocolates[p] != ch) sum += p,co ++;
					for(int p = l;p <= r;p ++) //枚举左右分界线，左边这种颜色的数量和右边颜色的数量都要大于等于内部需要的数量
						if (chocolates[p] != ch)
						{
							if (cur_c <= cl && co - cur_c <= cr) 
								mc = min(mc,cur_s - ps[cur_c] + ps1[co - cur_c] - (sum - cur_s)); //直接算代价
							++ cur_c,cur_s += p;							
						}
					if (cur_c <= cl && co - cur_c <= cr) 
						mc = min(mc,cur_s - ps[cur_c] + ps1[co - cur_c] - (sum - cur_s)); //全在一边的代价
					if (mc <= maxSwaps) return len;
				}
			}
	}
};
