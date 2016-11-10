#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <sstream>

int A[310][310], B[310][310];
int cntA[310], cntB[310];

class TreeUnion
{
public:
	double expectedCycles(vector<string> ea, vector<string> eb, int k)
	{
		if(k == 3) return 0;
		stringstream inA, inB;
		for(int i = 0; i != (int) ea.size(); ++i) inA << ea[i];
		for(int i = 0; i != (int) eb.size(); ++i) inB << eb[i];
		string inpA = inA.str();
		int N = count(inpA.begin(), inpA.end(), ' ') + 2;
		for(int i = 0; i != N; ++i)
			memset(A[i], 63, N << 2),
			memset(B[i], 63, N << 2),
			A[i][i] = B[i][i] = 0;
		for(int i = 1; i != N; ++i)
		{
			int T;
			inA >> T; A[i][T] = A[T][i] = 1;
			inB >> T; B[i][T] = B[T][i] = 1;
		}
		for(int k = 0; k != N; ++k)
			for(int i = 0; i != N; ++i)
				for(int j = 0; j != N; ++j)
					A[i][j] = min(A[i][j], A[i][k] + A[k][j]),
					B[i][j] = min(B[i][j], B[i][k] + B[k][j]);
		for(int i = 0; i != N; ++i)
			for(int j = i + 1; j != N; ++j)
				++cntA[A[i][j]],
				++cntB[B[i][j]];
		double ans = 0;
		for(int p = 1; p + 2 < k; ++p)
		{
			int q = k - 2 - p;
			ans += (cntA[p] * cntB[q]) * 2.0 / (N * (N - 1));
		}
		return ans;
	}
}	user;
