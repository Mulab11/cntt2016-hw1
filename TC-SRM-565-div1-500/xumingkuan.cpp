#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <queue>
using namespace std;
class TheDivisionGame
{
	private:
	int number[1010101];//temporarily store numbers in [L, R]
	int a[1010101];//number of prime divisors
	int bucket[10101];
	public:
	long long countWinningIntervals(int L, int R)
	{
		for(int i = 1; i <= R - L + 1; i++)
			number[i] = L + i - 1;
		memset(a, 0, (R - L + 2) * sizeof(int));
		for(int i = 2; i * i <= R; i++)//enumerate divisor
			for(int j = (i - L % i) % i + 1; j <= R - L + 1; j += i)
				while(number[j] % i == 0)
					number[j] /= i, a[j]++;
		memset(bucket, 0, sizeof(bucket));
		bucket[0]++;
		for(int i = 1; i <= R - L + 1; i++)
		{
			if(number[i] > 1)//remaining big prime
				a[i]++;
			bucket[a[i] ^= a[i - 1]]++;//get prefix xor sum
		}
		long long ans = (long long)(R - L + 2) * (R - L + 1) / 2;
		for(int i = 0; i <= 10000; i++)
			ans -= (long long)bucket[i] * (bucket[i] - 1) / 2;
		return ans;
	}
};

