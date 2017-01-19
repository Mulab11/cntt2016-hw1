#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class ColorfulChocolates
{
public:
	int maximumSpread(string a,int m)
	{
		int n=a.size(),p,ans=0;
		int i,j,k,x[100];
		for(i=0;i<n;i++)   //枚举答案子串的其中一个位置 
		  {
		   p=0;
		   for(j=i-1,k=0;j>=0;j--)   //计算其它相同字母移过来的代价 
		     if(a[i]==a[j])
		       x[++p]=k;
		     else
		       k++;
		   for(j=i+1,k=0;j<n;j++)
		     if(a[i]==a[j])
		       x[++p]=k;
		     else
		       k++;
		   sort(x+1,x+p+1);
		   for(j=1,k=0;j<=p && k+x[j]<=m;j++)
		     k+=x[j];
		   ans=max(ans,j);
		  }
		return ans;
	}
};
