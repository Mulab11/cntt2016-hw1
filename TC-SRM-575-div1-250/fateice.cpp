#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class TheNumberGameDivOne
{
public:
	string find(long long n)
	{
		if(n&1 || !(n&n-1) && int(log(n)/log(2)+0.5)&1)
		  return "Brus";
		else
		  return "John";
    }
};
