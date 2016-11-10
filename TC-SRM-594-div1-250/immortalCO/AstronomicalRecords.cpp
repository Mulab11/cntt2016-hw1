#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int f[60][60];

class AstronomicalRecords
{
public:
	int minimalPlanets(vector<int> A, vector<int> B)
	{
		int n = A.size(), m = B.size();
		int ans = 0;
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != m; ++j)
			{
				for(int a = 0; a != i; ++a)
					for(int b = 0; b != j; ++b)
						if((ll) A[i] * B[b] == (ll) A[a] * B[j])
							f[i][j] = max(f[i][j], f[a][b]);
				ans = max(ans, ++f[i][j]);
			}
		return n + m - ans;
	}
}   user;
