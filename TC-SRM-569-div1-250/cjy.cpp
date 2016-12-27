#include<bits/stdc++.h>
using namespace std;
int i,j,s,t[2];
class TheDevice
{
	public:
		int minimumAdditional(vector<string> a)
		{
			for(i=0;i<a[0].size();s=max(s,max(2-t[1],0)+max(1-t[0],0)),i++)for(j=t[0]=t[1]=0;j<a.size();j++)t[a[j][i]-48]++;
			return s;
		}
};
