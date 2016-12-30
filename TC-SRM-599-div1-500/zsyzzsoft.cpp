#include <algorithm>
#include <memory.h>
using namespace std;
int ints, inte[30000][3], sq[6500000];
class FindPolygons
{
public:
	int gsqu(int a)
	{
		if(a > 6500000)
			return -1;
		return sq[a];
	}
	int max(int a,int b,int c)
	{
		if(a > b && a > c)
			return a;
		if(b > c)
			return b;
		return c;
	}
	int min(int a,int b,int c)
	{
		if(a < b && a < c)
			return a;
		if(b < c)
			return b;
		return c;
	}
	double minimumPolygon(int l)
	{
		memset(sq, -1, sizeof(sq));
		for(int i = 0; i <= l / 2; i++) //预处理距离 
			sq[i * i] = i;
		for(int i = 0; i < l / 2; i++)
		{
			for(int j = 0; j < l / 2; j++)
			{
				int dist = i * i + j * j;
				if(dist > (l * l / 4))
					continue;
				int nows = gsqu(dist);
				if(nows != -1)
					inte[ints][0] = i, inte[ints][1] = j, inte[ints++][2] = nows;
			}
		}
		if(l == 2)
			return -1.0;
		if(l & 1)
			return -1.0;
		int ans = l / 2 % 2;
		bool flag = false;
		for(int i = 0; i < ints; i++) //枚举答案
		{
			for(int j = i + 1; j < ints; j++)
			{
				int dist = gsqu((inte[i][0] - inte[j][0]) * (inte[i][0] - inte[j][0]) + (inte[i][1] - inte[j][1]) * (inte[i][1] - inte[j][1]));
				if(dist == -1)
					continue;
				if(dist + inte[i][2] + inte[j][2] != l)
					continue;
				if(max(inte[i][2], inte[j][2], dist) * 2 >= l)
					continue;
				int nans = max(inte[i][2], inte[j][2], dist) - min(inte[i][2], inte[j][2], dist);
				if(!flag)
					flag = true, ans = nans;
				else if(nans < ans)
					ans = nans;
			}
		}
		return ans;
	}
};