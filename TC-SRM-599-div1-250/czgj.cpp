/*
	Greedy.
	1. It costs 1 for every prime factor of A.
	2. It costs log2(q - 1) to raise a prime p to the power of q.
*/
#include <bits/stdc++.h>
using namespace std;

class BigFatInteger {
	public:
	int log2(int x){
		int ret = 0;
		if (x == 0) return -1;
		while (x >>= 1) ++ret;
		return ret;
	}
	int minOperations(int A, int B) {
		int nPrime = 0, maxIndex = 0;
		for (int i = 2; i * i <= A; ++i)
			if (A % i == 0){
				int id = 0; ++nPrime;
				while (A % i == 0) A /= i, ++id;
				maxIndex = max(maxIndex, id);
			}
		if (A > 1) ++nPrime, maxIndex = max(maxIndex, 1);
		return nPrime + log2(B * maxIndex - 1) + 1;
	}
};

/*
	Warae ba ii to omou yo.
*/
