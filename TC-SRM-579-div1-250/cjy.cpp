#include<bits/stdc++.h>
using namespace std;
class UndoHistory
{
	public:
		int LCP(string a,string b)
		{
			int i=0;
			for(;i<a.size()&&i<b.size()&&a[i]==b[i];i++);
			return i;
		}
		int minPresses(vector<string> e)//贪心
		{
			int s=e[0].size()+e.size(),j,i=1,k;
			for(;i<e.size();s+=e[i].size()-k+2,i++)for(j=0,k=(LCP(e[i-1],e[i])==e[i-1].size()?e[i-1].size()+2:0);j<i;j++)k=max(k,LCP(e[i],e[j]));
			return s;
		}
};
