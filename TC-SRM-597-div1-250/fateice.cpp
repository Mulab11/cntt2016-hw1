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
using namespace std;
class LittleElephantAndString
{
	int n,x[30];
public:
	long long getNumber(string a,string b)
	{
		int i,j;
		n=a.size();
		for(i=0;i<n;i++)
		  x[a[i]-'A']++,x[b[i]-'A']--;
		for(i=0;i<26;i++)
		  if(x[i])
		    return -1;
		for(i=n-1,j=n;i>=0;i--)
		  {
		   for(j--;j>=0 && a[j]!=b[i];j--);
		   if(j<0)
		     break;
		  }
		return i+1;
    }
};
