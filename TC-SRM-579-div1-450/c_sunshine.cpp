#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int inf=1000000000;
template<class T>inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T>inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

class TravellingPurchasingMan
{
	public:
	int n,m,g[55][55];
	int L[55],R[55],D[55];
	int f[65536][55];
	
	void get_3_number(string s,int &a,int &b,int &c)
	{
		a=b=c=0;
		int i;
		for(i=0;s[i]!=' ';i++)a=a*10+s[i]-'0';
		for(i++;s[i]!=' ';i++)b=b*10+s[i]-'0';
		for(i++;i<s.size();i++)c=c*10+s[i]-'0';
	}
	
	int cnt1(int x)
	{return x?1+cnt1(x&(x-1)):0;}
	
	int maxStores(int N,vector<string> interestingStores,vector<string> roads)
	{
		n=N;m=interestingStores.size();
		for(int i=0;i<m;i++)
			get_3_number(interestingStores[i],L[i],R[i],D[i]);
		//Above is getting the input.
		memset(g,63,sizeof(g));
		for(int u,v,w,i=0;i<roads.size();i++)
		{
			get_3_number(roads[i],u,v,w);
			ten(g[u][v],w);
			ten(g[v][u],w);
		}
		for(int k=0;k<n;k++)//Use Floyd to determine APSP
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					ten(g[i][j],g[i][k]+g[k][j]);
		int ans=0;
		//f[s][i]: The earliest time to reach the situation that 
		//all stores in set s has been visited, and now in store i.
		memset(f,63,sizeof(f));
		f[0][n-1]=0;
		for(int s=0;s<1<<m;s++)
		{
			//We can go to any store without taking purchases,
			//and it's clear we should go along the shortest path.
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					ten(f[s][j],f[s][i]+g[i][j]);
			for(int i=0;i<n;i++)//Take a purchase in a store.
				if(f[s][i]<inf)
				{
					ans=max(ans,cnt1(s));//The number of purchases is the number of "1"s in binary s.
					if(i<m&&((s>>i)&1)==0&&f[s][i]<=R[i])
						ten(f[s^1<<i][i],max(L[i],f[s][i])+D[i]);
				}
		}
		return ans;
	}
};

