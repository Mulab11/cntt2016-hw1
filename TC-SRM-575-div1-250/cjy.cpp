#include<bits/stdc++.h>
using namespace std;
int k;
class TheNumberGameDivOne
{
	public:
		string find(long long n)
		{
			if(n&(n-1))return n%2?"Brus":"John";
			while(n-1)n/=2,k++;
			return k%2||!k?"Brus":"John";
		}
};
