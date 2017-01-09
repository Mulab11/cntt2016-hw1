//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

vector <int> get_vi(vector<string> str) {
  stringstream s;
  for (int i = 0; i < str.size(); i++) s << str[i];

  vector <int> res;
  int u;
  while (s >> u) res.push_back(u);
  return res;
}

int product(int x1, int y1, int x2, int y2, int x0, int y0) { //cross product
  x1 -= x0; y1 -= y0;
  x2 -= x0; y2 -= y0;
  return x1 * y2 - x2 * y1;
}

vector <int> redx, bluex, bluey;

int find (int ax, int pos) { //find in redx from pos to the end, the first element smaller than ax
	int nr = redx.size();
	if (redx[nr - 1] <= ax) return -1;

	int l = pos, r = nr - 1, u = nr - 1;
	while (l <= r) {
		int m = (l + r) / 2;

		if (redx[m] > ax) {
			u = m;
			r = m - 1;
		}
		else l = m + 1;
	}

	return u;
}

class Ear{
public:
	long long getCount(vector <string> _redX, vector <string> _blueX, vector <string> _blueY) {
		redx  = get_vi(_redX);
		bluex = get_vi(_blueX);
		bluey = get_vi(_blueY);

		sort(redx.begin(), redx.end());

		int nr = redx.size();
		int nb = bluex.size();

		long long res = 0;
		//fixed p and q
		for (int p = 0;  p < nb; p++)
			for (int q = 0; q < nb; q ++)
				if (bluey[p] > bluey[q]) {
					int posa = -1;
					for (int u = 0; u < nr; u++)
						if (product(redx[u], 0, bluex[q], bluey[q], bluex[p], bluey[p]) > 0)
							posa = u;

					int posd = -1;
					for (int u = 0; u < nr; u++)
						if (product(redx[u], 0, bluex[q], bluey[q], bluex[p], bluey[p]) < 0) {
							posd = u;
							break;
						}

					int maxb = -1;
					for (int u = 0; u < nr; u++)
						if (redx[u] < bluex[q]) {
							maxb = u;
						}

					if (posa == -1 || posd == -1 || maxb == -1) continue;

					//fixed a
					//b is in rang (a + 1, maxb)
					for (int a = 0; a <= posa; a++)
						if (redx[a] < bluex[p]) {
							int b = a + 1;
							if (redx[b] < bluex[q]) {
								//c is in range (pc, nr - 1) of redx
								int	pc = find(bluex[q], b + 1);
								if (pc == -1) continue;

								//d is in range (pc, nr - 1) of redx
								int pd = find(bluex[p], max(pc + 1, posd));
								if (pd == -1) continue;

								int nd = nr - pd, nc = nr - pc;

								int pr = nd * (nd - 1) / 2 + (nc - nd) * nd;
								res += (maxb - b + 1) * pr;
							}
						}

				}
		return res;
	}
};