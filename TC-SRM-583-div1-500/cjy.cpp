#include<bits/stdc++.h>
using namespace std;
int i,r,v[55],x;
class TurnOnLamps
{
	public:
		int minimize(vector<int> a,string s,string p)
		{
			for(i=a.size();i;i--)if(p[i-1]=='0')v[a[i-1]]^=v[i];else x=(s[i-1]=='0'),r+=(x!=v[i]),v[a[i-1]]^=x;
			return r+1>>1;
		}
};
