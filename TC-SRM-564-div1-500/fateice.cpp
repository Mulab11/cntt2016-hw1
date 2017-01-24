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
class AlternateColors2
{
	long long p;
public:
	long long countWays(int n,int m)
	{
		int i;
		if(m%3==1)
		  p+=(L)(n-m+2)*(n-m+1)/2;  //RGBRGB...RGB'R'...
		for(i=0;i*3<m;i++)
		  {
		   if(i*3+1<m)   //RGBRGB...RGBRRRRR...RR'R'...
		     p++;
		   p+=(m-i*3-2)/2*2;  //RGBRGB...RGBRGRGRG...RGRRR'R'...
		   if(i*3+1<m && m-i*3&1)  //RGBRGB....RGBRGRG...RGRG'R'...
		     p+=(n-m+1)*2;
		  }
		return p;
    }
};
