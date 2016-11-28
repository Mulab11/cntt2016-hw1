#include <algorithm>
#include <math.h>
using namespace std;
class CirclesGame
{
public:
	int n, p[50], sg[50];
	bool ap[64];
	void Dfs(int x, int w)
	{
		for(int i = x + 1; i < n; i++)
		{
			if(p[i] == x)
				w ^= sg[i];
		}
		ap[w] = true;
		for(int i = x + 1; i < n; i++)
		{
			if(p[i] == x)
				Dfs(i, w ^ sg[i]);
		}
	}
	string whoCanWin(vector<int> x, vector<int> y, vector<int> r)
	{
		n = r.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = n - 1; j > i; j--)
			{
				if(r[j - 1] < r[j])
					swap(x[j - 1], x[j]), swap(y[j - 1], y[j]), swap(r[j - 1], r[j]);
			}
		}
		for(int i = 0, j; i < n; p[i++] = j) //预处理包含关系 
			for(j = i - 1; j >= 0 && r[i] + sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) >= r[j]; j--);
		int ans = 0;
		for(int i = n - 1; i >= 0; i--)
		{
			for(int j = 0; j < 64; j++)
				ap[j] = false;
			Dfs(i, 0); //递归枚举路径 
			for(sg[i] = 0; ap[sg[i]]; sg[i]++); //计算SG值 
			if(p[i] < 0)
				ans ^= sg[i];
		}
		return ans ? "Alice" : "Bob";
	}
};
