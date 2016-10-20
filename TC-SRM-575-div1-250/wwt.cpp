#include <bits/stdc++.h>

using namespace std;

class TheNumberGameDivOne
{
public:
	string find(long long n)
	{
		//we can easily find that if n is odd or n is 2^{odd} that the first to move will lose
		if (n == 1) //cautious
			return "Brus";
		if (n & (n - 1)) //small trick if n is 2^k,it should be zero
			return (n & 1) ? "Brus" : "John";
		int c = 0;
		for(;n - 1;n >>= 1) c ++;
		return (c & 1) ? "Brus" : "John";
	}
};