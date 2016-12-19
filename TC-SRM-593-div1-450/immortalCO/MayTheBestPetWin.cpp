#include <bits/stdc++.h>
using namespace std;

class MayTheBestPetWin
{
public:
	int calc(vector<int> A, vector<int> B)
	{
		const int N = A.size();
		int S = 0, T = 0;
		bitset<1 << 20> f; f.set(0);
		for(int i = 0; i != N; ++i)
			f |= f << (A[i] + B[i]), S += (A[i] + B[i]), T += A[i];
		for(int i = (S + 1) >> 1; ; ++i) if(f.test(i))
			return 	i - T;
	}
}	user;
