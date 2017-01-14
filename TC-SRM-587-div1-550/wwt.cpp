#include <bits/stdc++.h>

using namespace std;

class TriangleXor
{
public:
	int theArea(int W)
	{
		double ans = 0;
		if (!(W & 1)) ans += W / 4.0;//topmost triangle
		for(int i = 0;i < W;i += 2) //left and right triangle
		{
			double x_0,y_0,x_1,y_1;
			if (!i) x_0 = 0,y_0 = 0; else
				x_0 = 1 / (1.0 / W + 1.0 / i),y_0 = 1.0 / W * x_0;
			x_1 = 1 / (1.0 / W + 1.0 / (i + 1)),y_1 = 1.0 / W * x_1;
			ans += fabs(x_0 * y_1 - x_0 - x_1 * y_0 + x_1);//get the area between point i and point i + 1
		}
		for(int i = 1;i < W;i += 2) //bottom rhumbus
		{
			double x_0,y_0,x_1,y_1;
			x_0 = 1 / (1.0 / W + 1.0 / i),y_0 = 1.0 / W * x_0;
			x_1 = 1 / (1.0 / W + 1.0 / (i + 1)),y_1 = 1.0 / W * x_1;
			ans += (W - 2 * x_0) * (y_1 - y_0);//底乘高（不用除2，计的是四边形面积）
		}
		return int(ans);
	}
};
