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
class GooseTattarrattatDiv1
{
	int n,f[30],x[30],w[30],p;
	inline int fa(int i)
	{
		return f[i]==i?i:f[i]=fa(f[i]);
	}
	inline void unit(int i,int j)
	{
		i=fa(i);
		j=fa(j);
		f[i]=j;
	}
public:
	int getmin(string a)
	{
		int i;
		n=a.size();
		for(i=1;i<=26;i++)
		  f[i]=i;
		for(i=0;i<n;i++)
		  {
		   unit(a[i]-'a'+1,a[n-1-i]-'a'+1);  //对应位置的字母最后一定要一样 
		   x[a[i]-'a'+1]++;
		  }
		for(i=1;i<=26;i++)
		  w[fa(i)]=max(w[fa(i)],x[i]);
		for(i=1;i<=26;i++)
		  p+=w[i];
		return n-p;
    }
};
