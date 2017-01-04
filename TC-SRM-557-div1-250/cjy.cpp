#include<bits/stdc++.h>
using namespace std;
int l,i;
class FoxAndMountainEasy//模拟
{
	public:
		string possible(int n,int a,int b,string s)
		{
			for(;i<s.size();i++)l=min(l,s[i]=='U'?++a:--a);
			return a-=l,n-=s.size()-l,abs(a-b)<=n&&!(a-b+n&1)?"YES":"NO";
		}
};
