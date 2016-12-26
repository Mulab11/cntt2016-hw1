#include <algorithm>
using namespace std;
int que[50], d[50];
class TravelOnMars
{
public:
	int Dist(int a, int b, int n)
	{
		return min(abs(a - b), abs(n - abs(a - b)));
	}
	int minTimes(vector<int> range, int s, int t)
	{
		int n = range.size();
		for(int i = 0; i < n; i++)
			d[i] = -1;
		d[s] = 0;
		que[0] = s;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(int i = 0; i < n; i++)
			{
				if(d[i] < 0 && Dist(i, cur, n) <= range[cur])
					d[que[r++] = i] = d[cur] + 1;
			}
		}
		return d[t];
	}
};