#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class FindPolygons
{
public:
	double minimumPolygon(int L)
	{
		// 猜想：只需要考虑三角形和四边形就 OK 了
		// 枚举三角形的两条边
		if(L < 3) return -1;
		double A = 1e10;
		for(int a = 1; a <= L; ++a)
			for(int b = a; b <= L - a - b; ++b)
			{
				int c = L - a - b;
				if(a + b <= c) continue;
				ll s = (ll) (a+b+c) * (a+b-c) * (a+c-b) * (b+c-a);
				ll t = sqrt(s) + 0.5;
				if(t * t == s) A = min(A, (double) c - a);
			}
		if(A <= L + 1) return A;
		if(L % 4 == 0) return 0;
		if(L % 2 == 0) return 1;
		return -1;
	}
}	user;
