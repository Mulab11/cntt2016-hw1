#include<bits/stdc++.h>
using namespace std;
int a1[400],a2[400],t1=1,t2=1,f1[400],f2[400],d1[303][303],d2[303][303],i,j,k;
double s;
class TreeUnion
{
	public:
		double expectedCycles(vector<string> s1,vector<string> s2,int K)
		{
			for(auto i : s1)for(auto j : i)if(j==' ')a1[++t1]=0;else a1[t1]=a1[t1]*10+j-48;
			for(auto i : s2)for(auto j : i)if(j==' ')a2[++t2]=0;else a2[t2]=a2[t2]*10+j-48;
			for(K-=2;i<=t1;i++)for(j=i+1;j<=t1;j++)d1[i][j]=d1[j][i]=d2[i][j]=d2[j][i]=1e9;
			for(i=1;i<=t1;i++)d1[i][a1[i]]=d1[a1[i]][i]=d2[i][a2[i]]=d2[a2[i]][i]=1;
			for(k=0;k<=t1;k++)for(i=0;i<=t1;i++)for(j=0;j<=t1;j++)d1[i][j]=min(d1[i][j],d1[i][k]+d1[k][j]),d2[i][j]=min(d2[i][j],d2[i][k]+d2[k][j]);
			for(i=0;i<=t1;i++)for(j=0;j<=t1;j++)f1[d1[i][j]]++,f2[d2[i][j]]++;
			for(i=1;i<K;i++)s+=.5*f1[i]*f2[K-i];
			return s/t1/(t1+1);
		}
};
