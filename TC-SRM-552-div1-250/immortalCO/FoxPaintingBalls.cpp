#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll min3(ll A, ll B, ll C) {return A < B ? A < C ? A : C : B < C ? B : C;}

class FoxPaintingBalls
{
public:
	ll theMax(ll A, ll B, ll C, ll N)
	{
		N = N * (N + 1) / 2;
		if(N == 1) return A + B + C;
		if(N % 3 == 0) return N /= 3, min3(A / N, B / N, C / N);
		return min((A + B + C) / N, min3(A / (N / 3), B / (N / 3), C / (N / 3)));
	}
}	user;
