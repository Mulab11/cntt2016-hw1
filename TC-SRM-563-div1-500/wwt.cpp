/*
好机智的题。。首先，假设我们操作的牌的集合为{x_i}，那么，只要\sum_{x_i} level_{x_i} <= n，这都是一种合法的操作。
证明？必要性显然，充分性可以这样证。假设我们一开始选最大的x_n来操作，不合法的情况是他能覆盖到x_1（否则直接从后往前即可），
那么我们可以尝试搞x_1，以此类推，假如到了x_{n-1}都不可以，证明level_{x_i}的和>n，
否则我们必然可以找到最后一个不覆盖下一个的位置，然后从这个开始倒着搞。最后就是个01背包了。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

class SpellCards
{
public:
	int f[55];

	int maxDamage(vector<int> level,vector<int> damage)
	{
		//直接背包
		for(int i = 0;i < level.size();i ++)
			for(int j = level.size();j >= level[i];j --)
				f[j] = max(f[j],f[j - level[i]] + damage[i]);
		int ans = 0;
		for(int i = 0;i <= level.size();i ++) ans = max(ans,f[i]);
		return ans;
	}
};
