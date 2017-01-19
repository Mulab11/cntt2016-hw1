#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class ConversionMachine
{
	int n,m,t,x[3],u[200][200],v[200][200],w[200][200];
	inline void cheng(int u[200][200])  //矩乘 
	{
		int i,j,k,q=1000000007;
		for(i=0;i<=t;i++)
		  for(j=0;j<=t;j++)
		    for(k=0;k<=t;k++)
		      w[i][j]=(w[i][j]+(L)u[i][k]*v[k][j])%q;
		for(i=0;i<=t;i++)
		  for(j=0;j<=t;j++)
		    {
			 v[i][j]=w[i][j];
			 w[i][j]=0;
			}
	}
public:
	int countAll(string a,string b,vector<int> c,int d)
	{
		int i,j;
		long long k=0;
		n=a.size();
		for(i=0;i<n;i++)
		  {
		   x[(b[i]-a[i]+3)%3]++;
		   if((b[i]-a[i]+3)%3>=1)
		     k+=c[a[i]-'a'];
		   if((b[i]-a[i]+3)%3==2)
		     k+=c[(a[i]-'a'+1)%3];
		  }
		if(k>d)
		  return 0;
		m=(d-k)/(c[0]+c[1]+c[2])*3+x[1]+x[2]*2+1;  //计算操作数上限 
		for(i=0;i<=n;i++)
		  for(j=0;j<=n-i;j++)
		    {
			 if(i)
			   u[i*(n+1)+j][(i-1)*(n+1)+j]=i;
			 if(j)
			   u[i*(n+1)+j][(i+1)*(n+1)+j-1]=j;
			 if(n-i-j)
			   u[i*(n+1)+j][i*(n+1)+j+1]=n-i-j;
			}
		t=n*(n+1)+1;
		u[0][t]=1;
		u[t][t]=1;
		for(i=0;i<=t;i++)
		  v[i][i]=1;
		//dp记录还需1/2次操作的位置数+矩乘快速幂 
		for(i=1;i<=m;i<<=1);
		for(i>>=1;i>0;i>>=1)
		  {
		   cheng(v);
		   if(m&i)
		     cheng(u);
		  }
		for(i=0;i<=t;i++)
		  for(j=0;j<=t;j++)
		    u[i][j]=0;
		u[0][x[1]*(n+1)+x[2]]=1;
		cheng(u);
		return v[0][t];
	}
};
