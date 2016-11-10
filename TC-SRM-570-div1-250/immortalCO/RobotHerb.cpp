#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

class RobotHerb
{
public:
	ll getdist(int t, vector<int> a)
	{
		const int CX[] = {0, 1, 0, -1};
		const int CY[] = {1, 0, -1, 0};
		ll x = 0, y = 0;
		int d = 0;
		for(int i = 0; i != (int) a.size(); ++i)
		{
			x += a[i] * CX[d];
			y += a[i] * CY[d];
			d = (d + a[i]) % 4;
		}
		ll X = 0, Y = 0; int D = 0;
		ll S = 0, T = 0;
		for(int i = 0; i != 4; ++i)
		{
			if(t % 4 == i) S = X, T = Y;
			switch(D)
			{
				case 0:	X += x, Y += y; break;
				case 1: X += y, Y -= x; break;
				case 2: X -= x, Y -= y; break;
				case 3: X -= y, Y += x; break;
			};
			D = (D + d) % 4;
		}
		S += X * (t / 4);
		T += Y * (t / 4);
		return max(S, -S) + max(T, -T);
	}
}	user;
