#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define inf 1000000000
using namespace std;
class PyramidSequences
{
	inline int gcd(int a,int b)
	{
		return b==0?a:gcd(b,a%b);
	}
public:
	long long distinctPairs(int n,int m)
	{
		n--;
		m--;
		int g=gcd(n,m);
		//分别统计每个循环中只出现一次的数对和出现多次的数对 
		return (L)n*m/g/g*(g-1)+(L)(n/g+1)*(m/g+1)/2;
    }
};
