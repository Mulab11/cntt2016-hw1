#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

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
#define Mo 1000000007

using namespace std;
int i,j,m,n,p,k,f[N][N],AL[N],AR[N],Max[N];
string L,R;

void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; }
class WolfInZooDivOne{
	 public:
	 	int count(int n,vector<string> A,vector<string> B)
	 	{
	 		  for (i=0;i<(int)A.size();++i) L+=A[i];
			  for (i=0;i<(int)B.size();++i) R+=B[i];
			  int now=0;
			  for (;now<L.length();++now)
			  {
			  	  int sum=0;
		          while (now<L.length()&&L[now]!=' ') sum=sum*10+L[now]-'0',++now;
		          ++sum;
				  AL[++m]=sum;
			  }
			  now=0; m=0;
			  for (;now<R.length();++now)
			  {
			  	  int sum=0;
		          while (now<R.length()&&R[now]!=' ') sum=sum*10+R[now]-'0',++now;
		          ++sum;
				  AR[++m]=sum; 
			  }		
			  for (i=1;i<=m;++i)
			    for (j=AL[i];j<=AR[i];++j)  Max[j]=max(Max[j],AR[i]);
			  f[0][0]=1;
			  for (i=0;i<n;++i) //设f_{i,j}为做完前i个位置,当前已经填了1个1的区间的最右端点是j的方案数. 
			    for (j=0;j<=n;++j)
				   if(f[i][j]) 
				   {
				   	     if (j==i+1) jia(f[i+1][0],f[i][j]); else jia(f[i+1][j],f[i][j]);
				   	     if(j) //考虑在这个位置放数的方案,那么预处理出包含某个点向后最右的右端点即可. 
				   	     {
				   	     int Next=max(Max[i+1],j);
				   	     if (Next<=j) jia(f[j][0],f[i][j]);
						 else jia(f[j][Next],f[i][j]); 
						 }
						 else 
						 {
						 	   if(Max[i+1]<=i+1) jia(f[i+1][0],f[i][j]);
						 	   else jia(f[i+1][Max[i+1]],f[i][j]);
						 }
			       }
	 	return f[n][0];
	    }
}E;
int main()
{
  vector<string> L,R;
  L.push_back("0"); R.push_back("4");
  printf("%d\n",E.count(5,L,R));
} 

