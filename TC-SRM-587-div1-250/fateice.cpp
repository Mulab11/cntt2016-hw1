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
class JumpFurther
{
public:
	int furthest(int n,int m)
	{
		int i;
		//判断是否会踩到坏的台阶 
		for(i=1;i<=n;i++)
		  if(i*(i+1)/2==m)
		    break;
		if(i>n)
		  return n*(n+1)/2;
		else
		  return n*(n+1)/2-1;
    }
};
