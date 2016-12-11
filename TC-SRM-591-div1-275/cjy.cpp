#include<bits/stdc++.h>
using namespace std;
int n,s,i,r;
class TheTree
{
	public:
		int maximumDiameter(vector<int>c)
		{
			n=c.size();
			for(i=0;i<n;i++)//枚举LCA			
			{
				for(r=i;r<n&&c[r]>1;r++);
				s=max(s,r+n-i-i);
			}
			return s;
		}
};
