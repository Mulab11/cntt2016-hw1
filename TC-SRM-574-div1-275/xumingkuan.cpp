#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class TheNumberGame
{
public:
	string determineOutcome(int A, int B)
	{
		int pB = 1;//pB is min power of 10 greater than B
		int revB = 0;//revB is reverse of B
		while(pB <= B)
		{
			revB = revB * 10 + B / pB % 10;
			pB *= 10;
		}
		for(int i = 1; (long long)i * min(B, revB) <= A; i *= 10)
			if(A / i % pB == B || A / i % pB == revB)//a includes B or revB
				return "Manao wins";
		return "Manao loses";
	}
};

