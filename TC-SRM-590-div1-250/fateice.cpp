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
class FoxAndChess
{
	int n;
public:
	string ableToMove(string a,string b)
	{
		int i,j;
		n=a.size();
		for(i=0,j=0;i<n && j<n;i++,j++)
		  {
		   while(i<n && a[i]=='.')
		     i++;
		   while(j<n && b[j]=='.')
		     j++;
		   if(i<n && j<n && (a[i]!=b[j] || a[i]=='L' && i<j || a[i]=='R' && i>j) || (i<n)^(j<n))
		     return "Impossible";
		  }
		while(i<n && a[i]=='.')
		  i++;
		while(j<n && b[j]=='.')
		  j++;
		if(i<n || j<n)
		  return "Impossible";
		else
		  return "Possible";
    }
};
