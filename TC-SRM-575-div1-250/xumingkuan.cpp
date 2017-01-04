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
class TheNumberGameDivOne
{
public:
	string find(long long n)
	{
		if(n & 1)
			return "Brus";
		int cnt = 0;
		while(n > 1)
		{
			if(n & 1)
				return "John";
			n >>= 1, cnt++;
		}
		return cnt & 1 ? "Brus" : "John";
	}
};

