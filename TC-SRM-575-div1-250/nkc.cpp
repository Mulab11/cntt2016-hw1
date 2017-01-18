#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define J return "John"
#define B return "Brus"
using namespace std;
struct TheNumberGameDivOne
{
	string find(long long n)
	{
		if(n%2==1) B;
		int i;
		for(i=1;(1LL<<i)<=n;i+=2)
		if((1LL<<i)==n) B;
		J;
	}
};