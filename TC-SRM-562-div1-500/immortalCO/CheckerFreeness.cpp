#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#include <sstream>

int count_str(const string& s, char v) {return count(s.begin(), s.end(), v);}

struct Point
{
	int x, y;
	Point operator - (const Point& p) const
	{
		return (Point) {x - p.x, y - p.y};
	}
	ll operator * (const Point& p) const
	{
		return (ll) x * p.y - (ll) y * p.x;
	}
} p[510], q[510];

struct Sort
{
	Point *p, v;
	bool operator < (const Sort& s) const
	{
		return v * s.v > 0;
	}
} pr[510], pl[510];

class CheckerFreeness
{
public:
	string isFree(vector<string> pX, vector<string> pY, vector<string> qX, vector<string> qY)
	{
		stringstream X, Y;
		X.str(""), Y.str("");
		for(int i = 0; i != (int) pX.size(); ++i) X << pX[i];
		for(int i = 0; i != (int) pY.size(); ++i) Y << pY[i];
		const int N = count_str(X.str(), ' ') + 1;
		for(int i = 0; i != N; ++i) X >> p[i].x, Y >> p[i].y;
		
		X.str(""), Y.str("");
		X.clear(), Y.clear();
		for(int i = 0; i != (int) qX.size(); ++i) X << qX[i];
		for(int i = 0; i != (int) qY.size(); ++i) Y << qY[i];
		const int M = count_str(X.str(), ' ') + 1;
		for(int i = 0; i != M; ++i) X >> q[i].x, Y >> q[i].y;
		
		// 枚举两个黑点
		for(int i = 0; i != N; ++i) for(int j = i + 1; j != N; ++j) //if(i != j)
		{
			const Point A = p[i], B = p[j], AB = B - A;
			int L = 0, R = 0;
			for(int k = 0; k != M; ++k)
			{
				((q[k] - A) * AB > 0 ? pr[R++] : pl[L++]) = (Sort) {q + k, q[k] - A};
			}
			if(!L || !R) continue;
			
			sort(pl, pl + L);
			sort(pr, pr + R);
			Point v = AB;
			int k = 0;
			for(int i = 0; i != R; ++i)
			{
				for(; k != L && pr[i].v * pl[k].v > 0; ++k)
				{
					Point w = (*(pl[k].p) - B);
					if(v * w > 0) v = w;
				}
				if((*pr[i].p - B) * v < 0) return "NO";
			}
		}
		return "YES";
		
	}
}	user;
