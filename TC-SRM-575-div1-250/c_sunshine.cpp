#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
class TheNumberGameDivOne
{
	public:
	string find(LL n)
	{
		//We can prove that he will lose if and only if n=2k+1 or n=2^(2k+1).
		bool ans=0;
		if(n==1)ans=0;
		else if(n&(n-1))ans=~n&1;
		else while(n)ans^=1,n>>=1;
		return ans?"John":"Brus";
	}
};

