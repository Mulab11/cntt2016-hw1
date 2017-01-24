#include <cstdio>
class AlternateColors2{
public:
	long long countWays(int n, int k){
		return (k+2ll)/3*(n*4-k*2-(k-1)/3*3)/2-((k+2)/3-k%2+1)/2*(2*(n-k)+1)+(k%3==1?(6*n-9*((n+2)/3+(k+2)/3)+9ll)*((n+2)/3-(k+2)/3)/2+(n%3==0):0);
	}
};
