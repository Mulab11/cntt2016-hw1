#include<bits/stdc++.h>
using namespace std;
int i,x,s;
vector<int> b;
class TheJediTest//贪心
{
	public:
		int minimumSupervisors(vector<int> a,int k)
		{
			for(b=a;i<a.size();i++)if(s+=a[i]/k,x=a[i]%k)if(i+1<a.size())if(x<=b[i])a[i+1]+=x;else a[i+1]-=min(a[i+1],k-x),s++;else s++;
			return s;
		}
};
