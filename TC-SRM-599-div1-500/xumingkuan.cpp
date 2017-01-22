#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class FindPolygons
{
private:
	int sqr(int x)
	{
		return x * x;
	}
	int gcd(int a, int b)
	{
		return !b ? a : gcd(b, a % b);
	}
	bool u[55][55];
public:
	double minimumPolygon(int L)//worst case: 86ms (test case #62)
	{
		if(L == 2 || (L & 1))
			return -1;
		for(int m1 = 1; m1 * m1 < L / 2; m1++)
			for(int n1 = 1; n1 <= m1 && m1 * m1 + n1 * n1 < L / 2; n1++)
				u[m1][n1] = u[n1][m1] = (gcd(m1, n1) != 1);
		int ans = L;
		//find triangles: suppose there is a point(0, 0), and the other 2 points are in the form of (k(m^2-n^2), 2kmn) (m,n,k > 0; distance to (0, 0) = k(m^2+n^2)) or (x, 0)
		for(int m1 = 1; m1 * m1 < L / 2; m1++)
			for(int n1 = 1; n1 <= m1 && m1 * m1 + n1 * n1 < L / 2; n1++)
			{
				if(u[m1][n1])//calculated
					continue;
				for(int k1 = 1; k1 * (m1 * m1 + n1 * n1) < L / 2; k1++)
				{
					int l1 = k1 * (m1 * m1 + n1 * n1);
					if(max(l1, (L - l1 + 1) / 2) - min(l1, (L - l1) / 2) >= ans)//pruning
						continue;
					int lsum = L - l1, x = k1 * (m1 * m1 - n1 * n1), y = 2 * k1 * m1 * n1, l2;
					int mnl = max(1, max(l1 - ans + 1, (lsum - ans) / 2 + 1)), mxl = min(min(L / 2 - 1, lsum - 1), min(l1 + ans - 1, (lsum + ans - 1) / 2));//pruning
					for(int m2 = 1; m2 * m2 <= mxl; m2++)
						for(int n2 = 1; n2 < m2 && m2 * m2 + n2 * n2 <= mxl; n2++)
						{
							if(u[m2][n2])//calculated
								continue;
							for(int k2 = (mnl - 1) / (m2 * m2 + n2 * n2) + 1; k2 * (m2 * m2 + n2 * n2) <= mxl; k2++)
							{
								int tmp = sqr(lsum - (l2 = k2 * (m2 * m2 + n2 * n2))) - sqr(2 * k2 * m2 * n2 - y);
								if(tmp == sqr(k2 * (m2 * m2 - n2 * n2) - x) || tmp == sqr(k2 * (m2 * m2 - n2 * n2) + x))
									ans = min(ans, max(l1, max(l2, lsum - l2)) - min(l1, min(l2, lsum - l2)));//, printf("(%d,%d) (+-%d,%d)\n", x, y, k2 * (m2 * m2 - n2 * n2), 2 * k2 * m2 * n2);
							}
						}
					for(int i = mnl; i <= mxl && y <= lsum - i; i++)
					{
						int tmp = sqr(lsum - (l2 = i)) - y * y;
						if(tmp == sqr(i - x) || tmp == sqr(i + x))
							ans = min(ans, max(l1, max(l2, lsum - l2)) - min(l1, min(l2, lsum - l2)));//, printf("(%d,%d) (+-%d,0)\n", x, y, i);
					}
					//printf("%d %d\n", l1, ans);
				}
			}
		if(ans == L)//no triangles
			ans = ((L >> 1) & 1);
		return ans;
	}
};

