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
class KnightCircuit2
{
public:
	int maxSize(int n,int m)
	{
		if(min(n,m)==1)
		  return 1;
		else if(min(n,m)==2)
		  return (max(n,m)+1)/2;
		else if(n==3 && m==3)
		  return 8;
		else
		  return n*m;
    }
};
