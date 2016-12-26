#include <algorithm>
#include <memory.h>
#include <math.h>
using namespace std;
class Constellation
{
public:
	double Abs(double a)
	{
		return a >= 0 ? a : -a;
	}
	double expectation(vector <int> x, vector <int> y, vector <int> prob)
	{
		int pl[55][2];
		double ans = 0;
		int n = x.size();
		for(int i = 0; i < n; i++)
			pl[i][0] = x[i] - 105, pl[i][1] = y[i] - 150;
		for(int i = 0; i < n; i++) //枚举逆时针点对 i, j 
			for(int j = 0; j < n;j++)
			{
				if(i == j) 
					continue;
				int dir = -1;
				if(pl[i][0] < pl[j][0]) //判断同异侧 
					dir = 1;
				if(pl[i][0] == pl[j][0] && pl[i][1] > pl[j][1]) 
					dir = 1;
				double posi = ((double)(prob[i] * prob[j])) / 1.0e6;
				double a, b, c;
				if(pl[i][0] == pl[j][0]) 
					a = 1, b = 0, c = -pl[i][0];
				else
					a = ((double)(pl[i][1] - pl[j][1])) / (pl[i][0] - pl[j][0]), b = -1, c = pl[i][1] - pl[i][0] * a;
				double o = c;
				for(int k = 0; k < n; k++)
				{
					if(k == i || k == j) 
						continue;
					double nowpl = a * pl[k][0] + b * pl[k][1] + c;
					bool flag = true;
					if(abs(nowpl) <= 1.0e-10) //判断能否有k 
					{
						if(b != 0)
						{
							if((pl[k][0] - pl[i][0]) * (pl[k][0] - pl[j][0]) < 0)
								flag = false;
						}
						else if((pl[k][1] - pl[i][1]) * (pl[k][1] - pl[j][1]) < 0)
							flag = false;
					}
					else if((nowpl * o * dir) < 0)
						flag = false;
					if(!flag)
						posi *= (1000 - prob[k]), posi /= 1000;
				}
				double nans = posi * dir; //计算面积 
				double l1, l2, l3;
				l1 = sqrt(pl[i][0] * pl[i][0] + pl[i][1] * pl[i][1]);
				l2 = sqrt(pl[j][0] * pl[j][0] + pl[j][1] * pl[j][1]);
				l3 = sqrt((pl[j][0] - pl[i][0]) * (pl[j][0] - pl[i][0]) + (pl[j][1] - pl[i][1]) * (pl[j][1] - pl[i][1]));
				double p = (l1 + l2 + l3) / 2;
				double area = sqrt(p * (p - l1) * (p - l2) * (p - l3));
				ans += area * nans;
			} 
		
		return ans;
	}
};