/*
枚举长度。设f[r]表示最后一段以r为结尾，前面全部覆盖完的最小代价。那么f[r]=min(f[l-1]+cost(l,r))，
其中l要满足l->r所有限制的颜色都相同，并且r-l+1>=LEN，cost直接算即可。
*/
#include <bits/stdc++.h>

using namespace std;

class Stamp
{
public:
	int getMinimumCost(string s,int stampCost,int pushCost)
	{
		int ans = (1 << 30);
		for(int l = 1;l <= s.length();l ++)
		{
			int cur = l * stampCost;
			static int f[55];
			memset(f,60,sizeof f);
			f[0] = 0;
			for(int j = 1;j <= s.length();j ++)
			{
				int ned = -1;
				for(int i = j;i;i --)
				{
					if (s[i - 1] != '*')
					{
						if (ned != -1 && ned != s[i - 1]) break;
						ned = s[i - 1];
					}
					int len = j - i + 1;
					if (len < l) continue;//假如长度不满l那么不能放
					f[j] = min(f[j],f[i - 1] + (len / l + bool(len % l)) * pushCost); //一开始先l地放，最后多出一点可以叠上去 
				}
			}
			ans = min(ans,cur + f[s.length()]);
		}
		return ans;
	}
};
