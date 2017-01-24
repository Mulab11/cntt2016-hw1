#include <set>
#include <cstdio>
using namespace std;
class PyramidSequences{
public:
	int gcd(int a,int b){return b?gcd(b,a%b):a;}
	long long distinctPairs(int N, int M){
		int g=gcd(--N,--M);return((N/g+1ll)*(M/g+1)+1)/2+(g-1ll)*N/g*M/g;
	}
};
