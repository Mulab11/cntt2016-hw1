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
class GUMIAndSongsDiv1
{
	int n,p,x[100];
public:
	int maxSongs(vector<int> a,vector<int> b,int m)
	{
		int i,j,k,l;
		n=a.size();
		//按曲调排序 
		for(i=0;i<n;i++)
		  for(j=i+1;j<n;j++)
		    if(b[i]>b[j])
		      {
			   swap(a[i],a[j]);
			   swap(b[i],b[j]);
			  }
		//枚举曲调最低和最高的，其余按时间贪心取 
		for(i=0;i<n;i++)
		  for(j=i;j<n;j++)
		    {
			 for(k=i;k<=j;k++)
			   x[k-i]=a[k];
			 sort(x,x+j-i+1);
			 for(k=0,l=b[j]-b[i];k<=j-i && l+x[k]<=m;k++)
			   l+=x[k];
			 p=max(p,k);
			}
		return p;
    }
};
