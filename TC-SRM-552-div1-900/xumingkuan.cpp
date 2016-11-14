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
#include <cctype>
#include <queue>
#include <map>
using namespace std;

class HolyNumbers
{
	private:
	bool isprime[1010101];
	int prime[101010], primenum;
	/*int odd[1010101], mem[100001][51];//This approach would get TLE.
	long long solve(long long upTo, int p)//p-th prime
	{
		if(upTo == 1 || p == 0)//only "1"
			return 1;
		if(upTo <= prime[p])//only care about the "odd exponent" condition
			return odd[upTo];
		if(upTo <= 100000 && p <= 50 && mem[upTo][p] != -1)//memorization
			return mem[upTo][p];
		long long ret = solve(upTo, p - 1);
		for(upTo /= prime[p]; upTo >= 1; upTo /= (long long)prime[p] * prime[p])//enumerate the power of prime[p]
			ret += solve(upTo, p - 1);
		if(upTo <= 100000 && p <= 50)
			mem[upTo][p] = ret;
		return ret;
	}*/
	long long solve(long long upTo, int p)//p-th prime
	{
		if(upTo < prime[p] || p > primenum)//only "1"
			return 1;
		if(upTo < prime[p] * prime[p])//only care about the "prime" condition
			return upper_bound(prime + p, prime + primenum + 1, upTo) - (prime + p) + 1;
		// ---- what we are finding is either "1" or a prime >= prime[p].
		
		/*This would get segmentation fault.
		long long ret = solve(upTo, p + 1);
		for(upTo /= prime[p]; upTo >= 1; upTo /= (long long)prime[p] * prime[p])//enumerate the power of prime[p]
			ret += solve(upTo, p + 1);*///为什么别人这样写就A了啊T_T 
		const long long tmp = upTo;
		long long ret = 0;
		for(upTo /= prime[p]; upTo >= 1; upTo /= (long long)prime[p] * prime[p])//enumerate the power of prime[p]
			ret += solve(upTo, p + 1);
		ret += solve(tmp, p + 1);
		return ret;
	}
	public:
	void init(int maximalPrime)//get primes /*and numbers consist only of odd exponents*/
	{
		memset(isprime, true, sizeof(isprime));
		primenum = 0;
		for(int i = 2; i <= maximalPrime; i++)
		{
			if(isprime[i])
				prime[++primenum] = i;
			for(int j = 1; i * prime[j] <= maximalPrime && j <= primenum; j++)
				isprime[i * prime[j]] = false;
		}
		/*for(int i = 1; i <= maximalPrime; i++)
			odd[i] = 1;
    	for(int i = 1; i <= primenum && prime[i] * prime[i] <= maximalPrime; i++)
    		for(long long j = prime[i] * prime[i]; j <= maximalPrime; j *= prime[i] * prime[i])
	    		for(int k = 1; k * j <= maximalPrime; k++)
	    			if(k % prime[i] != 0)
	    				odd[k * j] = 0;
    	for(int i = 2; i <= maximalPrime; i++)
    		odd[i] += odd[i - 1];//prefix sum
    	memset(mem, -1, sizeof(mem));*/
	}
	long long count(long long upTo, int maximalPrime)
	{
		init(maximalPrime);
		return solve(upTo, 1);
	}
};

