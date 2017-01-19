#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class FoxPaintingBalls
{
public:
	long long theMax(long long r,long long g,long long b,int n)
	{
		long long m=(L)n*(n+1)/6;
		if(n==1)
		  return r+g+b;
		else if(n%3==1)
		  return min(min(r/m,g/m),min(b/m,(r+g+b)/(3*m+1)));  //n%3=1时，有一种颜色多一个 
		else
		  return min(min(r/m,g/m),b/m);  //n%3!=1时，每种颜色数量相同 
	}
};
