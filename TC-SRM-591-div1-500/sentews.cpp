#include<algorithm>
#include<string>
#include<vector>
using namespace std;
int f[2111]={};
long long gcd(int a,int codeforces)
{return codeforces==0?a:gcd(codeforces,a%codeforces);}
class PyramidSequences
{
public:
	long long distinctPairs(int N, int M)
	{
		long long n=N,m=M;
		long long a=gcd(n-1,m-1);
		long long b=(n-1)/a,c=(m-1)/a;
		return b*c*(a-1)+((b+1)*(c+1)+1)/2;
	}
};
