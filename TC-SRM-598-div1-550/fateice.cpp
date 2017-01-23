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
#define inf 1000000000000000000ll
#define eps 1e-9
using namespace std;
class FoxAndFencing
{
public:
	string WhoCanWin(int m1,int m2,int r1,int r2,int d)
	{
		//分类讨论 
		if(m1+r1>=d)
		  return "Ciel";
		else if(m1+r1==m2+r2)
		  return "Draw";
		else if(m1+r1>m2+r2)
		  if(m1>m2 && m1+r1>=m2+r2+1+m2)
		    return "Ciel";
		  else
		    return "Draw";
		else
		  if(m2>m1 && m2+r2>=m1+r1+1+m1 || m2+r2>=d+m1)
		    return "Liss";
		  else
		    return "Draw";
	}
};
