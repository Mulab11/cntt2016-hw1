#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
class RotatingBot
{
	int a[4];
	map<int,int> f;
public:
	int minArea(vector<int> w)
	{
		int n=w.size();
		int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
		int i,j,x=0,y=0;
		f[0]=1;
		for(i=0;i<n;i++)
		  {
		   for(j=1;j<=w[i];j++)
		     {
		 	  x+=dx[i&3];
			  y+=dy[i&3];
			  if(f[x*10000+y])
			    return -1;
			  f[x*10000+y]=1;
			 }
		   if(f[(x+dx[i&3])*10000+y+dy[i&3]])  //因为路径碰撞而转弯 
		     continue;
		   if(i<n-1 && (i==2 && x<0 || i==3 && y<0))  //没走到边界 
		     return -1;
		   if(i<=3)
		     a[i]=((i&1)?y:x);
		   else
		     if(((i&1)?y:x)!=a[i&3] && i<n-1)  //没走到边界 
		       return -1;
		  }
		if(a[2]<0)  //右边界和下边界不会小于0 
		  a[2]=0;
		if(a[3]<0)
		  a[3]=0;
		i--;
		if((i&3)<2 && ((i&1)?y:x)<a[i&3] || (i&3)>=2 && ((i&1)?y:x)>a[i&3])  //最后一步走出边界 
		  return -1;
		return (a[2]-a[0]+1)*(a[3]-a[1]+1);
	}
};
