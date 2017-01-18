#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 305
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,x[N],big[N],sma[N];
struct Point{
		int x,y;
}A[N];
int cross(Point a,Point b,Point c)
{
		return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
class Ear{
  public:
  long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
	{
	  string s="";
	  //先把数据处理出来 
	  for (i=0;i<(int)redX.size();++i) s+=redX[i];
	  int now=0,tot=1;
	  for (i=0;i<(int)s.length();++i)
	  {
	  		if (s[i]==' ') x[tot++]=now,now=0;
	  		else now=now*10+s[i]-'0';
	  }
	  x[tot++]=now;
	  x[0]=tot-1;
	  s="";
	  for (i=0;i<(int)blueX.size();++i) s+=blueX[i];
	  now=0; tot=1;
	  for (i=0;i<(int)s.length();++i)
	  {
			if (s[i]==' ') A[tot++].x=now,now=0;
			else now=now*10+s[i]-'0'; 
	  }
	  A[tot++].x=now;
	  s="";
	  for (i=0;i<(int)blueY.size();++i) s+=blueY[i];
	  now=0; tot=1;
	  for (i=0;i<(int)s.length();++i)
	  {
			if (s[i]==' ') A[tot++].y=now,now=0;
			else now=now*10+s[i]-'0'; 
	  }
	  A[tot++].y=now;
	  --tot;	  
	  sort(x+1,x+x[0]+1);
	  for (j=1;j<=tot;++j)
	  for (i=1;i<=x[0];++i) //处理每个点左边右边的点的个数 
	  {
	  	     if (A[j].x<=x[i]) big[j]++;
	  	     if (A[j].x>=x[i]) sma[j]++;
	  }
	  long long ans=0;
	  for (i=1;i<=tot;++i) //枚举P和Q 
	  	for (j=1;j<=tot;++j)
	  		if (i!=j)
		{
			  int L=0,R=0;
			 for (k=1;k<=x[0];++k) //判每个点是否成为A/B点 
			 	if (x[k]>A[i].x&&cross((Point){x[k],0},A[i],A[j])>0)
					R+=k-1-sma[j]; //计算C/D点的数量 
				else if (x[k]<A[i].x&&cross((Point){x[k],0},A[i],A[j])<0)
				    L+=x[0]-k-big[j];
			  ans+=1ll*L*R; 
		}
	   return ans;
  }
};

