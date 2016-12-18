#include<bits/stdc++.h>
using namespace std;
vector<int> a[55];
int r[55],t[55],i,j,k,b[55],n;
string res;
class SurveillanceSystem
{
	public:
		string getContainerInfo(string s,vector<int> c,int L)
		{
			for(n=s.size();i<n;i++)b[i+1]=b[i]+(s[i]=='X');
			for(i=0;i+L<=n;i++)a[b[i+L]-b[i]].push_back(i);
			for(auto x : c)t[x]++;
			for(i=0;i<=n;i++)for(j=0;j<n;k=0,j++)
			{
				for(auto x : a[i])k+=(j>=x&&j<x+L);
				if(k&&t[i])r[j]=max(r[j],1);
				if(k+t[i]>a[i].size())r[j]=max(r[j],2);
			}
			for(i=0;i<n;i++)res+=(r[i]?(r[i]%2?'?':'+'):'-');
			return res;
		}
};
