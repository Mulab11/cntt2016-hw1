#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class PyramidSequences{
public:
	int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
	LL distinctPairs(int n, int m){
		int g = gcd(-- n, -- m); n /= g, m /= g;
		return LL(n) * m * (g - 1) + (LL(n + 1) * (m + 1) + 1) / 2;
	}
};
