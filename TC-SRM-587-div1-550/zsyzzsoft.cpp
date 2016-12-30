#include <algorithm>
using namespace std;
class TriangleXor
{
public:
	int theArea(int w)
	{
		double ans = 0.0, f[70001] = {0}, g[70001] = {0};
		for(int i = 0; i <= w; i++) //计算每一层的面积 
		{
			f[i] = g[i] = (double)w / (w * 2 - i) * (i + 1); //这一层内所有三角形的面积之和 
			if(i > 0) //上一层的每个三角形要被减两次 
				f[i] -= g[i - 1] * 2.0;
			if(i > 1) //上上层的三角形被多减了一次 
				f[i] += g[i - 2];
			if((w - i) % 2 == 0)
				ans += f[i];
		}
		return (int)(ans * w / 2.0);
	}
};