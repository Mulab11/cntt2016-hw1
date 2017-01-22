#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class BigFatInteger
{
public:
	int minOperations(int A, int B)//O(sqrt(A) + log(B))
	{
		int nump = 0, maxq = 1;//A = p1^q1 * p2^q2 * ... * p_{nump}^q_{nump}
		for(int i = 2; i * i <= A; i++)//factorize
			if(A % i == 0)
			{
				nump++;
				int nowq = 1;
				while((A /= i) % i == 0)
					nowq++;
				if(nowq > maxq)
					maxq = nowq;
			}
		if(A > 1)//big prime
			nump++;
		//now nump = number of operation 1
		for(int i = maxq * B - 1; i; i >>= 1)
			nump++;//operation 2
		return nump;
	}
};

