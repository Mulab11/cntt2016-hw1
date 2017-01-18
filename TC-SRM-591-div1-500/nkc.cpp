#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct PyramidSequences
{
	int gcd(int a,int b)
	{
		if(!a) return b;
		return gcd(b%a,a);
	}
	long long distinctPairs(int N, int M)
	{
		N--;M--;
		long long g=gcd(N,M);
		N/=g;M/=g;
		long long ans=(long long)N*M*(g-1)+((long long)(N+1)*(M+1)+1)/2;//数学式子直接计算 
		return ans;
	}
};