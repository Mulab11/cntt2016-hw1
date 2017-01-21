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
class TurnOnLamps
{
	int n,f[60];
public:
	int minimize(vector<int> x,string a,string b)
	{
		int i;
		n=x.size();
		for(i=n;i>0;i--)
		  {
		   if(b[i-1]=='1' && !((f[i]^a[i-1]-'0')&1))  //判断i连向父亲的边是否需要翻转 
		     f[i]++;
		   f[x[i-1]]+=f[i];
		  }
		return f[0]+1>>1;
    }
};
