#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;


class TheBrickTowerMediumDivOne
{
	public:
	
	vector<int> find(vector<int> heights)
	{
		int n=heights.size();
		vector<int> h=heights,r(n,0),used(n,0);
		used[0]=1;
		for(int i=1;i<n;i++)
		{
			for(int j=n-1;j>=0;j--)
			if(!used[j])
			{
				//Find the minimum j that h[j]<h[r[i-1]] or h[j] is minimum among the unused elements.
				if(h[j]<=h[r[i-1]])r[i]=j;
				else
				{
					bool flag=1;
					for(int k=0;k<n&&flag;k++)
						if(!used[k]&&h[k]<h[j])flag=0;
					if(flag)r[i]=j;
				}
			}
			used[r[i]]=1;
		}
		return r;
	}
};

