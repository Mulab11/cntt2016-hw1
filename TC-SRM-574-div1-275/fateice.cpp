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
class TheNumberGame
{
	inline int rev(int i)
	{
		int k=0;
		while(i)
		  {
		   k=k*10+i%10;
		   i/=10;
		  }
		return k;
	}
public:
	string determineOutcome(int a,int b)
	{
		int i,n;
		for(n=1;n<=b;n*=10);
		//判断是否是子串 
		for(i=a;i;i/=10)
		  if(i%n==b)
		    return "Manao wins";
		//翻转 
		b=rev(b);
		for(i=a;i;i/=10)
		  if(i%n==b)
		    return "Manao wins";
		return "Manao loses";
    }
};
