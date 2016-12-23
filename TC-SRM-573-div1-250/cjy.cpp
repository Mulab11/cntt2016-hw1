#include<bits/stdc++.h>
using namespace std;
class TeamContest
{
	public:
		int worstRank(vector<int> a)
		{
			int b=max(max(a[0],a[1]),a[2])+min(min(a[0],a[1]),a[2])+1,l=3,r=a.size(),s=1;
			for(sort(a.begin()+3,a.end());--r;s++,l+=2)//贪心
			{
				while(l<r&&a[l]<b-a[r])l++;
				if(l+2>r)return s;
			}
		}
};
