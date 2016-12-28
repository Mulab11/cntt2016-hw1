#include <bits/stdc++.h>
using namespace std;
int f[55],s,i,j,n;
class SpellCards//背包
{
	public:
		int maxDamage(vector<int> v,vector<int> w)
		{
			for(n=v.size();i<n;i++)for(j=n-v[i];j>=0;j--)f[j+v[i]]=max(f[j+v[i]],f[j]+w[i]);
			for(i=n;~i;i--)s=max(s,f[i]);
			return s;
		}
};
