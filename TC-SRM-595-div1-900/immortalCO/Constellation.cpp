#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

struct Point
{
	int x, y, v;
	Point operator - (const Point& p) const {return (Point) {x - p.x, y - p.y};}
	int operator * (const Point& p) const {return x * p.y - y * p.x;}
} p[60];
bool between(int x, int a, int b) {return (a <= b) ? a <= x && x <= b : b <= x && x <= a;}

class Constellation
{
public:
	double expectation(vector<int> px, vector<int> py, vector<int> pr)
	{
		int n = px.size();
		for(int i = 0; i != n; ++i)
			p[i] = (Point) {px[i], py[i], pr[i]};
		double ans = 0;
		// 对于每一个原点三角形考虑其的贡献
		// 只需要考虑这条边（有向）在凸包上的概率（严格凸包）
		for(int i = 0; i != n; ++i) for(int j = 0; j != n; ++j) if(j != i)
		{
			const Point A = p[i], B = p[j], V = B - A;
			if(!(A * B)) continue;
			double cur = (B * A) * (A.v * B.v / 1000000.0);
			// 对于所有在这条边逆时针的点，或共线但不在这条线段上都不允许出现
			for(int k = 0; k != n; ++k)
				if(i != k && j != k && (V * (p[k] - A) > 0
										|| (V * (p[k] - A) == 0 && between(p[k].x, A.x, B.x) && between(p[k].y, A.y, B.y))))
					cur *= (1000 - p[k].v) / 1000.0;
			ans += cur;
		}
		return ans * 0.5;
	}
}   user;
