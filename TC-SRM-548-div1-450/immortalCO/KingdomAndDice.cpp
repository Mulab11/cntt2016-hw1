#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define dmin(a, b) ((a) < (b) ? (a) : (b))
bool f[110][5010];
int max0, max1, lim0, lim1;
void add(int c, int v)
{
	for(int i = max0; i >= 0; --i)
	for(int j = max1; j >= 0; --j)
		if(f[i][j]) f[i + c][j + v] = 1;
	max0 = dmin(max0 + c, lim0);
	max1 = dmin(max1 + v, lim1);
}
class KingdomAndDice
{
public:
	double newFairness(vector<int> A, vector<int> B, int m)
	{
		int n = A.size();
		int base = 0;
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != n; ++j)
				if(A[i] > B[j]) ++base;
		for(int i = 0; i != n; ++i)
			if(!A[i]) ++lim0;
		lim1 = n * n - base;
		f[0][0] = 1;
		vector<int> C;
		for(int i = 0; i != n; ++i)
		{
			if(A[i]) C.push_back(A[i]);
			if(B[i]) C.push_back(B[i]);
		}
		C.push_back(0);
		sort(C.begin(), C.end());
		C.push_back(m + 1);
		for(int i = 1; i != (int) C.size(); ++i)
			if(C[i - 1] + 1 < C[i])
			{
				int count = dmin(C[i] - C[i - 1] - 1, n);
				int value = 0;
				int number = C[i - 1] + 1;
				for(int j = 0; j != n; ++j)
					if(B[j] < number) ++value;
				if(!value) continue;
				int k = 1, v;
				for(; count; count -= v, k <<= 1)
				{
					v = dmin(k, count);
					add(v, v * value);
				}
			}
		long double ans = 1e9, val = 0, tmp;
		for(int i = 0; i <= lim1; ++i)
		{
			for(int j = 0; j <= lim0; ++j)
				if(f[j][i]) goto found;
			continue;
			found:
			tmp = (long double) (i + base) / (n * n);
			if(fabsl(tmp - 0.5) + 1e-9 < ans)
			{
				ans = fabs(tmp - 0.5);
				val = tmp;
			}
		}
		return (double) val;
	}
}	user;