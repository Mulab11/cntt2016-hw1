#include <bits/stdc++.h>

using namespace std;

class FoxAndAvatar
{
public:
	int ans,w;

	int take(int n,int r,int x,int y)
	{
		//总共有n个数，从第r行开始数，第x到y列的有数的位置数
		return ((n - 1) / w - r) * (y - x + 1) + min((n - 1) % w + 1,y + 1) - min((n - 1) % w + 1,x);
	}

	bool move_one_step(int n,int x)
	{
		//up
		if (x == n - 1 && x % w == 0) return 1;
		//down
		if (w == 1 && !x) return 1;
		//left_1
		if (n <= w && x == n - 1) return 1;
		//left_2
		if (n / w < 2 && x == w - 1) return 1;
		//right
		if (n <= w && !x) return 1;
		return 0;
	}

	void dfs(int step,int n,int x)
	{
		if (n == 1) ans = min(ans,step); else
			if (move_one_step(n,x)) ans = min(ans,step + 1); else
			{
				if (step + 2 >= ans) return;
				//pick the rectangle above x
				int r = x / w;
				for(int i = 1;i <= r;i ++)
					for(int j = 1;j <= w;j ++)
						dfs(step + 1,n - i * j,x - i * j);
				//pick the rectangle under x
				dfs(step + 1,(n - 1) / w == r ? n : (r + 1) * w,x);
				//pick the rectangle on the left of x
				for(int i = 1;i <= x % w;i ++)
					for(int j = 1;j <= r + 1;j ++)
						dfs(step + 1,n - take(n,r - j + 1,x % w - i,x % w - 1),x - i * j);
				//pick the rectangle on the right of x
				for(int i = 1;i <= w - x % w - 1;i ++)
					for(int j = 1;j <= r + 1;j ++)
						dfs(step + 1,n - take(n,r - j + 1,x % w + 1,x % w + i),x - (j - 1) * i);
			}
	}

	int minimalSteps(int n,int width,int x)
	{
		x --;
		w = width;
		ans = 4;
		dfs(0,n,x);
		return ans;
	}
};
