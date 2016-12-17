#include<bits/stdc++.h>
using namespace std;
int i,x,s;
class IncrementAndDoubling
{
	public:
		int getMin(vector<int>a)
		{
			for(;i<a.size();i++)s+=__builtin_popcount(a[i]),x=max(x,a[i]);
			return s+(x?(int)log2(x):0);//1的个数加倍增次数
		}
};
