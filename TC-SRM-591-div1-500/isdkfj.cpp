#include <bits/stdc++.h>

using namespace std;


class PyramidSequences {
public:
	long long distinctPairs(int N, int M) {
		--N,--M;
		int g=__gcd(N,M);
		N/=g;M/=g;
		return (1ll*(N+1)*(M+1)+1)/2+1ll*(g-1)*N*M;//经过多次+经过一次 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
