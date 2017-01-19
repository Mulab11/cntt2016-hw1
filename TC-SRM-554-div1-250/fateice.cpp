#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class TheBrickTowerEasyDivOne
{
public:
	int find(int a,int b,int c,int d)
	{
		if(b==d)   //高度一样 
		  return 2*min(a,c)+(a!=c);
		else       //高度不一样 
		  return 3*min(a,c)+(a!=c);
	}
};
