/*
可以很轻易的发现只有当r_h=b_h时，才可能计重。而这种情况是很容易讨论出答案的。
对于其他情况，设用了c个红色，那么蓝色只能是c-1,c,c+1，随便计就好了。
*/
#include <bits/stdc++.h>

using namespace std;

class TheBrickTowerEasyDivOne
{
public:
	int __b,sig;

	int calc(int p)
	{
		int tmp = 0;
		if (sig && p - 1 >= 0 && p - 1 <= __b || p > __b) ++ tmp;
		if (p >= 0 && p <= __b) ++ tmp;
		if (p + 1 <= __b) ++ tmp;
		return tmp;
	} 

	int find(int rc,int rh,int bc,int bh)
	{
		__b = bc;
		if (rh != bh) sig = 1;
		int l = 0,r = min(rc,bc + 1),ans = 0;
		if (r <= 1000) //数据范围小直接暴力，避免边界情况。
		{
			for(int i = l;i <= r;i ++) ans += calc(i);
			return ans - 1;
		}		
		for(int i = 0;i < 3;i ++) ans += calc(i);
		for(int i = 0;i < 3;i ++) ans += calc(r - i);
		ans += (r - 3 - (l + 3) + 1) * (2 + sig);
		return ans - 1;
	}
};
