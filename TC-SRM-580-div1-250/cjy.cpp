#include<bits/stdc++.h>
using namespace std;
int n,m,a[111],i,j,k,s,x;
class EelAndRabbit
{
	public:
		int getmax(vector<int> l,vector<int> t)//枚举
		{
			for(n=l.size(),i=0;i<n;i++)a[++m]=t[i],a[++m]=t[i]+l[i];
			for(i=0;i<m;i++)for(j=i;j<m;s=max(s,x),j++)for(k=x=0;k<n;k++)x+=t[k]<=a[i]&&a[i]<=t[k]+l[k]||t[k]<=a[j]&&a[j]<=t[k]+l[k];
			return s;
		}
};
