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
class TriangleXor
{
	double p;
public:
	int theArea(int n)
	{
		int i,j,k;
		//枚举每一层 
		for(i=n+1,j=0,k=1;i>0;i--,j++,k=-k)
		  p+=(j==0?0.5:(1-1.0*j/(j+n)))*n*i*k;
		return int(p);
    }
};
