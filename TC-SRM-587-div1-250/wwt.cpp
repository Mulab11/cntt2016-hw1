#include <bits/stdc++.h>

using namespace std;

const int maxn = 2001005;

bitset<maxn> f;

class JumpFurther
{
public:
	int furthest(int N, int badStep)
	{
		f[0] = 1;
		for(int i = 1;i <= N;i ++)
		{
			f |= (f << i); //move i steps,just use bitset to speed up
			if (badStep < maxn) f[badStep] = 0; //we can't walk to badStep
		}
		int mx = 0;
		for(int i = maxn - 1;i;i --) //get the topmost step
			if (f[i]) {mx = i;break;}
		return mx;
	}
};
