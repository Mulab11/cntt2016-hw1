#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int mo = 555555555;

class XorBoard
{
public : 
	int C[3115][3115], n;

	inline void upd(int & x, int y)
	{
		(x += y) >= mo ? x -= mo : 0;
	}

	int count(int H, int W, int Rc, int Cc, int S)
	{
		n = max(H + Rc, W + Cc);

		C[0][0] = 1;
		rep (i, 1, n)
		{
			C[i][0] = 1;
			rep (j, 1, i)
				(C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) >= mo ? C[i][j] -= mo : 0;
		}

		int ans = 0;

		for (int i = Rc % 2, up = min(Rc, H); i <= up; i += 2)
		{
			if (H == i * 2)
			{
				if (W * i == S)
				{
					int p = (LL) C[H][i] * C[(Rc - i) / 2 + H - 1][H - 1] % mo;
					upd(ans, (LL) p * C[Cc + W - 1][W - 1] % mo);
				}
			}
			else if ((S - W * i) % (H - i * 2) == 0)
			{
				int j = (S - W * i) / (H - i * 2);
				if (j >= 0 && j <= Cc && (j & 1) == (Cc & 1))
				{
					int p = (LL) C[H][i] * C[(Rc - i) / 2 + H - 1][H - 1] % mo;
					int q = (LL) C[W][j] * C[(Cc - j) / 2 + W - 1][W - 1] % mo;
					upd(ans, (LL) p * q % mo);
				}
			}
		}

		return ans;
	}
};
