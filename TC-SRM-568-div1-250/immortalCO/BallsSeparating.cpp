#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int mx3(int a, int b, int c) {return a > b ? (a > c ? a : c) : (b > c ? b : c);}

class BallsSeparating
{
public:
	int minOperations(vector<int> A, vector<int> B, vector<int> C)
	{
		int N = A.size(), R = 1 << 30;
		if(N < 3) return -1;
		for(int a = 0; a != N; ++a)
			for(int b = 0; b != N; ++b) if(b != a)
				for(int c = 0; c != N; ++c) if(c != a && c != b)
				{
					int T = B[a] + C[a] + A[b] + C[b] + A[c] + B[c];
					for(int i = 0; i != N; ++i)
						if(i != a && i != b && i != c)
							T += A[i] + B[i] + C[i] - mx3(A[i], B[i], C[i]);
					if(T < R) R = T;
				}
		return R;
	}
}	user;
